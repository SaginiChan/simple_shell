#include "shell.h"
/**
 * cleanup_and_free_tokens - Free the tokens array and perform cleanup.
 * @sh: Pointer to the shell structure.
 */
void cleanup_and_free_tokens(g_var *sh)
{
	free_arr(&(sh->tokens), sh->num_tokens);
	(sh->process_id)++;
	cleanup(sh);
}
