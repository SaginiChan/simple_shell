
/**
 * __free - frees all the node in a list.
 * @head: pointer to a list.
 * @i: node counter
 * Return: returns the number of nides
 */
int __free2(cmd_n_list *head, int i)
{
	int x = 0;

	if (!head)
		return (1);

	x = (i + __free2(head->next, i));
	free(head->str);
	free(head);
	return (x);
}
/**
 * free_listint_safe - frees all the node in a list and reset the head to NULL
 *                     in a safe way.
 * @h: pointer of pointer to a list.
 * Return: returns the size of the lst
 */
size_t free_listint_safe(cmd_n_list **h)
{
	int flag = 0;
	cmd_n_list *ptr1 =  *h, *ptr2 = *h;
	size_t sz = 0;

	while (ptr2 != NULL && ptr2->next !=  NULL)
	{
		if (ptr2->next == ptr1->next)
		{
			ptr2->next = NULL;
			ptr1 = *h;
			*h = NULL;
			sz = __free2(ptr1, 1);
			sz -= 1;
			break;
		}

		ptr1 = ptr1->next;

		if (flag == 0)
			ptr2 = ptr2->next->next;
		else
			ptr2 = ptr2->next;

		if (ptr1 == ptr2)
		{
			flag = 1;
			ptr1 = *h;
		}

	}

	return (sz);
}