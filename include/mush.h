#ifndef _MUSH_H
#define _MUSH_H

#include <stdbool.h>

#define PROMPT "( ͡° ͜ʖ ͡°) "

extern bool verbose;

/*
 * @brief: Print the prompt string
 */
void prompt(void);

/*
 * @brief: Read, evaluate, and print loop
 * @return: 0 on success, -1 on failure
 */
int read_eval_print_loop(void);

/*
 * @brief: Print usage information
 */
void usage(void);

#endif /* _MUSH_H */
