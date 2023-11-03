#include "shell.h"

/**
 * _fileno - get the file descriptor number
 * @stream: stream to find fd for
 * Return: returns the file escriptor
*/
int _fileno(FILE *stream)
{
	return (stream->_fileno);
}
/**
 * read_buffer - reads the fd to buff
 * @fd: file descriotor to read from
 * @man_buf: buffer to save to
 * @n: size of buffer
 * Return: returns number of chars read
 *
*/
size_t read_buffer(int fd, char **man_buf, size_t *n)
{
	size_t i = 0;
	ssize_t charsRead = 0, chars = -1;
	char c = '\0';

	while ((charsRead = read(fd, &c, sizeof(c))) > 0)
	{
		if (chars == BUFFERSIZE)
		{
			*n = BUFFERSIZE * 2;
			*man_buf = realloc(*man_buf, *n);

			if (*man_buf == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
		}

		if (c == '\n')
		{
			*(*man_buf + i) = '\n';
			*(*man_buf + i)  = '\0';
			chars++;
			break;
		}

		*(*man_buf + i)  = c;
		i++;
		chars = i;
	}

	if (charsRead == -1)
	{
		perror("Invalid read: ");
		free(man_buf);
		exit(EXIT_FAILURE);
	}

	return (chars);
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
	int fd = 0;

	fd = _fileno(stream);

	if (*lptr == NULL)
	{
		*n = BUFFERSIZE;
		*lptr = malloc(sizeof(char) * (*n));
	}



	nread = read_buffer(fd, lptr, n);


	return (nread);
}
