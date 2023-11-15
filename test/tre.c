#include "shell.h"
/**
 * read_buffer - reads the fd to buff
 * @fd: file descriptor to read from
 * @man_buf: buffer to save to
 * @n: size of buffer
 * Return: returns number of chars read
 */
size_t read_buffer(int fd, char **man_buf, size_t *n)
{
    size_t len = _strlen(*man_buf);
    ssize_t charsRead = 0, chars = -1;
    char buffer[BUFFERSIZE];
    size_t totalCharsRead = 0;

    if (len > 0)
    {
        *(*man_buf + len) = ' ';
        len++;
    }

   

    while ((charsRead = read(fd, buffer, sizeof(buffer))) > 0)
    {
        totalCharsRead += charsRead;

        if (totalCharsRead == BUFFERSIZE)
        {
            *n = BUFFERSIZE * 2;
            *man_buf = realloc(*man_buf, *n);

            if (*man_buf == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }

        for (size_t i = 0; i < charsRead; i++)
        {
            if (buffer[i] == '\n')
            {
                *(*man_buf + len) = '\n';
                *(*man_buf + len + 1) = '\0';
                chars++;
                return (chars);
            }

            *(*man_buf + len) = buffer[i];
            len++;
            chars = len;
        }
    }

    if (charsRead == -1)
    {
        perror("Invalid read: ");
        free(*man_buf);
        exit(EXIT_FAILURE);
    }

    return (totalCharsRead);
}



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
	size_t len = _strlen(*man_buf);
	ssize_t charsRead = 0, chars = -1;
	char c = '\0';
	if (len > 0)
	{
		*(*man_buf + len)  = ' ';
		len++;
	}
	
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
			*(*man_buf + len) = '\n';
			*(*man_buf + len)  = '\0';
			chars++;
			break;
		}

		*(*man_buf + len)  = c;
		len++;
		chars = len;
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
	static char *buf;

	fd = _fileno(stream);

	if (*lptr == NULL)
	{
		*n = BUFFERSIZE;
		*lptr = malloc(sizeof(char) * (*n));
		_memset(*lptr, 0, *n);
		buf = *lptr;
	}




	nread = read_buffer(fd, &buf, n);
	/* buf = *lptr; */

	return (nread);
}
