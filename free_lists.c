#include "shell.h"

/**
 * __free - frees all the node in a list.
 * @head: pointer to a list.
 */
void __free(cmd_n_list *head)
{
	if (!head)
		return;

	__free(head->next);

	if (head->str != NULL)
	{
		free(head->str);
	}
	head->str = NULL;
	free(head);
}
/**
 * free_listint_safe - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_listint_safe(cmd_n_list **h)
{
	cmd_n_list *temp;

	if (!h)
		return;

	if (*h)
	{
		temp = *h;
		*h = NULL;
		__free(temp);
		return;
	}
}
/**
 * __free_cmd - frees all the node in a list.
 * @head: pointer to a list.
 */
void __free_cmd(cmd_list *head)
{
	if (!head)
		return;

	__free_cmd(head->next);
	free(head->str);
	head->str = NULL;
	free(head);
}
/**
 * free_list_cmd - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_list_cmd(cmd_list **h)
{
	cmd_list *temp;

	if (!h)
		return;

	if (*h)
	{
		temp = *h;
		*h = NULL;
		__free_cmd(temp);
		return;
	}
}
