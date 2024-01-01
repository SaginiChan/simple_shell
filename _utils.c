#include "shell.h"
#define BUF_SIZE 120
/**
 * _change_dir_actions - Perform the actions for changing the directory.
 * @sh: A pointer to the global variables structure.
 * @arg: The argument representing the new directory.
 * @flg: Flag indicating whether to print the new directory.
 * Return: 0 on success, 1 on failure.
 */
int _change_dir_actions(g_var **sh, const char *arg, int flg)
{
	DIR *dir = opendir(arg);
	char cwd[BUF_SIZE] = {0};

	if (dir == NULL)
	{
		cd_error(arg, (*sh)->prog_name);
		closedir(dir);
		return (1);
	}

	if (chdir(arg) == -1)
	{
		perror("chdir");
		closedir(dir);
		return (1);
	}
	else
	{
		_set(sh, "OLDPLW", getcwd(cwd, BUF_SIZE));
		_set(sh, "PWD", (char *)arg);
	}

	if (flg == 1)
	{
		write(1, getcwd(cwd, BUF_SIZE), strlen(getcwd(cwd, BUF_SIZE)));
		_puts("\n");
	}

	closedir(dir);
	return (0);
}

/**
 * process_switch - Process the result of a built-in command.
 * @sh: A pointer to the global variables structure.
 * @tm: An array of strings representing the command tokens.
 * @temp: A temporary string.
 * @size_a: The number of tokens in the command.
 * @p: A pointer to a structure representing the pipeline.
 * Return: 1 if processing was successful, 0 otherwise.
 */
int process_switch(g_var *sh, char **tm, char *temp, int size_a, ppl *p)
{
	int result = 0;

	switch (result)
	{
		case 2:
			sh->command = _strdup(temp);
			sh->fl_pip  = 8;
			result = _echo(&sh);
			free_arr(&tm, size_a);
			break;
		case 3:
			cleanup_and_exit(sh, tm, temp, size_a, p);
			exiting(&sh);
			return (1);
		case 4:
			free_arr(&tm, size_a);
			sh->fl_pip = 8;
			_printenv(&sh);
			break;
		case 5:
			if (size_a >= 4)
				__setenv(&sh, tm);
			free_arr(&tm, size_a);
			sh->fl_pip = 8;
			break;
		case 6:
			unsetenv(tm[1]);
			free_arr(&tm, size_a);
			sh->fl_pip = 8;
			break;
		case 7:
			_change_dir(&sh, tm, size_a);
			free_arr(&tm, size_a);
			sh->fl_pip = 8;
			break;
		default:
			break;
	}
	return (1);
}
