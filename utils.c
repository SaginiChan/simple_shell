#include "shell.h"
#include <stdbool.h>
/**
 * remove_spaces - remove all white spaces
 * @string: string to remove white spaces
 *
*/
void remove_spaces(char *string)
{

	int length = strlen(string);
	int j = 0, i = 0;

	for (; i < length; i++)
	{
		if (string[i] != ' ')
		{
			string[j] = string[i];
			j++;
		}
	}

	string[j] = '\0';
}

/**
 * remove_extra_spaces - remove extra white spaces
 * @str: string to remove white spaces
 *
*/
void remove_extra_spaces(char **str)
{
	int length = strlen(*str), i = 0, j = 0;
	bool last_char_not_space = true;

	for (i = 0; i < length; i++)
	{
		if ((*str)[i] != ' ' || last_char_not_space)
		{
			(*str)[j] = (*str)[i];
			j++;
		}

		if ((*str)[i] == ' ')
			last_char_not_space = false;
		else
			last_char_not_space = true;
	}

	(*str)[j] = '\0';
}

/**
 * _isprint - checks for non printable characters
 * @c: character to be checked
 * @sh: gloabal variables
 * Return: returns 1 if true 0 if false
*/
int _isprint(g_var **sh, char *c)
{
	int count = 0;

	remove_extra_spaces(&c);

	while (c[count] == ' ' ||
			c[count] == '\t')
		count++;

	if (count > 0)
	{
		remove_spaces(c);
	}


	if (_strlen(c) <= 1)
	{
		if ((*sh)->nread == 0 && _strcmp(((*sh)->buffer), "") == 0)
			control_d(*sh);

		if (_strcmp(((*sh)->buffer), "\n") == 0)
		{
			free(((*sh)->buffer));
			((*sh)->buffer) = NULL;
			return (1);
		}


	}
	else
	{
		return (0);
	}

	return (*c >= 0x20 && *c <= 0x7E);
}

/**
 * remove_emptyspaces - remove white spaces
 * @str: string to remove white spaces
 *
*/
void remove_emptyspaces(char **str)
{
	int i = strlen(*str) - 1, count = 0;

	while (i >= 0)
	{
		if ((*str)[i] == ' ' || (*str)[i] == '\n' ||
				(*str)[i] == '\t')
			i--;
		else
			break;
	}

	(*str)[i + 1] = '\0';

	while ((*str)[count] == ' ' ||
			(*str)[count] == '\n' ||
			(*str)[count] == '\t')
		count++;

	if (count != 0)
	{
		i = 0;

		while ((*str)[i + count] != '\0')
		{
			(*str)[i] = (*str)[i + count];
			i++;
		}

		(*str)[i] = '\0';
	}

	remove_extra_spaces(str);
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
