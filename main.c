#include <sys/types.h>

#include "mush.h"

int main(int argc, char *argv[])
{
	// TODO: configure signal handling
	return read_eval_print_loop();
}
