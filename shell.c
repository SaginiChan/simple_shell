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
	g_var *sh = malloc(sizeof(gbf_var));
	int i = 0;

	if (sh == NULL)
	{
		exit(1);
	}

	(void) argc;
	sh->prog_name = argv[0];
	initialize_shell(&sh, envp);

	if (argc > 1)
	{
		sh->buffer = _calloc(sizeof(char *), MAX_INPUT_SIZE);

		for (i = 1; i < argc; i++)
		{
			strcat(sh->buffer, argv[i]);

			if (i < argc - 1)
			{
				_strcat(sh->buffer, " ");
			}
		}

		sh->mode = 1;
		remove_nl(&(sh->buffer));
		shell_prompt(&sh);
	}
	else
	{
		shell_prompt(&sh);
	}

	free(sh);
	return (0);
}
