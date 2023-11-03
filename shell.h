#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

#define BUFFERSIZE 120
/**
 * _strlen - String length
 *
 * @s: The string to be measured
 *
 * Return: The length of @s
 */
int _strlen(const char *s);
/**
 * _strcmp - it compares two strings
 * @s1: first string to be used to compare
 * @s2: second string used to be compare
 * Return: returns a - 0 if s1 and s2 are equal:
 *                     negative if s1 is less than s2
 *                     positive if s1 is greater than s2
 */

int _strcmp(char *s1, char *s2);
/**
 * _strncpy - copies a number of characters
 * @dest: the destination of copied charaters
 * @src: the source of characters to be copied
 * @n: number of characters to be copied
 * Return: returns the modified string
 */

char *_strncpy(char *dest, char *src, int n);
/**
 * _strncat - conctaenates a string to n characters
 * @dest: the destination of copiied characters
 * @src: the source of copied of characters
 * @n: number of characters to be copied
 * Return: returns a modified string
 */


char *_strncat(char *dest, char *src, int n);
/**
 * _strcat - it concantenates two strings
 * @dest: string to be appended to
 * @src: string to be appended from
 * Return: retursns combined strins
 */

char *_strcat(char *dest, char *src);
/**
 * _strpbrk - slices the string and returns the remaining the rest of the str
 * @s: source string to be spiced
 * @accept: the str used to screen s
 *
 * Return: returns the pointer begining for str spliced after char from s
 *         is found
 *         returns null if not found
 */
char *_strpbrk(char *s, char *accept);
/**
 * _strspn - eturns the length of the initial substring of the string
 *           pointed to
 *           by s that is made up of only those character contained in the
 *           string pointed to by accept.
 * @s: string to be scanned
 * @accept: array of chars to be checked
 * Return:  returns the number of characters
 *          in the initial segment of swhich consist
 *          only of characters from ccept
 */
unsigned int _strspn(char *s, char *accept);
/**
 * _strchr - splices the string by returning the matching charcter of s
 * @s: string to be used
 * @c: charcter to be searched
 * Return: returns the first occurnce of c to the end of the string
 *         returns NULL if the character not found
 */
char *_strchr(char *s, char c);
/**
 * _puts - prints stringgs
 * @str: string to be printed
*/
void _puts(char *str);
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c);
/**
 * _memcpy - copies n bytes from memory area src to memory
 *           area dest
 * @dest: destination memory area of src
 * @src: source memory area to be copued
 * @n: number of bytes to be copied
 *
 * Return: returns dest
 */
char *_memcpy(char *dest, char *src, unsigned int n);
/**
 * _memset - it sets the n bytes with  b pointed to by s
 * @s: pointer to memory to be manipulated
 * @b: charcter to be used to manipulate
 * @n: number of bytes to use
 *
 * Return: it returns a pointer to s;
 */
char *_memset(char *s, char b, unsigned int n);
/**
 * _getline - gets input from stream
 * @lptr: pointer to buffer to be stored
 * @n: size of buffer
 * @stream: stream to read from
 * Return: returns number of chars read
*/
size_t _getline(char **lptr, size_t *n, FILE *stream);
#endif /*SHELL_H*/
