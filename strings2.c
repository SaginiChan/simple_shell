#include "shell.h"
/**
 * _strtok - breaks the  string into portions by inroducing null pointers
 * @str: dstring to be broken
 * @delim: delim to be searched
 * Return: returns copied string
*/
char *_strtok(char *str, char *delim)
{
	int i = 0;
	static char *ch, *ch1;

	if (str == NULL)
	{
		str = ch1;
	}


	if (str && _strpbrk(str, delim))
	{
		ch = _strpbrk(str, delim);
		ch1 = (ch + _strspn(ch, delim));
	}
	else
	{
		ch1 = NULL;
		ch = NULL;
	}

	while (str && str[i])
	{
		if (ch && str[i] == *ch)
		{
			str[i] = '\0';
			break;
		}

		i++;
	}

	return (str);
}
/**
 * _strcpy - copies string from src to des
 * @dest: destination for string to be copied
 * @src: sourc of the string coipied
 * Return: returns copied string
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (src == NULL)
		return (dest);

	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * str_buff - convert int to str
 * @buf: buffer to be updated
 * @n: number to be converted
 * @len: length of the string
 * Return: returns the updated buffer
*/
char *str_buff(char **buf, int n, int len)
{
	int i = 0, ble = 0, count = 0;
	unsigned int no = 0;

	if (sizeof(no) != 4)
		return (NULL);
	if (*buf == NULL)
		return (NULL);

	ble = _strlen(*buf);
	if (n < 0)
	{
		if (n <= INT_MIN)
			no = n;
		else
		{
			n = -n;
			no = n;
		}
		len += 1;
		count = (ble + len - 1);
		*buf[ble] = '-';
		i = ble + 1;
	}
	else
	{
		no = n;
		count = (ble + len - 1);
		i = ble;
	}
	for (; count >= i ; count--)
	{
		if (no < 10)
			*buf[count] = (no + '0');
		else
		{
			*buf[count] = (no % 10) + '0';
			no /= 10;
		}
	}
	return (*buf);
}
/**
 * int_len - finds the length of an in
 * @n: integer to find length for
 * Return: returns ength of int
*/
int int_len(int n)
{
	int i = 0;

	if (n == 0)
	{
		return (1);
	}

	for (i = 0; n != 0; i++)
	{
		n /= 10;
	}

	return (i);
}
/**
 * int_str - convert int to str
 * @buf: buffer to be updated
 * @n: number to be converted
 * @len: length of the string
 * Return: returns the updated buffer
*/
char *int_str(char *buf, int n, int len)
{
	int i = 0, ble = 0, count = 0;
	unsigned int no = 0;

	if (sizeof(no) != 4)
		return (NULL);
	if (buf == NULL)
		return (NULL);
	ble = _strlen(buf);
	if (n < 0)
	{
		if (n <= INT_MIN)
			no = n;
		else
		{
			n = -n;
			no = n;
		}
		len += 1;
		count = (ble + len - 1);
		buf[ble] = '-';
		i = ble + 1;
	}
	else
	{
		no = n;
		count = (ble + len - 1);
		i = ble;
	}
	for (; count >= i ; count--)
	{
		if (no < 10)
			buf[count] = (no + '0');
		else
		{
			buf[count] = (no % 10) + '0';
			no /= 10;
		}
	}
	return (buf);
}
