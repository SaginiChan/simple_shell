#include "shell.h"

/**
 * is_balanced_quotes - Checks if the input string has
 *                      balanced single and double quotes.
 * @buffer: The input string to be checked for balanced quotes.
 *
 * Return: Returns 1 if the input has balanced quotes, 0 otherwise.
 */
int is_balanced_quotes(const char *buffer)
{
	int single_quotes = 0;
	int double_quotes = 0, i = 0;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '\'')
		{
			single_quotes = 1 - single_quotes;
		}
		else
			if (buffer[i] == '\"')
			{
				double_quotes = 1 - double_quotes;
			}
	}

	return ((single_quotes == 0) && (double_quotes == 0));
}

/**
 * hasSymbols - it checks if symbols exists if
 *                   exists breaks the command into list
 * @sh: global variable in struct
 *
 * Return: returns 1 if true and 0 if false
*/
int hasSymbols(g_var **sh)
{
	char *hasSymbols[] = {"&&", "||", "#", NULL };
	int i = 0, j = 0;

	while (hasSymbols[i])
	{
		for (j = 0; j < (*sh)->num_tokens - 1; j++)
		{
			if (_strcmp((*sh)->tokens[j], hasSymbols[i]) == 0)
			{
				return (1);
			}
		}

		i++;
	}

	return (0);
}
/**
 * process_hsh_sym - check availability and validity of  #symbol
 * @sh: global variables
*/
void process_hsh_sym(g_var **sh)
{
	int pos = 0, i = 0, space = 0, flag = 0, len = 0, j = 1;
	char *temp = NULL;

	while ((*sh)->tokens && (*sh)->tokens[i])
	{
		pos = _strspn((*sh)->tokens[i], "#");

		if (pos == 1)
		{
			flag = 1;
			break;
		}

		len += _strlen((*sh)->tokens[i]);
		space++;
		i++;
	}

	if (flag == 1)
	{
		free((*sh)->buffer);
		(*sh)->buffer = NULL;
		if (len + space == 0)
			return;
		(*sh)->buffer = _calloc(len + space, sizeof(char));
		i = 0;
		j = 1;
		while (j < space)
		{
			temp = _strdup((*sh)->tokens[i]);
			_strcat((*sh)->buffer, temp);
			_strcat((*sh)->buffer, " ");
			free(temp);
			i++;
			j++;
		}
		temp = _strdup((*sh)->tokens[i]);
		_strcat((*sh)->buffer, temp);
		free(temp);
	}
}
/**
 * input_check - checks if command is complete
 * @sh: global variables
 */
void input_check(g_var *sh)
{
	int num = sh->num_tokens - 2;

	if (_strcmp(sh->tokens[num], "||") == 0 ||
			_strcmp(sh->tokens[num], "&&") == 0 ||
			_strcmp(sh->tokens[num], "|") == 0)
	{
		free_arr(&(sh->tokens), sh->num_tokens);
		_puts("> ");
		while (1)
		{
			_getline(&(sh->buffer), &(sh->size), stdin);
			if (is_balanced_quotes(sh->buffer))
			{
				break;
			}
			else
			{
				_puts(">> ");
			}
		}
		sh->num_tokens = tokenize(&(sh->tokens), sh->buffer, " ");
	}
	else
		if (is_balanced_quotes(sh->buffer) == 0)
		{
			_puts("> ");
			while (1)
			{
				_getline(&(sh->buffer), &(sh->size), stdin);
				if (is_balanced_quotes(sh->buffer))
					break;
				_puts("> ");
			}
			return;
		}
		else
		{
			return;
		}
	input_check(sh);
}
/**
 * check_single_quote - Add single quotes to a string if not present.
 * @str: Pointer to the string to check.
 * Return: 1 if modified, 0 if not.
 */
int check_single_quote(char **str)
{
	char *dup = NULL;
	int i = 0, j = 0;

	if (_strchr(*str, '\'') == NULL)
	{
		dup = _calloc(_strlen(*str) + 3, sizeof(char));

		if (dup == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		dup[j] = '\'';
		j++;

		while ((*str)[i] != '\0')
		{
			dup[j] = (*str)[i];
			j++;
			i++;
		}

		dup[j] = '\'';
		dup[j + 1] = '\0';

		*str = dup;
		return (1);
	}

	return (0);
}
