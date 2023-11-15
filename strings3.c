#include "shell.h"

/**
 * str_contains - checks if a character is contained in a variable
 *
 * @str: the striing to inspect.
 * @ch: the character being ispected.
 *
 * Return: returns true if char found and false if not found.
 *
 */
int str_contains(char *str, char ch)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == ch)
		{
			return (1);
		}

		i++;
	}

	return (0);
}
