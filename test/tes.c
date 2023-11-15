#include "shell.h"

/**
 * _echo - Display a message with variable substitution.
 * @sh: Pointer to the shell structure.
 * Return: 0 on success, 1 on failure.
 */
int _echo(g_var **sh)
{
	int int_ln = int_len((*sh)->status_code);
	int i = 0, pi_ln = 0;
	int len2 = strlen((*sh)->tokens[0]) + 1, count = 0;
	char *status = NULL, *buf = NULL, *str = NULL;
	pid_t pid = getpid();

	if (!(*sh)->command)
		return (1);
	remove_emptyspaces(&((*sh)->command));
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
		if ((*sh)->command[len2 + i] == '$')
		{
			if ((*sh)->command[len2 + i + 1] == '?')
			{
				status = int_str(status, (*sh)->status_code, int_ln);
				_strcat(buf, status);
				i += 2;
			}
			else
				if ((*sh)->command[len2 + i + 1] == '$')
				{
					status = int_str(status, pid, pi_ln);
					_strcat(buf, status);
					i += 2;
				}
				else
					buf[i] = (*sh)->command[len2 + i];
		}
		else
			buf[i] = (*sh)->command[len2 + i];
		free(status);
		status = NULL;
	}
	if (write(1, buf, _strlen(buf)) == -1)
		handle_error("Error writing to stdout");
	_puts("\n");
	free(buf);
	free(str);
	return (0);
}

int search_alias(g_var *sh, char *arg)
{
	int i = 0;
	char *str = NULL;

	while (sh->alias && sh->alias[i] != NULL)
	{
		str = _strdup(sh->alias[i]);
		str = _strtok(str, "=");

		if (_strcmp(str, arg))
		{
			_puts(sh->alias[i]);
			_puts("\n");
			return (0);
		}

		free(str);
		i++;
	}

	return (1);
}
int print_alias(g_var *sh)
{
	int i = 0;

	while (i < sh->alias_size)
	{
		_puts(sh->alias[i]);
		_puts("\n");
		i++;
	}

	return (0);
}
void allocate_alias(g_var **shell, int *len, int *old_sz, int new_sz)
{
	char **temp = NULL;

	if ((*shell)->alias == NULL)
	{
		*len = (*shell)->num_tokens;
		(*shell)->alias = _calloc(*len + 1, sizeof(char *));

		if ((*shell)->alias == NULL)
		{
			perror("calloc failed");
		}
	}
	else
	{
		temp = _realloc((*shell)->alias, *old_sz * sizeof(char *),
		                new_sz * sizeof(char *));

		if (temp  == NULL)
		{
			perror("realloc failed");
		}
		else
		{
			(*shell)->alias = temp;
		}
	}
}
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

		/* free(*str); */
		*str = dup;
		return (1);
	}

	return (0);
}
int _alias(g_var **sh)
{
	char *arg = NULL, *str = NULL, *strd = NULL, *cp = NULL;
	int i = 0, j = 1, len = 0, flag = 0, fr = 0;
	g_var *shell = *sh;
	int *old_sz = &shell->alias_size, new_sz = shell->alias_size + 1;

	if (shell->num_tokens == 2)
	{
		print_alias(*sh);
		return (0);
	}

	while (j < shell->num_tokens && shell->tokens[j])
	{
		arg = shell->tokens[j];

		if (_strchr(arg, '=') != NULL)
		{
			allocate_alias(&shell, &len, old_sz, new_sz);
			cp = _strdup(arg);
			str = _strtok(cp, "=");
			strd = _strdup(str);
			i = 0;

			while (shell->alias[i] != NULL)
			{
				if (_strcmp(shell->alias[i], str) == 0)
				{
					free(shell->alias[i]);
					shell->alias[i] = NULL;
					str = _strtok(NULL, "=");
					len = _strlen(strd) + _strlen(str);
					shell->alias[i] = _calloc(len + 1, sizeof(char));
					fr = check_single_quote(&str);
					_strcat(shell->alias[i], strd);
					_strcat(shell->alias[i], "=");
					_strcat(shell->alias[i], str);
					flag = 1;
					break;
				}

				i++;
			}

			if (flag == 0)
			{
				len = _strlen(shell->tokens[j]);
				shell->alias[i] = _calloc(len + 3, sizeof(char));
				str = _strtok(NULL, "=");
				fr = check_single_quote(&str);
				_strcat(shell->alias[i], strd);
				_strcat(shell->alias[i], "=");
				_strcat(shell->alias[i], str);
				shell->alias_size++;
			}

			if (fr == 1)
			{
				free(str);
				str = NULL;
			}

			free(cp);
			cp = NULL;
			free(strd);
			strd = NULL;
		}
		else
			if (search_alias(shell, shell->tokens[j]) == 1)
			{
				_puts("alias: ");
				_puts(arg);
				_puts(" not found");
				_puts("\n");
			}

		j++;

	}

	return (0);
}