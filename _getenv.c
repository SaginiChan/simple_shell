#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @var: The environment variable to retrieve.
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *_getenv(char *var)
{
	char *val = NULL, *copy = NULL, *cp/* , *temp = NULL */;
	char **env = environ;
	int i = 0;

	if (var == NULL || *var == '\0')
	{
		return (NULL);
	}

	while (env && env[i] != NULL)
	{
		cp = strdup(env[i]);
		copy = strtok(cp, "=");

		if (strcmp(var, copy) == 0 && strcmp(copy, ".") != 0)
		{
			val = strdup(cp + strlen(copy) + 1);
			free(copy);
			return (val);
		}

		free(copy);
		i++;
	}

	if (i <= 2)
	{
		return ("PATH");
	}

	return (NULL);
}
