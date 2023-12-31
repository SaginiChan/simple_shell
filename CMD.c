#include "shell.h"
/**
 * handleCommon - Handles common operations for special cases.
 *
 * @sh: Pointer to the shell structure.
 * @p: Pointer to the list of pipe cmds.
 * @h: Pointer to the list of commands with symbols.
 * Return: 1 on success, indicating that the process has been handled.
 */
int handleCommon(g_var **sh, ppl **p, cmd_n_list **h)
{
	(*sh)->pip_num = tokenize(&((*sh)->pip_cmds), (*sh)->buffer, "|");
	ex_pipes(sh, p);
	proc_pip(*sh, h, p);
	free_arr(&((*sh)->pip_cmds), (*sh)->pip_num);
	free_pip(p);
	return (1);
}
/**
 * process_special_cases - Process special cases in user input.
 * @sh: Pointer to the shell structure.
 * @h: pointer to list of commands with symbols
 * @p: list of pipe cmds
 * @head: Pointer to the command list head.
 * Return: returns 1 if one of the proces is passed 0 if not;
 */
int process_special_cases(g_var **sh, cmd_list **head, cmd_n_list **h, ppl *p)
{
	if (!isatty(STDIN_FILENO))
	{
		handleCommon(sh, &p, h);
		return (1);
	}

	if (check_semicolon(sh, head))
	{
		process_commands(*head, *sh, h);
		((*sh)->process_id)++;
		free_list_cmd(head);
		(*sh)->command = NULL;
		cleanup(*sh);
		return (1);
	}

	if (hasSymbols(sh) && (*sh)->buffer)
	{
		(*sh)->command = _strdup((*sh)->buffer);
		check_symbols(sh, h);
		process_cmd_symbols(*h, *sh);
		((*sh)->process_id)++;
		free_listint_safe(h);
		(*sh)->command = NULL;
		cleanup(*sh);
		return (1);
	}
	if (_strchr((*sh)->buffer, '|'))
	{
		handleCommon(sh, &p, h);
		return (1);
	}
	if (get_built_in(*sh, ((*sh)->tokens)[0]))
	{
		(*sh)->command = _strdup((*sh)->buffer);
		get_built_in(*sh, ((*sh)->tokens)[0])(sh);
		cleanup_and_free_tokens(*sh);
		return (1);
	}
	return (0);
}
/**
 * checks_ser - conducts series of checks.
 * @sh: Pointer to the shell structure.
 */
void checks_ser(g_var **sh)
{
	input_check(*sh);
	free_arr(&(*sh)->tokens, (*sh)->num_tokens);
	remove_qutes(&((*sh)->buffer));
	remove_nl(&((*sh)->buffer));
	(*sh)->num_tokens = tokenize(&((*sh)->tokens), (*sh)->buffer, " ");
	/* remove_extra_spaces(&((*sh)->buffer)); */
	/* remove_emptyspaces(&((*sh)->buffer)); */
	process_hsh_sym(sh);
}
/**
 * shell_prompt - is a prompt that keeps asking for user input
 * @sh: struct for global variables
*/
void shell_prompt(g_var **sh)
{
	cmd_list *head = NULL;
	cmd_n_list *h = NULL;
	ppl *pipes = NULL;
	char *p_nm = (*sh)->prog_name, *msg = "not found";

	/* signal(SIGINT, sigint_handler); */

	while ((*sh)->PROMPT)
	{
		if (!isatty(STDIN_FILENO))
			(*sh)->PROMPT = false;

		(*sh)->nread = _getline(&((*sh)->buffer), &((*sh)->size), stdin);

		if (_isprint(sh, (*sh)->buffer) == 1)
			continue;

		rmTb((*sh)->buffer);
		remove_emptyspaces(&((*sh)->buffer));
		(*sh)->num_tokens = tokenize(&((*sh)->tokens), (*sh)->buffer, " ");
		checks_ser(sh);

		if (!(*sh)->buffer)
		{
			cleanup_and_free_tokens(*sh);
			continue;
		}
		if (process_special_cases(sh, &head, &h, pipes) == 1)
			continue;
		(*sh)->command = check_cmd_exist((*sh)->tokens[0]);
		if ((*sh)->command)
		{
			execute(*sh, (*sh)->tokens, (*sh)->environs);
			cleanup_and_free_tokens(*sh);
			continue;
		}
		else
			not_found(*sh, p_nm, ((*sh)->tokens)[0], (*sh)->process_id, msg);
		cleanup_and_free_tokens(*sh);
	}
}
