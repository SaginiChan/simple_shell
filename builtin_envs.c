#include "shell.h"
/**
 * add_environment_variable - Add a new environment variable.
 * @sh: Pointer to the shell structure.
 * @env: environment variables
 * @n_tty: create an array of command if ait a non terminal
 * @i: loop tracker
 * Return: 0 on success, 1 on failure.
 */
int add_environment_variable(g_var **sh, char **env, int *i, char **n_tty)
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
 * update_pointers - Updates environment pointers in the current process.
 *
 * @sh: Global variable containing pointers to be updated.
 * @env: Array of environment variables.
 * @i: index of envs
 * @n_tty: create an array of command if ait a non terminal
 * Return:
 * Returns 1 if a new environment variable is added, 0 otherwise.
 */
int update_pointers(g_var **sh, char **env, int *i, char **n_tty)
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
			add_environment_variable(sh, env, i, n_tty);
			free(cp);
			return (1);
		}

		free(cp);
		*i += 1;
	}

	return (0);
}

/**
 * _setenv - it set environment var for the current proccess
 *
 * @sh: global variable containig variable to be set.
 * Return: returns 0 on success and -1 on error
 */
int _setenv(g_var **sh)
{
	char **env = (*sh)->environs, **n_tty = NULL, *rep = NULL;
	int i = 0;
	int n_tlen = 0;

	if ((*sh)->fl_pip == 2)
		return (5);
	if (isatty(STDIN_FILENO))
	{
		rep = (*sh)->tokens[1];
		n_tlen = (*sh)->num_tokens;
		n_tty = (*sh)->tokens;
	}
	else
	{
		n_tlen = tokenize(&n_tty, (*sh)->command, " ");
		rep = _strdup(n_tty[1]);
	}
	if ((n_tlen - 1) <= 2)
	{
		free_arr(&n_tty, n_tlen);
		free(rep);
		return (1);
	}
	if (rep && _strchr(rep, '='))
	{
		free_arr(&n_tty, n_tlen);
		free(rep);
		return (1);
	}
	if (update_pointers(sh, env, &i, n_tty))
	{
	}
	else
	{
		add_environment_variable(sh, env, &i, n_tty);
		env[i + 1] = NULL;
	}
		free_arr(&n_tty, n_tlen);
		free(rep);
	return (0);
}


/**
 * _unsetenv - it Remove environment var for the current proccess
 *
 * @sh: gloabal variables.
 * Return: return 0 if success and -1 if faild
 */
int _unsetenv(g_var **sh)
{
	char *copy = NULL, *cp;
	char **env = (*sh)->environs;
	int i = 0, j = 0, k = 0;

	if ((*sh)->fl_pip)
	{
		return (6);
	}

	if ((*sh)->tokens[1] == NULL)
		return (1);

	if (str_contains((*sh)->tokens[1], '='))
		return (1);
	while (env[k] != NULL)
		k++;
	while (env[i] != NULL)
	{
		cp = _strdup(env[i]);
		copy = _strtok(cp, "=");
		if (_strcmp((*sh)->tokens[1], copy) == 0)
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
/**
 * _printenv - Gets the value of an environment variable.
 * @sh: The global environment variable to retrieve.
 * Return: 0 if succes , -1 otherwise.
 */
int _printenv(g_var **sh)
{
	char **env = (*sh)->environs;
	int i = 0;

	if ((*sh)->fl_pip == 2)
	{
		return (4);
	}

	if (env == NULL)
	{
		return (1);
	}

	while (env[i] != NULL)
	{
		remove_emptyspaces(&env[i]);
		if (strcmp(env[i], "") != 0)
		{
			printf("%s\n", env[i]);
		}
		/* _puts("\n"); */
		i++;
	}

	return (0);
}
