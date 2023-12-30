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
			case 2:
				sh->command = _strdup(temp);
				sh->fl_pip  = 8;
				result = _echo(&sh);
				free_arr(&tm, size_a);
				break;
			case 3:
				cleanup_and_exit(sh, tm, temp, size_a, p);
				exiting(&sh);
				return (1);
			case 4:
				free_arr(&tm, size_a);
				sh->fl_pip = 8;
				_printenv(&sh);
				break;
			case 5:
				free_arr(&tm, size_a);
				sh->fl_pip = 8;
				_setenv(&sh);
				break;
			case 6:
				free_arr(&tm, size_a);
				sh->fl_pip = 8;
				_unsetenv(&sh);
				break;
			default:
				break;
		}
		return (1);
	}
	return (0);
}
/**
 * process_semicolon_cmd - Process a command if the token contains a semicolon.
 * @temp: temporary string
 * @head: head of a list
 * @sh: gloabal variables
 * @h: list of commands
 * @arr: array of strings
 * @size_a: size of the array
 * Return: returns 1 if semi colon present else 0;
 */
int process_semicolon_cmd(char *temp, cmd_list **head, g_var *sh,
cmd_n_list **h, char **arr, int size_a)
{
	if (check_semicolon_tk(temp, head))
	{
		process_commands(*head, sh, h);
		sh->process_id++;
		free_list_cmd(head);
		free_arr(&arr, size_a);
		free(temp);
		arr = NULL;
		free(sh->command);
		return (1);
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
	char **tm = NULL, *temp = NULL, *tem =  NULL, *ch = NULL, *ch1 = NULL;
	cmd_n_list **h = NULL;
	cmd_list *head = NULL;
	size_t size_a = 0, j = 0;
	int i = 0;

	for (i = 0; i < sh->num_tokens - 1; ++i, tm = NULL, sh->command = NULL)
	{
		remove_emptyspaces(&sh->tokens[i]);
		temp = _strdup(sh->tokens[i]);
		size_a = tokenize(&tm, sh->tokens[i], " ");
		if (process_semicolon_cmd(temp, &head, sh, h, tm, size_a))
			continue;
		if (process_builtin(sh, tm, temp, size_a, *p))
		{
		}
		else
		{
			for (j = 1; j < size_a - 1; j++, free(tem))
			{
				tem = _strdup(tm[j]);
				if (tem && _strpbrk(tem, "$"))
				{
					ch = _strpbrk(tem, "$");
					ch1 = (ch + _strspn(ch, "$"));
					ch1 = _getenv(ch1);
					free(tm[j]);
					tm[j] = ch1;
				}
			}
			sh->command = check_cmd_exist(tm[0]);
			if (sh->command != NULL)
				execute(sh, tm, sh->environs);
			else
				not_found(sh, sh->prog_name, tm[0], sh->process_id, "not found");
			free_arr(&tm, size_a);
			free(sh->command);
		}
		free(temp);
	}
}
