#include <sys/types.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include "mush.h"

#define EXIT_ERR(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define USAGE_MSG "Usage: mush [options] [command_string | file]\n" \
	"Options:\n" \
	"  -h, --help     Display this help message and exit\n" \
	"  -v, --verbose  Enable verbose output\n"

/*
 * @brief Print the usage message to stderr.
 */
static void print_usage(void)
{
	fprintf(stderr, USAGE_MSG);
}


/*
 * @brief General-purpose signal handler to handle clean shutdown.
 * @param signum The signal number that was received.
 */
static void signal_handler(int signum)
{
	fprintf(stderr, "\nReceived signal %d. Exiting...\n", signum);
	// Clean up resources...
	exit(EXIT_SUCCESS);
}

/*
 * @brief Configures signal handling for the server with a specified handler.
 * @param handler A pointer to the signal handler function.
 * @return 0 on success, or a non-zero value if any sigaction call fails.
 *
 * @details This function sets up signal handling for several critical signals
 * (SIGINT, SIGTERM, SIGHUP, SIGQUIT) using a provided signal handler.
 * The function aims to ensure that the server can shut down gracefully when
 * receiving these signals. The SA_RESTART flag is not set in order to allow
 * system calls like accept() to be interrupted, facilitating a clean shutdown.
 * The caller must provide a valid signal handler function that matches the
 * signature required for signal handlers. If configuring any signal fails,
 * the function immediately returns a non-zero value indicating failure.
 */
int configure_shutdown_signals(void (*handler)(int))
{
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	/* Don't set SA_RESTART to allow clean interruption */
	return (sigaction(SIGINT, &sa, NULL) || sigaction(SIGTERM, &sa, NULL) ||
		sigaction(SIGHUP, &sa, NULL) || sigaction(SIGQUIT, &sa, NULL));
}

/*
 * @brief Reap all terminated children to prevent zombie processes.
 * @param sig The signal number (should be SIGCHLD).
 *
 * @details
 * Loop as long as waitpid finds terminated children to reap.
 * `waitpid` with -1 waits for any child process.
 */
static void sigchld_handler(int sig)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		; /* Empty loop body; all work is done in the condition. */
}

/*
 *
 * @details This function installs sigchld_handler to handle SIGCHLD signals.
 * It ensures that child processes are properly reaped to avoid zombie processes.
 */
int install_child_reaper(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	sa.sa_handler = sigchld_handler;
	return sigaction(SIGCHLD, &sa, NULL);
}

/* 
 * @brief Main entry point for the program.
 */
int main(int argc, char *argv[])
{
	int opt;
	/* Define long options */
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"verbose", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};

	/* Configure signal handling */
	if (configure_shutdown_signals(signal_handler))
		EXIT_ERR("Failed to configure shutdown signals");

	if (install_child_reaper())
		EXIT_ERR("Failed to install child reaper");


	/* Parse command line options */
	while ((opt = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
		switch (opt) {
			case 'h':
				print_usage();
				exit(EXIT_SUCCESS);
			case 'v':
				verbose = true;
				break;
			case '?':
				print_usage();
				exit(EXIT_FAILURE);
			default:
				; // do nothing
		}
	}

	/* Run the shell */
	return read_eval_print_loop();
}
