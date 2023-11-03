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
