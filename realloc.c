#include "shell.h"
#include <stdlib.h>
/**
 * _realloc - reallocate a memory block using malloc
 * @ptr: pointer of memory to be reallocated
 * @old_size: ptrs old memory size
 * @new_size: ptrs new size
 * Return: returns a pointer to memory f the new allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *ptr1 = NULL;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		ptr = malloc(new_size);

		if (ptr == NULL)
			return (NULL);

		return (ptr);
	}

	ptr1 = malloc(new_size);

	if (ptr1 == NULL)
	{
		return (NULL);
	}

	_memset(ptr1, 0, new_size);
	ptr1 = _memcpy(ptr1, ptr, old_size);
	free(ptr);

	return (ptr1);
}
