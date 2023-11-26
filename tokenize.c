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
 * process_tokens - Process tokens in the shell structure.
 * @sh: Pointer to the shell structure.
 */
void process_tokens(g_var *sh)
{
	char **tm = NULL;
	size_t size_a = 0;
	int i = 0;

	for (i = 0; i < sh->num_tokens - 1; ++i)
	{
		tm = NULL;
		remove_emptyspaces(&sh->tokens[i]);
		size_a = tokenize(&tm, sh->tokens[i], " ");

		if (get_built_in(sh, tm[0]))
		{
			get_built_in(sh, tm[0])(&sh);
		}
		else
		{
			sh->command = check_cmd_exist(tm[0]);

			if (sh->command != NULL)
			{
				execute(sh, tm, sh->environs);
			}
			else
			{
				not_found(sh, sh->prog_name, tm[0], sh->process_id, "not found");
			}

			free_arr(&tm, size_a);
			free(sh->command);
			sh->command = NULL;
		}
	}
}
