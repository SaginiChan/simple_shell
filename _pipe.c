#include "shell.h"
/**
 * add_node_end - adds node at the end of the list
 * @head: its the head of the lis
 * @str: string data to add
 * Return: returns the pointer to address of the added node
*/
ppl *add_node_pipe(ppl **head, const char *str)
{
	char *strd = _strdup((char *)str);
	ppl *temp = malloc(sizeof(ppl)), *ptr;

	if (temp == NULL)
	{
		return (NULL);
	}

	ptr = *head;


	temp->str = strd;
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
 * ex_pipes - Execute commands with pipes recursively.
 * @sh: Pointer to global variable structure.
 * @pipe: pointer to cmd of pipe list
 */
void ex_pipes(g_var **sh,  ppl **pipe)
{
	int i = 0;


	while ((*sh)->pip_cmds && (*sh)->pip_cmds[i])
	{

		add_node_pipe(pipe, (*sh)->pip_cmds[i]);
		i++;

	}

}
