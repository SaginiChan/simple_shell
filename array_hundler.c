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
