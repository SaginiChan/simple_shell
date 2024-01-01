#include "shell.h"
#define BUFS 1024
/**
 * int_To_Str - Converts an integer to a string.
 * @str: Pointer to the destination string.
 * @num: The integer to convert.
 */
void int_To_Str(char *str, int num)
{
	int i = 0;
	int is_Neg = 0;

	if (num < 0)
	{
		is_Neg = 1;
		num = -num;
	}

	do {
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num > 0);

	if (is_Neg)
	{
		str[i++] = '-';
	}

	str[i] = '\0';
}

/**
 * not_found - Handles the "not found" case.
 * @sh: global variables
 * @prog: Name of the program.
 * @comd: Command that was not found.
 * @pid_no: Process ID number.
 * @msg: Error message.
 */

void not_found(g_var *sh, char *prog, char *comd, int pid_no, char *msg)
{
	char *str = malloc(sizeof(char) * 4);
	int len = 0;

	_memset(str, 0, 4);
	len = int_len(pid_no);
	str_buff(&str, pid_no, len);

	write(STDERR_FILENO, prog, _strlen(prog));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, _strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, comd, _strlen(comd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);

	sh->status_code = 127;
	free(str);
}
/**
 * illegal_no - Handles the "illegal number" case.
 * @prog_name: Name of the program.
 * @com: command that fails
 * @pr_id: Process ID number.
 * @msg: Error message.
 * @str: Command that was not found.
 */
void illegal_no(char *prog_name, char *com, int pr_id, char *msg, char *str)
{
	char *string = malloc(sizeof(char) * 4);
	int len = 0;

	_memset(string, 0, 4);
	len = int_len(pr_id);
	str_buff(&string, pr_id, len);

	write(STDERR_FILENO, prog_name, strlen(prog_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, string, strlen(string));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, com, strlen(com));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, strlen(str));
	write(STDERR_FILENO, "\n", 1);
	free(string);
}
/**
 * usage_err - Handles the "usage erro" case.
 * @str: error messege
 */
void usage_err(char *str)
{
	size_t len = _strlen(str) + 1;

	write(STDERR_FILENO, str, len);
	_puts("\n");
}
/**
 * cd_error - Handles the "chane DIR" case.
 * @prog_name: Name of the program.
 * @arg: name of the directory.
 */
void cd_error(const char *arg, const char *prog_name)
{
    char buf[BUFS];
    char *name = (char *)malloc(BUFS);

    if (name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    memset(name, 0, BUFS);
    memcpy(name, prog_name, BUFS);
    memset(buf, 0, BUFS);
    _strcat(buf, name);
    _strcat(buf, ": ");
    _strcat(buf, "1: ");
    _strcat(buf, "cd: ");
    _strcat(buf, "can't cd to ");
    _strcat(buf, (char *)arg);
    _strcat(buf, "\n");

    write(STDERR_FILENO, buf, _strlen(buf));

    free(name);
}
