#include "shell.h"
/**
 * cleanup_and_free_tokens - Free the tokens array and perform cleanup.
 * @sh: Pointer to the shell structure.
 */
void cleanup_and_free_tokens(g_var *sh)
{
	free_arr(&(sh->tokens), sh->num_tokens);
	(sh->process_id)++;
	cleanup(sh);
}
/**
 * remove_qutes - remove all white spaces
 * @string: string to remove white spaces
 *
*/
void remove_qutes(char **string)
{
	int j = 0, i = 0;

	for (; (*string)[i]  != '\0'; ++i)
	{
		if ((*string)[i] != '"')
		{
			(*string)[j] = (*string)[i];
			j++;
		}
	}

	(*string)[j] = '\0';
}
/**
 * remove_nl - remove extra white spaces
 * @str: string to remove white spaces
 *
*/
void remove_nl(char **str)
{
	int length = _strlen(*str);

	if (length > 0 && (*str)[length - 1] == '\n')
	{
		(*str)[length - 1] = '\0';
	}

}
