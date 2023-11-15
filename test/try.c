/**
 * input_check - checks if command is comlete
 * @sh: global variables
*/
void input_check(g_var *sh)
{
    int num = sh->num_tokens - 2;

    if (_strcmp(sh->tokens[num], "||") == 0 ||
_strcmp(sh->tokens[num], "&&") == 0 )
    {
/*         free(sh->buffer); */
        free_arr(sh->tokens, sh->num_tokens);
/*         sh->buffer = NULL; */
/*        _puts("\n"); */
       _puts(">");
       _getline(&(sh->buffer), &(sh->size), stdin);
       sh->num_tokens = tokenize(&(sh->tokens), sh->buffer, " ");
    }
    else
    {
        return;
    }
    input_check(sh);
    
    
}

