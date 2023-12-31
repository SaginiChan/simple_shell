#include "shell.h"
/**
 * _puts - prints stringgs
 * @str: string to be printed
*/
void _puts(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * print_number - prints integers using _putchar
 * @n: is the number to be printed
 */
void print_number(int n)
{
	if (n == 0)
	{
		_putchar('0');
		return;
	}

	if (n == INT_MIN)
	{
		_putchar('-');
		_putchar('2');
		n = 147483648;
	}

	if (n < 0)
	{
		_putchar('-');
		n = -n;
	}

	if (n / 10 != 0)
		print_number(n / 10);

	_putchar(n % 10 + '0');
}
/**
 * print_alias - Print all defined aliases.
 * @sh: Pointer to the shell structure.
 * Return: Always 0.
 */
int print_alias(g_var *sh)
{
	int i = 0;

	while (i < sh->alias_size)
	{
		_puts(sh->alias[i]);
		_puts("\n");
		i++;
	}

	return (0);
}
