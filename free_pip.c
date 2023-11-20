#include "shell.h"
/**
 * __free_ - frees all the node in a list.
 * @head: pointer to a list.
 */
void __free_(ppl *head)
{
	if (!head)
		return;

	__free_(head->next);
	free(head->str);
	head->str = NULL;
	free(head);
}
/**
 * free_pip - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_pip(ppl **h)
{
	ppl *temp;

	if (!h)
		return;

	if (*h)
	{
		temp = *h;
		*h = NULL;
		__free_(temp);
		return;
	}
}
