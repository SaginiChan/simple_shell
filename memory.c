#include "shell.h"
/**
 * _memcpy - copies n bytes from memory area src to memory
 *           area dest
 * @dest: destination memory area of src
 * @src: source memory area to be copued
 * @n: number of bytes to be copied
 *
 * Return: returns dest
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	for (; i < n ; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
/**
 * _memset - it sets the n bytes with  b pointed to by s
 * @s: pointer to memory to be manipulated
 * @b: charcter to be used to manipulate
 * @n: number of bytes to use
 *
 * Return: it returns a pointer to s;
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	for (; i < n ; i++)
	{
		s[i] = b;
	}

	return (s);
}
/**
 * proces_buf - process buffer
 * @sh: global variables
 * @buf: buffer to be processed
*/
void proces_buf(g_var **sh, char *buf)
{
	if ((*sh)->fl_pip == 1)
	{
		(*sh)->buf_pi = _calloc(_strlen(buf) + 120, sizeof(char));
		_strcat((*sh)->buf_pi, buf);
	}
	else
	{
		if (write(1, buf, _strlen(buf)) == -1)
			handle_error("Error writing to stdout");
		fflush(stdout);
	}
}
