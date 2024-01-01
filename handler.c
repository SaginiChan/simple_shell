#include "shell.h"

/**
 * cleanup_exit - Clean up resources and exit the shell.
 * @sh: A pointer to the global variables structure.
 * @shell: A double pointer to the shell structure.
 * @status: The exit status code.
 * @sh: Pointer to the global variables structure.
 * @shell: Double pointer to the shell structure.
 * @status: Exit status code.
 */
void cleanup_exit(g_var *sh, g_var **shell, int status)
{
	free_arr(&(sh->tokens), sh->num_tokens);
	free_arr(&(sh->alias), sh->alias_size);
	free_arr(&(sh->pointers), sh->added_envs);
	free_arr(&(sh->pip_cmds), sh->pip_num);
	free(sh->buf_pi);
	cleanup(sh);
	*shell = NULL;
	exit(status);
}
/**
 * refresh - clean up the varable used before next iteration.
 * @shell: Pointer to the shell structure to be cleaned.
 */
void refresh(g_var *shell)
{
	g_var *sh = shell;

	if (sh->tokens)
		free_arr(&(sh->tokens), sh->num_tokens);

	sh->tokens = NULL;

	if (shell->command != NULL)
	{
		free(shell->command);
		shell->command = NULL;
	}

	if (shell->buffer != NULL)
	{
		free(shell->buffer);
		shell->buffer = NULL;
	}

	sh->num_tokens = 0;
	sh->command = NULL;
	sh->buffer = NULL;
}

/**
 * cleanup - Clean up the variables used before the next iteration.
 * @shell: Pointer to the shell structure to be cleaned.
 */
void cleanup(g_var *shell)
{
	if (shell == NULL)
	{
		return;
	}

	if (shell->command != NULL)
	{
		free(shell->command);
		shell->command = NULL;
	}

	if (shell->buffer != NULL)
	{
		free(shell->buffer);
		shell->buffer = NULL;
	}
	if (shell->buf_pi != NULL)
	{
		free(shell->buf_pi);
		shell->buffer = NULL;
	}
	/* free(shell->PATH); */
	shell->nread = 0;
	shell->num_tokens = 0;
	shell->size = 0;
}

/**
 * exiting - converts str to int status.
 * @shell: stract passed to access the array of commands.
 * Return: returns 0 on succes
 *                 -1 on failuire
 */
int exiting(g_var **shell)
{
	int status = 0;
	g_var *sh = *shell;
	char *str = NULL, *name = sh->prog_name;

	str = sh->tokens[1];

	if (sh->fl_pip == 2)
	{
		return (3);
	}
	if (str != NULL)
	{
		status = _atoi(str);
		if (status >= 0)
		{
			free_arr(&(sh->tokens), sh->num_tokens);
			free_arr(&(sh->pip_cmds), sh->pip_num);
			free(sh->buf_pi);
			cleanup(sh);
			free(*shell);
			exit(status);
		}
		else
		{
			illegal_no(name, sh->tokens[0], sh->process_id, "Illegal number", str);
			free_arr(&(sh->tokens), sh->num_tokens);
			free_arr(&(sh->pip_cmds), sh->pip_num);
			free(sh->buf_pi);
			cleanup(sh);
			free(*shell);
			exit(2);
		}
	}
	else
	{
		cleanup_exit(sh, shell, status);
	}
	return (-1);
}
/**
 * control_d - Exits a command using CTR + D.
 * @shell: The pointer to struct variables.
 *
 */
void control_d(g_var *shell)
{
	g_var *sh = shell;

	if (sh->buffer != NULL)
	{
		/* free_arr(sh->tokens, sh->num_tokens); */
		free_arr(&(sh->alias), sh->alias_size);
		free_arr(&(sh->pointers), sh->added_envs);
		cleanup(sh);
		free(sh);
	}
	else
	{
		free_arr(&(sh->tokens), sh->num_tokens);
		free_arr(&(sh->alias), sh->alias_size);
		free_arr(&(sh->pointers), sh->added_envs);
		cleanup(sh);
		free(sh);
	}

	exit(EXIT_SUCCESS);
}
