#include "shell.h"

/**
 * array_sort - it sorts an array of str from
 *              shortest to longest variables.
 * @arr: a pointer to the string to be sorted
 * @size: size of the array.
 * Return: it returns an array of strings.
 */
void array_sort(char *arr[], int size)
{
	int i, j;
	char *temp;

	for (i = 1; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{

			if (_strlen(arr[j]) > _strlen(arr[j + 1]))
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
/**
 * free_arr - frees an array for tokenization
 * @arr: array to be freed
 * @tokens: number of tokens to be freed
*/
void free_arr(char ***arr, int tokens)
{
	int i = 0;

	if ((*arr) == NULL)
	{
		return;
	}

	for (i = 0; i < tokens; i++)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}

	free(*arr);
	(*arr) = NULL;
}
/**
 * free_env - frees an array for tokenization
 * @sh: it has array of environs array to be freed
*/
void free_env(g_var *sh)
{
	int i = 1, k = 0;

	while (sh->added_envs >= 0)
	{

		free(sh->environs[sh->added_envs]);
		sh->environs[k - i] = NULL;
		sh->added_envs--;
	}
}
/**
 * addAtBeg - adds string at the begining of the array.
 * @array: Pointer to the array to be manipulated.
 * @size: size of the array
 * @element: string to be added
 */
void addAtBeg(char *array[], int size, const char *element)
{
	int i = 0;

	for (i = size - 1; i > 0; i--)
	{
		array[i] = array[i - 1];
	}

	array[0] = _strdup((char *)element);

	if (array[0] == NULL)
	{
		errno = ENOMEM;
		perror("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	/*  (*size)++; */
}
/**
 * duplicateArray - Duplicates an array of strings.
 * @original: The original array of strings.
 * @size: The size of the array.
 *
 * Return: A duplicated array of strings.
 */
char **duplicateArray(char **original, size_t size)
{
	size_t i = 0;
	char **duplicate = malloc(size * sizeof(char *));

	if (duplicate == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < size; i++)
	{
		duplicate[i] = _strdup(original[i]);

		if (duplicate[i] == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
	}

	return (duplicate);
}
