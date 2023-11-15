#include "shell.h"
/**
 * search_alias - Search for an alias and print its value if found.
 * @sh: Pointer to the shell structure.
 * @arg: The alias to search for.
 * Return: 0 if found, 1 otherwise.
 */
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


/**
 * allocate_alias - Allocate memory for aliases.
 * @shell: Pointer to the shell structure.
 * @len: Pointer to the length variable.
 * @old_sz: Pointer to the old size variable.
 * @new_sz: New size for reallocation.
 */
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
		temp = _realloc((*shell)->alias, (*old_sz * sizeof(char *)),
(new_sz * sizeof(char *)));

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
/**
 * update_alias_entry - Update an alias entry with proper formatting.
 * @shell: Pointer to the shell structure.
 * @alias_index: Index of the alias entry to update.
 * @original: Original string before modification.
 * @new_value: New value to be added to the alias entry.
 * Return: 1 on success, 0 on failure.
 */
static int update_alias_entry(g_var **shell, int alias_index, char *original,
char *new_value)
{
	int fr = check_single_quote(&new_value);

	_strcat((*shell)->alias[alias_index], original);
	_strcat((*shell)->alias[alias_index], "=");
	_strcat((*shell)->alias[alias_index], new_value);

	return (fr);
}


/**
 * modify_alias - Modify or add an alias.
 * @shell: Pointer to the shell structure.
 * @arg: The alias argument to modify or add.
 * @old_sz: Pointer to the old size variable.
 * @new_sz: New size for reallocation.
 * Return: Always 0.
 */
static int modify_alias(g_var **shell, char *arg, int *old_sz, int new_sz)
{
	char *str = NULL, *strd = NULL, *cp = NULL;
	int i = 0, len = 0, flag = 0, fr = 0;

	allocate_alias(shell, &len, old_sz, new_sz);
	cp = _strdup(arg);
	str = _strtok(cp, "=");
	strd = _strdup(str);
	for (i = 0; (*shell)->alias[i] != NULL; i++)
	{
		if (_strcmp((*shell)->alias[i], str) == 0)
		{
			free((*shell)->alias[i]);
			(*shell)->alias[i] = NULL;
			str = _strtok(NULL, "=");
			len = _strlen(strd) + _strlen(str);
			(*shell)->alias[i] = _calloc(len + 1, sizeof(char));
			fr = update_alias_entry(shell, i, strd, str);
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		len = _strlen(arg);
		(*shell)->alias[i] = _calloc(len + 3, sizeof(char));
		str = _strtok(NULL, "=");
		fr = update_alias_entry(shell, i, strd, str);
		(*shell)->alias_size++;
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
	return (0);
}

/**
 * _alias - Handle alias command: print, modify, or add aliases.
 * @sh: Pointer to the shell structure.
 * Return: Always 0.
 */
int _alias(g_var **sh)
{
	g_var *shell = *sh;
	char *arg = NULL;
	int j = 1;

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
			modify_alias(sh, arg, &shell->alias_size, shell->alias_size + 1);
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
