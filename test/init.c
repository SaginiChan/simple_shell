#include "main.h"
/**
 * initialize_shell - Initializes the shell structure.
 * @shell: Pointer to the shell structure.
 * @envp: environment variables array
 */
void initialize_shell(shell_var *shell, char **envp)
{
	shell->PROMPT = true;
	shell->buf = NULL;
	shell->size = 0;
	shell->chRead = 0;
	shell->finArr = NULL;
	shell->fin = NULL;
	shell->environs = envp;
	shell->command = NULL;
	shell->process_id = 1;
	shell->num_tokens = 0;

}

    char *str = NULL;
    char *strd = strdup(sh);
    char *symbol1 = "||";

    while ((str = strtok(strd, "&&")
            ? strtok(NULL, "&&")
            : strtok(NULL, "||")) != NULL)
    {
        add_node_end1(head, str, symbol1);
    }

    free(strd);
