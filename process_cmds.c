#include "shell.h"
/**
 * process_command_node - Process a command node in the linked list.
 * @h: Pointer to the command node in the linked list.
 * @sh: Pointer to the shell structure.
 * @nds: Pointer to the variable tracking the number of processed nodes.
 * @flag: Pointer to the flag indicating logical AND condition.
 * Return: 1 if a command node is processed, 0 otherwise.
 */
int process_command_node(const cmd_n_list **h, g_var *sh, int *nds, int *flag)
{
	if (*h == NULL)
		return (0);

	free_arr(&(sh->tokens), sh->num_tokens);
	free(sh->command);
	sh->command = _strdup((*h)->str);
	remove_emptyspaces(&sh->command);
	sh->num_tokens = tokenize(&(sh->tokens), sh->command, " ");

	if (get_built_in(sh, (sh->tokens)[0]))
	{
		get_built_in(sh, (sh->tokens)[0])(&sh);
		cleanup_and_free_tokens(sh);
		*flag = 1;
		return (1);
	}

	sh->command = check_cmd_exist(sh->tokens[0]);

	if (sh->command)
	{
		if (!hasSymbols(&sh))
		{
			execute(sh, sh->tokens, sh->environs);
			*h = (*h)->next;
			(*nds)++;
			*flag = 1;
			return (1);
		}
	}
	else
	{
		not_found(sh->prog_name, (sh->tokens)[0], sh->process_id, "not found");
	}

	cleanup_and_free_tokens(sh);
	*flag = 1;

	return (1);
}

/**
 * process_logical_and - Process logical AND symbol.
 * @h: Pointer to the command node in the linked list.
 * @nodes: Pointer to the variable tracking the number of processed nodes.
 * @flag: Pointer to the flag indicating logical AND condition.
 */
static void process_logical_and(const cmd_n_list **h,  int *nodes,
int *flag)
{
	*h = (*h)->next;
	(*nodes)++;
	*flag = 0;
}
/**
 * process_cmd_symbols - Process command symbols in the linked list.
 * @h: Pointer to the command node in the linked list.
 * @sh: Pointer to the shell structure.
 * Return: Number of processed nodes.
 */
size_t process_cmd_symbols(const cmd_n_list *h, g_var *sh)
{
	int nodes = 0, flag = 0;

	free(sh->command);
	sh->command = NULL;

	while (h != NULL)
	{
		if (h->symbol == NULL)
			return (nodes);

		if (_strcmp(h->symbol, "&&") == 0 && flag == 1)
		{
			process_logical_and(&h, &nodes, &flag);
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
				break;
			}
		}

		if (h == NULL)
		{
			break;
		}
		else if (process_command_node(&h, sh, &nodes, &flag))
			continue;
		nodes++;
	}
	free(sh->command);
	sh->command = NULL;
	return (nodes);
}
