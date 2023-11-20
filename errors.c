#include "shell.h"
/**
 * handle_error - Print an error message and exit.
 * @message: The error message to print.
 */
void handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
