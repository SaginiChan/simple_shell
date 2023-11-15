int (*get_built_in(g_var *shell, char *str))(g_var **)
{
    pid_t child;

    built_ins builtins[] = {
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"exit", exiting},
        {"env", _printenv},
        {"echo", _echo},
        {"alias", _alias},
        {"cd", _cd},
        {NULL, NULL}
    };

    int i = 0;

    // Check if the buffer exists or any other necessary conditions
    // You might want to add more meaningful conditions here if needed

    while (builtins[i].str != NULL)
    {
        if (_strcmp(builtins[i].str, str) == 0)
        {
            child = fork();

            if (child == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (child == 0)
            {
                // This is the child process

                if (builtins[i].f != NULL)
                {
                    // Execute the built-in command
                    builtins[i].f(&shell);

                    // If the command doesn't return, exit the child process
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    // The function pointer is NULL; this might be an error
                    fprintf(stderr, "Error: %s command not found\n", str);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // This is the parent process

                // Wait for the child process to complete
                wait(&(shell->exit_status));

                // Increment the process_id
                (shell->process_id)++;

                // Return the function pointer of the executed built-in command
                return (builtins[i].f);
            }
        }
        i++;
    }

    return NULL; // Command not found
}
int (*get_built_in(g_var *shell, char *str))(g_var **shell)
{
    pid_t child = getpid();
    	built_ins builtis[] = {
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"exit", exiting},
        {"env", _printenv},
		{"echo", _echo},
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
            child = fork();

            if (child == 0)
            {
                if ((builtis[i].f) != NULL)
                {
                    (shell->process_id)++;
                    perror(builtis[i].str);
                    exit(errno);
                }
                else
                {
                    exit(EXIT_SUCCESS);
                }
                
            }
            else
            {
                wait(&(shell->exit_status));
                (shell->process_id)++;
                return ((builtis[i].f));
            }
		}
        i++;
	}

	return (NULL);
}
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int _echo(g_var **sh)
{
	char *buf = NULL, *status = NULL;
    int i = 0, len = 0, len2 = 0;
    
	if ((*sh)->command)
	{
		len = _strlen((*sh)->command);
		len2 = _strlen((*sh)->tokens[0]);
		buf = malloc(sizeof(char) * len + 1);
		_memset(buf, 0, len);
	}
	else
	{
		errno = EINVAL;
		return (1);
	}
    while ((*sh)->command[len2 + i])
    {
            if ((*sh)->command[len2 + i] == '$' && (*sh)->command[len2 + i + 1] == '?')
            {
				status = _calloc(10, sizeof(char));
				status = str_buff(&status, (*sh)->exit_status, int_len((*sh)->exit_status));
				_strcat(buf, status);
				i = _strlen(buf);
				len2 += 2;
				continue; 
            }else if ((*sh)->command[len2 + i] == '$' && (*sh)->command[len2 + i + 1] == '$')
            {
				_strcat(buf, "REPLACE2");
				i = _strlen(buf);
				len2 += 2;
				continue;
            }
			else
			{
				buf[i] = (*sh)->command[len2 + i];
			}
			
        i++;
    }
	write(1, buf, _strlen(buf));
	_puts("\n");
	free(buf);
	free(status);
	return (0);

}
/**
 * process_commands - prints contents of the list
 * @head: poiter to the first node cmd list colons
 * @h: poiter to the first node cmd list symbols
 * @sh: gloabal variables
 * Return: returns number of nodes in the lis
 *
*/
size_t process_commands(const cmd_list *h, g_var *sh, cmd_n_list **head)
{
	int nodes = 0;

	while (h != NULL)
	{
		if (h->str == NULL)
		{
			printf("[0] %s\n", "nil");
		}
		else
		{
			free_arr(&(sh->tokens), sh->num_tokens);
			free(sh->command);
			sh->command  = _strdup(h->str);
			remove_emptyspaces(&(sh->command));
			sh->num_tokens = tokenize(&(sh->tokens), sh->command, " ");
			if (hasSymbols(&sh))
			{

				check_symbols(&sh, head);
				process_cmd_symbols(*head, sh);
				free_listint_safe(head);
				(sh->process_id)++;
				free_arr(&(sh->tokens), sh->num_tokens);
				free(sh->command);
				sh->command = NULL;
				cleanup(sh);
				h = h->next;
				nodes++;
				continue;

			}
			if (get_built_in(sh, (sh->tokens)[0]))
			{
				get_built_in(sh, (sh->tokens)[0])(&sh);
				(sh->process_id)++;
				free_arr(&(sh->tokens), sh->num_tokens);
				free(sh->command);
				sh->command = NULL;
				cleanup(sh);
				h = h->next;
				nodes++;
				continue;
			}
			free(sh->command);
			sh->command = NULL;
			sh->command = check_cmd_exist(sh->tokens[0]);
			if (sh->command)
			{
				execute(sh, sh->tokens,  sh->environs);
				h = h->next;
				nodes++;
				continue;
			}
			else
			{
				not_found(sh->prog_name, (sh->tokens)[0], sh->process_id, "not found");
				(sh->process_id)++;
			}
			free_arr(&(sh->tokens), sh->num_tokens);
			cleanup(sh);
		}
		h = h->next;
		nodes++;
	}
	return (nodes);
}
size_t process_cmd_symbols(const cmd_n_list *h, g_var *sh)
{
	int nodes = 0, flag = 0;

	while (h != NULL)
	{
		if (h->symbol == NULL)
			return (nodes);
		if (_strcmp(h->symbol, "&&") == 0 && flag == 1)
		{
			h = h->next;
			nodes++;/* flag = 0 */
			flag = 0;
		}
		while (h != NULL && flag == 1)
		{
			if (h->next->symbol == NULL && _strcmp(h->symbol, "||") == 0)
				return (nodes);
			if (_strcmp(h->symbol, "||") == 0)
				h = h->next;
			else
			{
				h = h->next;
				break;/* add h = h->next */
			}
		}
		if (h == NULL)
			break;
		else
		{
			free_arr(&(sh->tokens), sh->num_tokens);
			free(sh->command);
			sh->command  = _strdup(h->str);
			remove_emptyspaces(&sh->command);
			sh->num_tokens = tokenize(&(sh->tokens), sh->command, " ");
			if (get_built_in(sh, (sh->tokens)[0]))
			{
				get_built_in(sh, (sh->tokens)[0])(&sh);
				(sh->process_id)++;
				free_arr(&(sh->tokens), sh->num_tokens);
				free(sh->command);
				sh->command = NULL;
				flag = 1;
				continue;
			}
			if (sh->command != NULL)
			{
				free(sh->command);
				sh->command = NULL;
			}
			sh->command = check_cmd_exist(sh->tokens[0]);
			if (sh->command)
			{
				if (!hasSymbols(&sh))
				{
					execute(sh, sh->tokens,  sh->environs);
					h = h->next;
					nodes++;
					flag = 1;
					free(sh->command);
					sh->command = NULL;
					continue;
				}
			}
			else
			{
				not_found(sh->prog_name, (sh->tokens)[0], sh->process_id, "not found");
				(sh->process_id)++;
				free(sh->command);
				sh->command = NULL;
			}
			free_arr(&(sh->tokens), sh->num_tokens);
			cleanup(sh);
			flag = 1;
		}
		nodes++;
	}
	return (nodes);
}