#include "shell.h"

/**
 * _set - it set environment var for the current proccess
 * @sh: set of gloabl variables
 * @var:  to be set.
 * @val: value to set
 * Return: returns 0 on success and -1 on error
 */
int _set(g_var **sh, char *var, char *val)
{
	char *copy = NULL, *cp = NULL, *temp = NULL, **env = environ;
	int i = 0, k = 0, len = 0, old = 0, nw_size = 0;

	if (str_contains(val, '='))
	{
		usage_err("Usage: setenv VARIABLE VALUE");
		return (-1);
	}

	if ((*sh)->pointers ==  NULL)
		(*sh)->pointers = malloc(sizeof(char *) * 1);
	else
	{
		old = (sizeof(char *) * ((*sh)->added_envs));
		nw_size = (sizeof(char *) * ((*sh)->added_envs + 1));
		(*sh)->pointers = _realloc((*sh)->pointers, old, nw_size);
	}
	len = _strlen(var) + _strlen(val);
	temp = malloc(sizeof(char) * len + 2);
	while (env[k] != NULL)
		k++;
	while (env[i] != NULL)
	{
		cp = _strdup(env[i]);
		copy = _strtok(cp, "=");
		if (_strcmp(var, copy) == 0)
		{
			_strcpy(temp, var);
			_strcat(temp, "=");
			env[i] = _strcat(temp, val);
			(*sh)->pointers[(*sh)->added_envs] = env[i];
			(*sh)->added_envs++;
			free(cp);
			return (0);
		}
		free(cp);
		i++;
	}
	free(temp);
	return (1);
}
/**
 * check_sm - Print an error message and exit.
 * @sh: set of global variables
 * @status: status char to be saved
 * @ln: length of int passed
 * @buf: buffer to be updated
 * @i: tracks the position of the loop
 * @len2: length of the toke 2
 */
void check_sm(g_var **sh, char *status, int ln, char *buf, int *i, int len2)
{
	int pi_ln = 0;
	pid_t pid = getpid();

	pi_ln = int_len(pid);

	if ((*sh)->command[len2 + *i] == '$')
	{
		if ((*sh)->command[len2 + *i + 1] == '?')
		{
			status = int_str(status, (*sh)->status_code, ln);
			_strcat(buf, status);
			*i += 2;
		}
		else
			if ((*sh)->command[len2 + *i + 1] == '$')
			{
				status = int_str(status, pid, pi_ln);
				_strcat(buf, status);
				*i += 2;
			}
			else
				buf[*i] = (*sh)->command[len2 + *i];
	}
	else
		buf[*i] = (*sh)->command[len2 + *i];
}
/**
 * _echo - Display a message with variable substitution.
 * @sh: Pointer to the shell structure.
 * Return: 0 on success, 1 on failure.
 */
int _echo(g_var **sh)
{
	int int_ln = int_len((*sh)->status_code), i = 0, pi_ln = 0;
	int len2 = strlen((*sh)->tokens[0]) + 1, count = 0, n_tm = 0;
	char *status = NULL, *buf = NULL, *str = NULL, **tmp = NULL;
	pid_t pid = getpid();

	if ((*sh)->fl_pip == 2)
	{
		return (2);
	}

	if (!(*sh)->command)
		return (1);

	n_tm = tokenize(&tmp, (*sh)->command, " ");
	len2  = _strlen(tmp[0]) + 1;

	while ((*sh)->command[len2 + count])
		count++;

	pi_ln = int_len(pid);
	buf = _calloc((pi_ln + count + int_ln + 1), sizeof(char));
	str = _calloc(_strlen((*sh)->command) + 2, sizeof(char));
	_strcpy(str, (*sh)->command);

	if (!buf)
		handle_error("Error allocating memory");

	for (i = 0; str[len2 + i] != '\0'; ++i)
	{
		status = _calloc(pi_ln + int_ln + 1, sizeof(char));
		check_sm(sh, status, int_ln, buf, &i, len2);
		free(status);
		status = NULL;
	}
	proces_buf(sh, buf);
	_puts("\n");
	free_arr(&tmp, n_tm);
	free(buf);
	free(str);
	return (0);
}
/**
 * check_file_permissions - Check file permissions and handle error if needed.
 * @arg: directory path
 * @sh:  gloabl variables
 * Return: Returns 1 if there's an error, 0 otherwise.
 */
int check_file_permissions(const char *arg, g_var **sh)
{
	struct stat fs;
	char buf[BUFSIZ];
	int r  = 0;

	r = stat(arg, &fs);
	if (r == -1)
	{
		fprintf(stderr, "File error\n");
		return (2);
	}
	if (stat(arg, &fs) == -1)
	{
		perror("stat");
		return (1);
	}

	if (!(fs.st_mode & S_IRUSR) ||
	!(fs.st_mode & S_IWUSR) || (fs.st_mode & S_IXUSR))
	{
		_strcat(buf, (*sh)->prog_name);
		_strcat(buf, ": ");
		_strcat(buf, "1:");
		_strcat(buf, "cd ");
		_strcat(buf, "can't cd to ");
		write(STDERR_FILENO, buf, _strlen(buf));
		return (1);
	}

	return (0);
}

/**
 * _cd - Change the current working directory.
 * @sh: A pointer to the global variables structure
 *      containing the command tokens
 * and environment variables.
 *
 * Return: 0 on success, -1 on failure.
 */
int _cd(g_var **sh)
{
	char *arg = NULL, cwd[120] = {0};
	DIR *dir = NULL;

	if ((*sh)->fl_pip == 2)
	{
		return (7);
	}

	if ((*sh)->num_tokens > 3)
		return (0);
	getcwd(cwd, 120);
	arg = (*sh)->tokens[1];
	if ((*sh)->num_tokens == 2 || (arg && arg[0] == '\0'))
		arg = getenv("HOME");
	else if (_strcmp(arg, "-") == 0)
	{
		arg = getenv("OLDPWD");
		if (arg == NULL || arg[0] == '\0')
			arg = getenv("HOME");
	}
	dir = opendir(arg);
	if (dir == NULL)
		return (1);
	if (check_file_permissions(arg, sh))
		return (1);
	if (chdir(arg) == -1)
	{
		perror("chdir");
		closedir(dir);
		return (1);
	}
	else
	{
		_set(sh, "OLDPLW", cwd);
		_set(sh, "PWD", arg);
	}
	closedir(dir);
	return (0);
}
