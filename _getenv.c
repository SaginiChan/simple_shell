#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @var: The environment variable to retrieve.
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *_getenv(char *var)
{
	char *val = NULL, *copy = NULL, *cp, temp[120] = {0};
	char **env = environ;
	int i = 0;

	if (var == NULL || *var == '\0')
	{
		return (NULL);
	}

	while (env[i] != NULL)
	{
		cp = _strdup(env[i]);
		copy = _strtok(cp, "=");

		if (_strcmp(var, copy) == 0)
		{
			val = _strdup((cp + _strlen(copy) + 1));
			free(cp);
			_strcpy(temp, val);
			return (val);
		}

		free(cp);
		cp = NULL;
		i++;
	}

	return (NULL);
}
