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
/**
 * _unsetenv_p - it Remove environment var for the current proccess
 *
 * @str: string to be unset.
 * @env: evironment variables
 * Return: return 0 if success and -1 if faild
 */
int _unsetenv_p(char *str, char **env)
{
	char *copy = NULL, *cp;
	int i = 0, j = 0, k = 0;

	if (str == NULL)
		return (1);
	while (env[k] != NULL)
		k++;
	while (env[i] != NULL)
	{
		cp = _strdup(env[i]);
		copy = _strtok(cp, "=");
		if (_strcmp(str, copy) == 0)
		{
			env[i] = NULL;
			j = i;
			free(cp);
			break;
		}
		free(cp);
		i++;
	}
	while (j < k)
	{
		env[j] = env[j + 1];
		j++;
	}
	return (0);
}
