#include "shell.h"
/**
 * tokenize - tokenize the string and save them in an arrray
 * @arr: array to be modifieda and save tokens
 * @strn: string to be tokenized
 * @delim: delimeter used to tokenize a string
 * Return: returns size of the string array
*/
int tokenize(char ***arr, char *strn, char *delim)
{
	char *str = NULL, *strd = NULL, *strl = NULL, *strln = NULL;
	int tokens = 0, i = 0;

	if (strn == NULL)
		return (tokens);

	strl = _strdup(strn);
	strln = _strtok(strl, delim);

	while (strln)
	{
		tokens++;
		strln = _strtok(NULL, delim);
	}

	tokens++;
	free(strl);

	*arr = malloc(sizeof(char *) * tokens);
	strd = _strdup(strn);
	str = _strtok(strd, delim);

	while (str)
	{
		(*arr)[i] = malloc(sizeof(char) * strlen(str) + 1);
		_strcpy((*arr)[i], str);
		str = _strtok(NULL, delim);
		i++;
	}

	(*arr)[i] = NULL;
	free(strd);

	return (tokens);
}
/**
 * cleanup_and_exit - Cleans up resources and exits the program.
 * @sh: Pointer to the g_var structure.
 * @tm: Pointer to the char array.
 * @temp: Pointer to the char array.
 * @size_a: The size of the char array.
 * @p: Pointer to the ppl structure.
 */
void cleanup_and_exit(g_var *sh, char **tm, char *temp, int size_a, ppl *p)
{
	free_arr(&sh->tokens, sh->num_tokens);
	free_arr(&tm, size_a);
	sh->num_tokens = tokenize(&sh->tokens, temp, " ");
	free_pip(&p);
	free(temp);
	sh->fl_pip = 8;
}

/**
 * process_builtin - Process built-in commands in the shell.
 * @sh: Pointer to the g_var structure.
 * @tm: Array of command tokens.
 * @temp: Temporary string.
 * @size_a: Size of array.
 * @p: Pointer to pip_t structure.
 * Return: 1 if successful, 0 otherwise.
 */
int process_builtin(g_var *sh, char **tm, char *temp, int size_a, ppl *p)
{
	int result = 0;

	if (get_built_in(sh, tm[0]))
	{
		sh->fl_pip = 2;
		result = get_built_in(sh, tm[0])(&sh);

		switch (result)
		{
			case 3:
				cleanup_and_exit(sh, tm, temp, size_a, p);
				exiting(&sh);
				return (1);

			case 4:
				cleanup_and_exit(sh, tm, temp, size_a, p);
				_printenv(&sh);
				exiting(&sh);
				return (1);

			case 5:
				break;

			case 6:
				break;

			default:
				break;
		}
	}

	return (0);
}

/**
 * process_tokens - Process tokens in the shell structure.
 * @sh: Pointer to the shell structure.
 * @p: list of pipe commands
 */
void process_tokens(g_var *sh, ppl **p)
{
	char **tm = NULL, *temp = NULL;
	size_t size_a = 0;
	int i = 0;

	for (i = 0; i < sh->num_tokens - 1; ++i)
	{
		tm = NULL;
		remove_emptyspaces(&sh->tokens[i]);
		temp = _strdup(sh->tokens[i]);
		size_a = tokenize(&tm, sh->tokens[i], " ");

		if (process_builtin(sh, tm, temp, size_a, *p))
		{

		}
		else
		{
			sh->command = check_cmd_exist(tm[0]);
			if (sh->command != NULL)
				execute(sh, tm, sh->environs);
			else
				not_found(sh, sh->prog_name, tm[0], sh->process_id, "not found");

			free_arr(&tm, size_a);
			free(sh->command);
			sh->command = NULL;
		}

		free(temp);
	}
}
