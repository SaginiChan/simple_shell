#include "shell.h"
/**
 * power - finds the power
 * @base: base of power
 * @exponent: exponent to the base
 * Return: returns power of a number
*/
int power(int base, int exponent)
{
	int i = 0, num = 1;

	for (; i < exponent; i++)
	{
		num *= base;
	}

	return (num);
}
/**
 * _atoi - converts string to int
 * @str: string to be converted
 * Return: returns an integer
*/
int _atoi(char *str)
{
	int num = 0, i = 0, len = _strlen(str) - 1;

	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num += power(10, len) * (str[i] - '0');
		}
		else
		{
			return (-1);
		}

		len--;
		i++;
	}

	return (num);
}
