#include "shell.h"


/**
 * check_semicolon - it checks if colon exists if
 *                   exists breaks the command into list
 * @sh: global variable in struct
 * @head: head of the list;
 *
 * Return: return 1 if semicolon found and 0 otherwise
*/
int check_semicolon(g_var **sh, cmd_list **head)
{
	int i = 0, flg = 0;
	char *str = NULL, *strd = NULL;


	while ((*sh)->buffer && (*sh)->buffer[i])
	{
		if ((*sh)->buffer[i] == ';')
		{
			flg = 1;
			break;
		}

		i++;

	}

	if (flg == 1)
	{
		strd = _strdup((*sh)->buffer);
		str = _strtok(strd, ";");

		while (str)
		{
			add_node_end(head, str);
			str = _strtok(NULL, ";");
		}

		free(strd);
		return (1);
	}
	else
	{
		return (0);
	}

}
/**
 * get_built_in - selects the correct function to perform
 *               the operation aske by the user
 * @shell: struct containing lobal variabkes
 * @str: string to be searched
 * Return: returns a pointer to the function foun
 *         returns NULL if not found
 */
int (*get_built_in(g_var *shell, char *str))(g_var **shell)
{
	built_ins builtis[] = {
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"exit", exiting},
		{"env", _printenv},
		{"echo", _echo},
		{"/bin/echo", _echo},
		{"alias", _alias},
		{"cd", _cd},
		{NULL, NULL}
	};
	int i = 0;

	if (shell->buffer)
	{
	}


	while (builtis[i].str != NULL)
	{

		if (_strcmp(builtis[i].str, str) == 0)
		{
			return (builtis[i].f);
		}

		i++;
	}

	return (NULL);
}

/**
 * check_symbols - it checks if symbol exists if
 *                   exists breaks the command into list
 * @sh: global variable in struct
 * @head: head of the list;
 *
*/
void check_symbols(g_var **sh, cmd_n_list **head)
{
	int i = 0, j = 0;
	char *buf = malloc(sizeof(char) * _strlen((*sh)->command)  + 1);

	_memset(buf, 0, _strlen((*sh)->command));
	while ((*sh)->command && (*sh)->command[i])
	{
		if ((*sh)->command[i] == '|' && (*sh)->command[i + 1] == '|')
		{
			add_node_end_sym(head, buf, "||");
			free(buf);
			buf = NULL;
			buf = malloc(sizeof(char) * _strlen((*sh)->command)  + 1);
			_memset(buf, 0, _strlen((*sh)->command));
			j = 0;
			i++;
		}
		else
			if ((*sh)->command[i] == '&' && (*sh)->command[i + 1] == '&')
			{
				add_node_end_sym(head, buf, "&&");
				free(buf);
				buf = NULL;
				buf = malloc(sizeof(char) * _strlen((*sh)->command)  + 1);
				_memset(buf, 0, _strlen((*sh)->command));
				j = 0;
				i++;
			}
			else
			{
				buf[j] = (*sh)->command[i];

				j++;
			}
		i++;
	}
	if (buf != NULL)
	{
		add_node_end_sym(head, buf, NULL);
	}
	free(buf);
}
/**
 * check_semicolon_tk - it checks if colon exists if
 *                   exists breaks the command into list
 * @string: string in struct
 * @head: head of the list;
 *
 * Return: return 1 if semicolon found and 0 otherwise
*/
int check_semicolon_tk(char *string, cmd_list **head)
{
	int i = 0, flg = 0;
	char *str = NULL, *strd = NULL;

	while (string && string[i])
	{
		if (string[i] == ';')
		{
			flg = 1;
			break;
		}

		i++;
	}

	if (flg == 1)
	{
		strd = strdup(string);
		str = _strtok(strd, ";");

		while (str)
		{
			if (strcmp(str, "") != 0)
				add_node_end(head, str);
			str = _strtok(NULL, ";");
		}

		free(strd);
		return (1);
	}
	else
		return (0);
}
