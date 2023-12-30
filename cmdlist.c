#include "shell.h"
/**
 * add_node_end - adds node at the end of the list
 * @head: its the head of the lis
 * @str: string data to add
 * @sym: symbol to track
 * Return: returns the pointer to address of the added node
*/
cmd_n_list *add_node_end_sym(cmd_n_list **head, const char *str, char *sym)
{
	char *strd = _strdup((char *)str);
	int len = 0;
	cmd_n_list *temp = malloc(sizeof(cmd_n_list)), *ptr;

	if (temp == NULL)
	{
		return (NULL);
	}

	ptr = *head;

	if (strd == NULL)
		len = 0;
	else
	{
		len = strlen(strd);
	}

	temp->str = strd;
	temp->symbol = sym;
	temp->len = len;
	temp->next = NULL;

	if (ptr == NULL)
	{
		*head = temp;
	}
	else
	{
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		ptr->next = temp;
	}

	return (temp);
}
/**
 * add_node_end - adds node at the end of the list
 * @head: its the head of the lis
 * @str: string data to add
 * Return: returns the pointer to address of the added node
*/
cmd_list *add_node_end(cmd_list **head, const char *str)
{
	char *strd = _strdup((char *)str);
	int len = 0;
	cmd_list *temp = malloc(sizeof(cmd_list)), *ptr;

	if (temp == NULL)
	{
		return (NULL);
	}

	ptr = *head;

	if (strd == NULL)
		len = 0;
	else
	{
		len = _strlen(strd);
	}

	temp->str = strd;
	temp->len = len;
	temp->next = NULL;

	if (ptr == NULL)
	{
		*head = temp;
	}
	else
	{
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		ptr->next = temp;
	}

	return (temp);
}

/**
 * process_sle_command - Process a single command from the command list.
 * @h: Pointer to the command list node.
 * @sh: Pointer to the shell structure.
 * @head: Pointer to the command node list.
 * Return: 1 if a command is processed, 0 otherwise.
 */
static int process_sle_command(const cmd_list *h, g_var *sh, cmd_n_list **head)
{
	free(sh->command);
	sh->command = NULL;
	if (h->str == NULL)
	{
	}
	else
	{
		free_arr(&(sh->tokens), sh->num_tokens);
		sh->command  = _strdup(h->str);
		remove_emptyspaces(&(sh->command));
		sh->num_tokens = tokenize(&(sh->tokens), sh->command, " ");
		if (hasSymbols(&sh))
		{
			check_symbols(&sh, head);
			process_cmd_symbols(*head, sh);
			free_listint_safe(head);
			cleanup_and_free_tokens(sh);
			return (1);
		}
		if (get_built_in(sh, (sh->tokens)[0]))
		{
			get_built_in(sh, (sh->tokens)[0])(&sh);
			cleanup_and_free_tokens(sh);
			return (1);
		}
		free(sh->command);
		sh->command = check_cmd_exist(sh->tokens[0]);
		if (sh->command)
		{
			execute(sh, sh->tokens,  sh->environs);
			cleanup_and_free_tokens(sh);
			return (1);
		}
		else
		{
			not_found(sh, sh->prog_name, (sh->tokens)[0], sh->process_id, "not found");
		}
		cleanup_and_free_tokens(sh);
	}
	return (0);
}

/**
 * process_commands - Process commands from the command list.
 * @h: Pointer to the command list.
 * @sh: Pointer to the shell structure.
 * @head: Pointer to the command node list.
 * Return: Number of nodes processed.
 */
size_t process_commands(const cmd_list *h, g_var *sh, cmd_n_list **head)
{
	size_t nodes = 0;

	while (h != NULL)
	{
		if (process_sle_command(h, sh, head))
		{
			h = h->next;
			nodes++;
			continue;
		}
		h = h->next;
		nodes++;
	}
	return (nodes);
}
