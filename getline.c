#include "shell.h"

/**
 * check_chars - checks if chars_read is -1
 * if true it exits the shell
 * @charsRead: number of characters read
 * @man_buf: buffer to be freed in case of error
 */
void check_chars(ssize_t charsRead, char **man_buf)
{
	if (charsRead == -1)
	{
		perror("Invalid read: ");
		free(*man_buf);
		exit(EXIT_FAILURE);
	}
}

/**
 * _fileno - get the file descriptor number
 * @stream: stream to find fd for
 * Return: returns the file descriptor
 */
int _fileno(FILE *stream)
{
	return (stream->_fileno);
}
/**
 * validate - validates buffer
 * @len: stream to find fd for
 * @tm_n: previuose size of buffer
 * @man_buf: pointer to buffer
 * @n: size of buffer
 */
void validate(size_t len, int tm_n, char **man_buf, size_t *n)
{
	if (len > 0)
	{
		if (len < *n - 1)
		{
			(*man_buf)[len] = ' ';
			len++;
		}
		else
		{
			*n = len + 2;
			*man_buf = _realloc(*man_buf, tm_n, *n);

			if (*man_buf == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}

			(*man_buf)[len] = ' ';
			len++;
		}
	}
}
/**
 * read_buffer - reads the fd to buff
 * @fd: file descriptor to read from
 * @man_buf: buffer to save to
 * @n: size of buffer
 * Return: returns number of chars read
 */
size_t read_buffer(int fd, char **man_buf, size_t *n)
{
	size_t len = _strlen(*man_buf), totalCharsRead = 0;
	ssize_t charsRead = 0;
	char buffer[BUFFERSIZE];
	int i = 0, tm_n = *n;

	validate(len, tm_n, man_buf, n);

	while ((charsRead = read(fd, buffer, sizeof(buffer))) > 0)
	{
		totalCharsRead += charsRead;

		if (totalCharsRead >= *n)
		{
			*n *= 2;
			*man_buf = _realloc(*man_buf, tm_n, *n);
			tm_n = *n;

			if (*man_buf == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
		}

		for (i = 0; i < charsRead; i++)
		{
			if (buffer[i] == '\n')
			{
				(*man_buf)[len] = '\n';
				(*man_buf)[len + 1] = '\0';
				return (len);
			}

			(*man_buf)[len] = buffer[i];
			len++;
		}
	}

	check_chars(charsRead, man_buf);
	return (totalCharsRead);
}

/**
 * _getline - gets input from stream
 * @lptr: pointer to buffer to be stored
 * @n: size of buffer
 * @stream: stream to be read
 * Return: returns number of chars read
 */
size_t _getline(char **lptr, size_t *n, FILE *stream)
{
	size_t nread = 0;
	int fd = _fileno(stream);
	static char **buf;

	if (*lptr == NULL)
	{
		*n = BUFFERSIZE;
		*lptr = _calloc(sizeof(char), *n);

		if (*lptr == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		buf = NULL;
		buf = lptr;
	}

	nread = read_buffer(fd, buf, n);

	return (nread);
}
