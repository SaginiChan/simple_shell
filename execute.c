#include "shell.h"

void handle_exit_status(g_var *sh, int status);
/**
 * conc_fpath - Concatenates the file path.
 * @filepath: Pointer to the file path.
 * @path_entry: Path entry.
 * @cmd: Command to concatenate.
 *
 * Return: The concatenated file path.
 */

char *conc_fpath(char *filepath, char *path_entry, char *cmd)
{
	filepath = _strcpy(filepath, path_entry);
	filepath = _strcat(filepath, "/");
	filepath = _strcat(filepath, cmd);

	return (filepath);
}

/**
 * check_cmd_exist - Checks if a cmd exists in the PATH environment variable.
 *
 * @term_cm: Command to check.
 * Return: The command if it exists, NULL otherwise.
 */

char *check_cmd_exist(char *term_cm)
{
	char *copy = NULL, *PATH;
	int i = 0, tokens = 0, ttl = 0;
	char *fpath = NULL;
	char **arr = NULL, *commnd, *strd = NULL;

	PATH = getenv("PATH");

	if (NULL == PATH)
		return (NULL);
	if (access(term_cm, X_OK) == 0)
	{
		strd = _strdup(term_cm);
		return (strd);
	}

	copy = _strdup(PATH);
	tokens = tokenize(&arr, copy, ":");
	array_sort(arr, tokens);
	while (arr[i] != NULL)
	{
		ttl = _strlen(term_cm) + _strlen(arr[i]);
		fpath = malloc(sizeof(char) * ttl + 2);

		if (fpath == NULL)
			return (NULL);


		fpath = conc_fpath(fpath, arr[i], term_cm);

		if (access(fpath, X_OK) == 0)
		{
			commnd = _strdup(fpath);
			free_arr(&arr, tokens);
			free(fpath);
			free(copy);
			fpath = NULL;
			return (commnd);

		}

		i++;
		free(fpath);
		fpath = NULL;
	}

	free_arr(&arr, tokens);
	free(copy);
	return (NULL);
}
/**
 * execute - Execute a command with arguments in a child process.
 * @shell: The shell context.
 * @fin: Command arguments.
 * @envp: Environment variables.
 *
 * This function forks a new process to execute the specified command with arg.
 * It handles errors and updates the shell context accordingly.
 *
 * Return: Status code (0 for success, 1 for general error, or other err codes)
 */
int execute(g_var *shell, char **fin, char **envp)
{
	pid_t child_pid;
	g_var *sh = shell;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (child_pid == 0)
	{
		if (execve(sh->command, fin, envp) == -1)
		{
			perror("execve");
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		handle_exit_status(sh, status);
		if (sh->buf_pi == NULL)
		{
			free(sh->command);
			sh->command = NULL;
			refresh(sh);
		}
		(sh->process_id)++;
		return (sh->status_code);
	}

	return (0);
}

/**
 * handle_exit_status - Handle the exit status of a child process.
 * @sh: The shell context.
 * @status: The exit status of the child process.
 *
 * This function process the exit status of a child process, updates the shell
 * context status_code accordingly, and prints relevant error messages.
 */
void handle_exit_status(g_var *sh, int status)
{
	if (WIFEXITED(status))
	{
		sh->status_code = WEXITSTATUS(status);

		if (sh->status_code == 0)
		{
			return;
		}
		else
			if (sh->status_code == 126)
			{
				perror("Permission denied");
				sh->status_code = EACCES;
			}
			else
				if (sh->status_code == 127)
				{
					perror("No such file or directory");
					sh->status_code = ENOENT;
				}
				else
					if (sh->status_code >= 128)
					{
						/* int signal_number = sh->status_code - 128; */
						sh->status_code = sh->status_code;
					}
					else
					{
						sh->status_code = 2;
					}
	}
	else
	{
		sh->status_code = 2;
	}
}
