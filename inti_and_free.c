#include "shell.h"

void constructor(void) __attribute__((constructor));
/**
 * constructor - print bfore main star
*/
void constructor(void)
{

}
/**
 * initialize_shell - Initializes the shell structure.
 * @sh: Pointer to the shell structure.
 * @envp: environment variables array
 */
void initialize_shell(g_var **sh, char **envp)
{
	(*sh)->buffer = NULL;
	(*sh)->tokens = NULL;
	(*sh)->command = NULL;
	(*sh)->PATH = NULL;
	(*sh)->process_id = 1;
	(*sh)->num_tokens = 0;
	(*sh)->added_envs = 0;
	(*sh)->pointers = NULL;
	(*sh)->alias = NULL;
	(*sh)->alias_size = 0;
	(*sh)->exit_status = 0;
	(*sh)->status_code = 0;
	(*sh)->flag = 0;
	(*sh)->environs = envp;
	(*sh)->size = 0;
	(*sh)->nread = 0;

}

/**
 * free_mem - frees memory previousely allocated
 * @buffer: buffer to be freed
*/
void free_mem(char *buffer)
{
	if (buffer != NULL)
	{
		free(buffer);
		buffer = NULL;
	}

}
