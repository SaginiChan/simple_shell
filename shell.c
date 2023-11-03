#include "shell.h"

/**
 * main - simple shell program
 * @argc: NUMBER OF ARGUMENTS
 * @argv: array of strings
 * @envp: array of environment variables
 * Return: always return 0;
*/
int main(int argc, char const *argv[], char *envp[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 9;

	(void) argc;
	(void) argv;
	(void) envp;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("$ ");
		}

		read = _getline(&line, &len, stdin);

		if (read == -1)
			break;

	}

	free(line);

	return (0);
}
