#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
char *tokens[] = { "echo", "$?", NULL};
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
char *str_buff(char *buf, int n, int len)
{
    int i = 0, ble = 0, count = 0;
    unsigned int no = 0;

    if (sizeof(no) != 4)
        return (NULL);
    if (buf == NULL)
        return (NULL);
    ble = strlen(buf);
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
int _echo(char *command, int exit_status) 
{
    int len = strlen(command), int_ln = int_len(exit_status);
    int len2 = strlen(tokens[0]) + 1, count = 0;
    int i = 0, pi_ln = 0;
    char *status = NULL;
    char *buf = NULL;
    pid_t pid = getpid();

    if (!command) {
        errno = EINVAL;
        return 1;
    }
  while (command[len2 + count]) count++;
  pi_ln = int_len(pid);
    buf = calloc((pi_ln + count + int_ln + 1), sizeof(char));
    for (i = 0; command[len2 + i]; ++i) {
          status = calloc(pi_ln + int_ln + 1, sizeof(char));
        if (command[len2 + i] == '$') {
            if (command[len2 + i + 1] == '?') {
                status = str_buff(status, exit_status, int_ln);
                strcat(buf, status);
                i += 2;
            } else if (command[len2 + i + 1] == '$') {
                status = str_buff(status, pid, pi_ln);
                strcat(buf, status);
                i += 2;
                free(status);
                status = NULL;
            } else {
                buf[i] = command[len2 + i];
            }
        } else {
            buf[i] = command[len2 + i];
        }
        free(status);
        status = NULL;
    }

    if (write(1, buf, strlen(buf)) == -1)
        printf("Error writing to stdout");

    puts("\n");
    free(buf);
    return 0;
}
int main() {
    char cmd[] = "echo status=$? exit_status=$$";
    int status = 12345;

    _echo(cmd, status);

    return 0;
}
int _echo(g_var **sh) 
{
    int len = _strlen((*sh)->command);
    int len2 = _strlen((*sh)->tokens[0]) + 1;
	int i = 0;
	char *status = NULL;
    char *buf = _calloc(len + 1, sizeof(char));

    if (!(*sh)->command) {
        errno = EINVAL;
        return 1;
    }

    if (!buf)
		handle_error("Error allocating memory");

	remove_emptyspaces(&((*sh)->command));
    for (i = 0; (*sh)->command[len2 + i]; ++i) {
        if ((*sh)->command[len2 + i] == '$') {
            if ((*sh)->command[len2 + i + 1] == '?') {
				 status = _calloc(len + 1, sizeof(char));
                status = str_buff(&status, (*sh)->exit_status, int_len((*sh)->exit_status));
                _strcat(buf, status);
                i = _strlen(buf) - 1;
                len2 += 2;
                free(status);
            } else if ((*sh)->command[len2 + i + 1] == '$') {
                _strcat(buf, "REPLACE2");
                i = _strlen(buf) - 1;
                len2 += 2;
            } else {
                buf[i] = (*sh)->command[len2 + i];
            }
        } else {
            buf[i] = (*sh)->command[len2 + i];
        }
/* 		free(status);
		status = NULL; */
    }

    if (write(1, buf, _strlen(buf)) == -1)
        handle_error("Error writing to stdout");

    _puts("\n");
    free(buf);
    return 0;
}