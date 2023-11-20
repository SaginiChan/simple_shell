#include "shell.h"
/**
 * process_special_cases1 - Process special cases in user input.
 * @sh: Pointer to the shell structure.
 * @h: pointer to list of commands with symbols
 * @head: Pointer to the command list head.
 * Return: returns 1 if one of the proces is passed 0 if not;
 */
int process_special_cases1(g_var **sh, cmd_list **head, cmd_n_list **h)
{

	if (check_semicolon(sh, head))
	{
		process_commands(*head, *sh, h);
		((*sh)->process_id)++;
		free_list_cmd(head);
		(*sh)->command = NULL;
		cleanup(*sh);
		exit(1);
	}

	if (hasSymbols(sh))
	{
		(*sh)->command = _strdup((*sh)->buffer);
		check_symbols(sh, h);
		process_cmd_symbols(*h, *sh);
		((*sh)->process_id)++;
		free_listint_safe(h);
		(*sh)->command = NULL;
		cleanup(*sh);
		exit(1);
	}

	if (get_built_in(*sh, ((*sh)->tokens)[0]))
	{
		/* (*sh)->command = _strdup((*sh)->buffer); */
		get_built_in(*sh, ((*sh)->tokens)[0])(sh);
		cleanup_and_free_tokens(*sh);
		exit(1);
	}

	exit(0);
}
/**
 * execute_command - Execute a command.
 * @cmd: Command string.
 * @shell: Pointer to the global variable structure.
 * @head: Pointer to the command list structure.
 * @h: Pointer to the command node structure.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char *cmd, g_var **shell, cmd_list *head, cmd_n_list *h)
{
	char  *p_nm = (*shell)->prog_name, *msg = "not found";
	g_var **sh = shell;


	(*sh)->num_tokens = tokenize(&((*sh)->tokens), cmd, " ");
	process_special_cases1(sh, &head, &h);
	cmd = check_cmd_exist((*sh)->tokens[0]);
	(*sh)->command = cmd;

	if (cmd)
	{
		if (execve(cmd, (*sh)->tokens, (*sh)->environs) == -1)
		{
			perror("PIPE");
			exit(errno);
		}

		return (0);
	}
	else
		not_found(p_nm, ((*sh)->tokens)[0], (*sh)->process_id, msg);

	cleanup_and_free_tokens(*sh);
	return (0);
}

/**
 * chk_cmd - check command exist.
 * @sh: Pointer to the shell structure.
 * Return: 1 if true, 0 otherwise.
 */
int chk_cmd(g_var **sh)
{
	int i = 0, size_a = 3/* , size_b = 0 */;
	char *tmp = NULL, **tm = NULL;
	/* pid_t childPid; */
	tmp = _strdup((*sh)->command);
	free((*sh)->command);
	(*sh)->command = NULL;


	(*sh)->command = check_cmd_exist(tmp);

	free_arr(&((*sh)->tokens), (*sh)->num_tokens);

	if ((*sh)->command)
	{
		(*sh)->num_tokens  = tokenize(&((*sh)->tokens), (*sh)->buf_pi, "\n");

		for (i = 0; i < (*sh)->num_tokens - 1; ++i)
		{
			remove_emptyspaces(&((*sh)->tokens[i]));
			remove_nl(&((*sh)->tokens[i]));
			tm = _calloc((size_a), sizeof(char *));
			addAtBeg(tm, size_a, (*sh)->tokens[i]);
			addAtBeg(tm, size_a, (*sh)->command);
			tm[size_a - 1] = NULL;
			execute(*sh, tm, (*sh)->environs);
			free_arr(&(tm), size_a);
		}

		free((*sh)->buf_pi);
		(*sh)->buf_pi = NULL;
		cleanup_and_free_tokens(*sh);
		free(tmp);
		return (1);
	}
	else
	{
		not_found((*sh)->prog_name, tmp, (*sh)->process_id, "not found");
		free(tmp);
	}
	return (0);
}
/**
 * process_sle - Process a single command from the command list.
 * @p: Pointer to the pip command list node.
 * @sh: Pointer to the shell structure.
 * @head: Pointer to the command node list.
 * Return: 1 if a command is processed, 0 otherwise.
 */
static int process_sle(g_var *sh, cmd_n_list **head, ppl *p)
{

	free(sh->command);
	sh->command = NULL;

	if (p->next == NULL)
	{
		sh->fl_pip = 0;
	}

	if (p != NULL)
	{
		free_arr(&(sh->tokens), sh->num_tokens);
		sh->command  = _strdup(p->str);

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

		chk_cmd(&sh);
		cleanup_and_free_tokens(sh);
	}

	return (0);
}

/**
 * proc_pip - Process commands from the command list.
 * @p: Pointer to the command list.
 * @sh: Pointer to the shell structure.
 * @head: Pointer to the command node list.
 * Return: Number of nodes processed.
 */
size_t proc_pip(g_var *sh, cmd_n_list **head, ppl **p)
{
	size_t nodes = 0;
	ppl *h = *p;

	while (h != NULL)
	{
		sh->fl_pip = 1;

		if (process_sle(sh, head, h))
		{
			h = h->next;
			nodes++;
			continue;
		}

		h = h->next;
		nodes++;
	}

	free(sh->buf_pi);
	sh->buf_pi = NULL;
	return (nodes);
}
