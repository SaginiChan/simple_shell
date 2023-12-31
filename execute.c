#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
/**
 * check_path - Check if a command exists in the current directory.
 * @cmd: The command to check.
 *
 * Return: An empty string if the command is found,
 * otherwise the original command.
 */
char *check_path(char *cmd)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");

	if (dir == NULL)
	{
		perror("Error opening directory");
		return (NULL);
	}

	entry = readdir(dir);

	while (entry != NULL)
	{
		if (_strcmp(entry->d_name, cmd) == 0)
		{
			closedir(dir);
			return (NULL);
		}

		entry = readdir(dir);
	}

	closedir(dir);

	return (cmd);
}

/**
 * check_and_get_exec - Check if a file is executable and return its path.
 * @term_cm: The file path to check.
 *
 * Return: A dynamically allocated string containing the executable path,
 *         or NULL if the file is not executable or an error occurs.
 */
char *check_and_get_exec(char *term_cm)
{
	char *strd = NULL;
	struct stat file_stat;

	if (!check_path(term_cm))
	{
		return (NULL);
	}


	if (access(term_cm, X_OK | R_OK) == 0)
	{

		if (stat(term_cm, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode) && (file_stat.st_mode & S_IXUSR))
			{
				strd = _strdup(term_cm);
				return (strd);
			}
		}
	}

	return (NULL);
}
int handle_exit_status(g_var *sh, int status);
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
 * build_path - Build PATH from path segments.
 * @path_segments: Array of path segments.
 * @num_segments: Number of segments in path_segments.
 *
 * Return: A pointer to the constructed PATH.
 */
char *build_path(char *path_segments[], int num_segments)
{
	char *PATH = NULL;
	size_t ns  = 0, old = 0;
	int j;

	if (PATH == NULL)
	{
		PATH = malloc(sizeof(char) * (_strlen(path_segments[0]) + 1));

		if (PATH != NULL)
		{
			_strcpy(PATH, path_segments[0]);

			for (j = 1; j < num_segments; j++)
			{
				ns = sizeof(char) * (_strlen(PATH) + _strlen(path_segments[j]) + 2);
				old = _strlen(PATH);
				PATH = _realloc(PATH, old, ns);

				if (PATH != NULL)
				{
					_strcat(PATH, ":");
					_strcat(PATH, path_segments[j]);
				}
				else
				{
					fprintf(stderr, "Error: Failed to reallocate memory for PATH\n");
					return (NULL);
				}
			}
		}
		else
		{
			fprintf(stderr, "Error: Failed to allocate memory for PATH\n");
			return (NULL);
		}
	}

	return (PATH);
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
	char **arr = NULL, *commnd/* , *strd = NULL */;
	char *path_seg[] = {
		"/usr/local/sbin",
		"/usr/local/bin",
		"/usr/sbin",
		"/usr/bin",
		"/sbin",
		"/bin",
		"/usr/games",
		"/usr/local/games"
	};
	int ele = sizeof(path_seg) / sizeof(path_seg[0]);

	PATH = _getenv("PATH");

	if (PATH == NULL)
	{
		PATH = check_and_get_exec(term_cm);
		if (PATH == NULL)
		{
			return (NULL);
		}
		free(PATH);
		PATH = build_path(path_seg, ele);
	}

	commnd = check_and_get_exec(term_cm);
	if (commnd)
	{
		free(PATH);
		return (commnd);
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

		commnd = check_and_get_exec(fpath);

		if (commnd)
		{

			free_arr(&arr, tokens);
			free(fpath);
			free(copy);
			fpath = NULL;
			free(PATH);
			return (commnd);
		}


		i++;
		free(fpath);
		fpath = NULL;
	}

	free(PATH);
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
 * Return: returns exit status
 */
int handle_exit_status(g_var *sh, int status)
{
	if (WIFEXITED(status))
	{
		sh->status_code = WEXITSTATUS(status);

		if (sh->status_code == 0)
		{
			return (sh->status_code);
		}
		else
			if (sh->status_code == 126)
			{
				perror("Permission denied");
				sh->status_code = 127;
			}
			else
				if (sh->status_code == 127)
				{
					perror("No such file or directory");
					sh->status_code = ENOENT;
					return (2);
				}
				else
					if (sh->status_code >= 128)
					{
						/* int signal_number = sh->status_code - 128; */
						sh->status_code = sh->status_code;
						return (sh->status_code);
					}
					else
					{
						sh->status_code = 2;
						return (sh->status_code);
					}
	}
	else
	{
		sh->status_code = 2;
		return (sh->status_code);
	}

	return (sh->status_code);
}
