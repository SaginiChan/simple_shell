#include "shell.h"

/**
 * main - simple shell program
 * @argc: NUMBER OF ARGUMENTS
 * @argv: array of strings
 * @envp: array of environment variables
 * Return: always return 0;
*/
int main(int argc, char  *argv[], char *envp[])
{
	g_var *sh = _calloc(sizeof(char *), sizeof(gbf_var));

	if (sh == NULL)
	{
		exit(1);
	}

	(void) argc;
	sh->prog_name = argv[0];
	initialize_shell(&sh, envp);
	shell_prompt(&sh);
	free(sh);
	return (0);
}
