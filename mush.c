#include <stdio.h>
#include <unistd.h>
#include "mush.h"

#define BUFSIZE 4096

char input[BUFSIZE];

void prompt(void)
{
	fprintf(stderr, "%s", PROMPT);
}

int read_eval_print_loop(void)
{
	ssize_t n = 0;
	prompt();
	while ((n = read(STDIN_FILENO, input, sizeof(input))) > 0) {
		if (n > 0)
			write(STDOUT_FILENO, input, n);
		prompt();
	}
	return 0;
}
