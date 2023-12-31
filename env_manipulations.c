#include "shell.h"

/**
 * _add_environment_variable - Add a new environment variable.
 * @sh: Pointer to the shell structure.
 * @env: environment variables
 * @n_tty: create an array of command if ait a non terminal
 * @i: loop tracker
 * Return: 0 on success, 1 on failure.
 */
int _add_environment_variable(g_var **sh, char **env, int *i, char **n_tty)
{
	char *temp = NULL;
	int tokln1 = _strlen(n_tty[1]), tokln2 = _strlen(n_tty[2]);

	if ((*sh)->added_envs >= MAX_ENVS)
		return (1);

	temp = _calloc(tokln1 + tokln2 + 2, sizeof(char));

	if (!temp)
		return (1);

	_strcpy(temp, n_tty[1]);
	_strcat(temp, "=");
	_strcat(temp, n_tty[2]);

	env[*i] = temp;
	(*sh)->pointers[(*sh)->added_envs] = env[*i];
	(*sh)->added_envs++;

	return (0);
}
/**
 * _update_pointers - Updates environment pointers in the current process.
 *
 * @sh: Global variable containing pointers to be updated.
 * @env: Array of environment variables.
 * @i: index of envs
 * @n_tty: create an array of command if ait a non terminal
 * Return:
 * Returns 1 if a new environment variable is added, 0 otherwise.
 */
int _update_pointers(g_var **sh, char **env, int *i, char **n_tty)
{
	size_t old, nw_size;
	int k = 0;
	char *cp, *copy;

	if ((*sh)->pointers == NULL)
	{
		(*sh)->pointers = malloc(sizeof(char *));
	}
	else
	{
		old = sizeof(char *) * ((*sh)->added_envs);
		nw_size = sizeof(char *) * ((*sh)->added_envs + 1);
		(*sh)->pointers = _realloc((*sh)->pointers, old, nw_size);
	}

	while (env[k] != NULL)
		k++;

	while (env[*i] != NULL)
	{
		cp = _strdup(env[*i]);
		copy = _strtok(cp, "=");

		if (_strcmp(n_tty[1], copy) == 0)
		{
			_add_environment_variable(sh, env, i, n_tty);
			free(cp);
			return (1);
		}

		free(cp);
		*i += 1;
	}

	return (0);
}

/**
 * __setenv - it set environment var for the current proccess
 *
 * @sh: global variable containig variable to be set.
 * @tm: array of arguments
 * Return: returns 0 on success and -1 on error
 */
int __setenv(g_var **sh, char **tm)
{
	char **env = environ;
	int i = 0;

	if (tm && _strchr(tm[1], '='))
	{
		return (1);
	}
	if (_update_pointers(sh, env, &i, tm))
	{
	}
	else
	{
		_add_environment_variable(sh, env, &i, tm);
		env[i + 1] = NULL;
	}
	return (0);
}
