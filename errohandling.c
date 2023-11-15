#include "shell.h"

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
 * @prog: Name of the program.
 * @comd: Command that was not found.
 * @pid_no: Process ID number.
 * @msg: Error message.
 */

void not_found(char *prog, char *comd, int pid_no, char *msg)
{
	char *str = malloc(sizeof(char) * 4);
	int len = 0;

	_memset(str, 0, 4);
	len = int_len(pid_no);
	str_buff(&str, pid_no, len);
	_puts(prog);
	_puts(": ");
	_puts(comd);
	_puts(": ");
	_puts(str);
	_puts(": ");
	_puts(msg);
	_puts("\n");
	free(str);
}
/**
 * illegal_no - Handles the "illegal number" case.
 * @prog_name: Name of the program.
 * @pr_id: Process ID number.
 * @msg: Error message.
 * @str: Command that was not found.
 */
void illegal_no(char *prog_name, int pr_id, char *msg, char *str)
{
	char *string = malloc(sizeof(char) * 4);
	int len = 0;

	_memset(string, 0, 4);
	len = int_len(pr_id);
	string = str_buff(&str, pr_id, len);
	_puts(prog_name);
	_puts(": ");
	_puts(string);
	_puts(": ");
	_puts(msg);
	_puts(": ");
	_puts(str);
	_puts("\n");
	free(str);
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
