#include "shell.h"
#include <stdbool.h>
#include <ctype.h>

/**
 * _isspace - Custom implementation of isspace function
 * @c: The character to check for white-space
 *
 * Return: true if the character is white-space, false otherwise.
 */
bool _isspace(char c)
{
	return (c == ' ');
}
/**
 * remove_spaces - remove all white spaces
 * @string: string to remove white spaces
 *
*/
void remove_spaces(char *string)
{

	int length = _strlen(string);
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
 * @input: string to remove white spaces
 *
*/
void remove_extra_spaces(char *input)
{
	char *output = input;
	int isSpace = 0;

	while (input && *input)
	{
		if (_isspace(*input))
		{
			if (!isSpace)
			{
				*output++ = ' ';
				isSpace = 1;
			}
		}
		else
		{
			*output++ = *input;
			isSpace = 0;
		}

		input++;
	}

	if (output)
	{
		*output = '\0';
	}

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


	while (c[count] == ' ' || c[count] == '\t')
	{
		if (c[count] == ' ' ||
				c[count] == '\t')
			count++;
		else
			break;
	}
	if (count > 0 && (*sh)->mode == 1)
	{
		remove_spaces(c);
	}
	if (_strlen(c) <= 1)
	{
		if (((*sh)->nread == -1 || (*sh)->nread == 0) &&
				_strcmp(((*sh)->buffer), "") == 0)
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
	int i = 0, count = 0;

	if (*str)
	{
		i = _strlen(*str) - 1;
	}


	while (i >= 0)
	{
		if ((*str) && ((*str)[i] == ' ' ||
					(*str)[i] == '\t'))
			i--;
		else
			break;
	}

	if ((*str))
	{
		(*str)[i + 1] = '\0';
	}


	while ((*str) && ((*str)[count] == ' ' ||
				(*str)[count] == '\t'))
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
	remove_extra_spaces(*str);
}
