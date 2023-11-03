#include "shell.h"
/**
 * _strcat - it concantenates two strings
 * @dest: string to be appended to
 * @src: string to be appended from
 * Return: retursns combined strins
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;
	int new_length = 0;

	i =  _strlen(dest);
	new_length = i + _strlen(src);
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}

	*(dest + new_length) = '\0';

	return (dest);
}
/**
 * _strncat - conctaenates a string to n characters
 * @dest: the destination of copiied characters
 * @src: the source of copied of characters
 * @n: number of characters to be copied
 * Return: returns a modified string
 */


char *_strncat(char *dest, char *src, int n)
{
	int i = _strlen(dest);
	int j = 0;

	if (n > _strlen(src))
	{
		n = _strlen(src);
	}

	while (j < n && (*src + j) != '\0')
	{
		*(dest + i) = *(src + j);
		j++;
		i++;
	}

	*(dest + i) = '\0';

	return (dest);
}
/**
 * _strncpy - copies a number of characters
 * @dest: the destination of copied charaters
 * @src: the source of characters to be copied
 * @n: number of characters to be copied
 * Return: returns the modified string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	for (; i < n && *(src + i) != '\0'; i++)
	{
		*(dest + i) = *(src + i);
	}

	for (; i < n; i++)
		dest[i] = '\0';


	return (dest);
}
/**
 * _strcmp - it compares two strings
 * @s1: first string to be used to compare
 * @s2: second string used to be compare
 * Return: returns a - 0 if s1 and s2 are equal:
 *                     negative if s1 is less than s2
 *                     positive if s1 is greater than s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
/**
 * _strlen - String length
 *
 * @s: The string to be measured
 *
 * Return: The length of @s
 */
int _strlen(const char *s)
{
	unsigned int l = 0;

	while (s && s[l])
		++l;
	return (l);
}
