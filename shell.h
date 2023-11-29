#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ENVS 100
#define MAXSIZE 1024
#define BUFFERSIZE 1024
#define FLAG 0
extern int flag;
extern char **environ;

/**
 * struct g_var - Shell variables struct
 * @PROMPT: prompt status
 * @status_code: Prompt flag(true or false)
 * @size: Buffer pointer
 * @command: Command pointer
 * @PATH: path to cmd programs
 * @process_id: Process ID
 * @num_tokens: Number of tokens
 * @environs: array of environment variables
 * @size: Size of buffer array
 * @nread: number of characters read
 * @buffer: array of environment variables
 * @prog_name: Size of fin array
 * @tokens: number of characters read
 * @added_envs: array of environment variables
 * @pointers: Size of fin array
 * @alias: number of characters read
 * @alias_size: array of environment variables
 * @flag: flag used to show signal statur
 * @pip_num: number of pips
 * @mode: mode of the pipe
 * @buf_pi: buffer to save pips
 * @fl_pip: flag to track pipe cmds
 * @pip_cmds: commands to  be put in a list
 * @exit_status: number of characters read
 */
typedef struct g_var
{
	bool PROMPT;
	char *buffer;
	int mode;
	char *command;
	char *PATH;
	char *prog_name;
	int process_id;
	char **tokens;
	int num_tokens;
	char **environs;
	int added_envs;
	char **pointers;
	char **alias;
	int alias_size;
	int flag;
	char **pip_cmds;
	int pip_num;
	char *buf_pi;
	int fl_pip;
	int exit_status;
	int status_code;
	size_t size;
	ssize_t nread;
} g_var;
typedef struct g_var gbf_var;
/**
 * struct cmd_list - singly linked list of commands
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct cmd_list
{
	char *str;
	unsigned int len;
	struct cmd_list *next;
} cmd_list;
/**
 * struct built_ins - Struct
 *
 * @str: The operator
 * @f: The function associated
 */
typedef struct built_ins
{
	char *str;
	int (*f)(g_var **sh);
} built_ins;
/**
 * struct cmd_n_list - singly linked list of commands
 * @str: string - (malloc'ed string)
 * @symbol: symbol to be passed
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct cmd_n_list
{
	char *str;
	char *symbol;
	unsigned int len;
	struct cmd_n_list *next;
} cmd_n_list;
/**
 * struct ppl - Struct
 *
 * @str: The string
 * @symbol: symbol to keep track
 * @next: next struct
 */
typedef struct ppl
{
	char *str;
	char *symbol;
	struct ppl *next;
} ppl;
/**
 * _isprint - checks for non printable characters
 * @c: character to be checked
 * @sh: gloabal variables
 * Return: returns 1 if true 0 if false
*/
int _isprint(g_var **sh, char *c);
/**
 * _strtok - breaks the  string into portions by inroducing null pointers
 * @str: dstring to be broken
 * @delim: delim to be searched
 * Return: returns copied string
*/
char *_strtok(char *str, char *delim);
/**
 * _strlen - String length
 *
 * @s: The string to be measured
 *
 * Return: The length of @s
 */
int _strlen(const char *s);
/**
 * _strcmp - it compares two strings
 * @s1: first string to be used to compare
 * @s2: second string used to be compare
 * Return: returns a - 0 if s1 and s2 are equal:
 *                     negative if s1 is less than s2
 *                     positive if s1 is greater than s2
 */

int _strcmp(char *s1, char *s2);
/**
 * _strncpy - copies a number of characters
 * @dest: the destination of copied charaters
 * @src: the source of characters to be copied
 * @n: number of characters to be copied
 * Return: returns the modified string
 */

char *_strncpy(char *dest, char *src, int n);
/**
 * remove_extra_spaces - remove extra white spaces
 * @input: string to remove white spaces
 *
*/
void remove_extra_spaces(char *input);
/**
 * remove_emptyspaces - remove white spaces
 * @str: string to remove white spaces
 *
*/
void remove_emptyspaces(char **str);
/**
 * remove_quites - remove all white spaces
 * @string: string to remove white spaces
 *
*/
void remove_qutes(char **string);
/**
 * remove_nl - remove new line at the end
 * @str: string to remove white spaces
 *
*/
void remove_nl(char **str);

/**
 * rmTb - removes tabs from strings
 * @str: string to be manipulated
*/
void rmTb(char *str);
/**
 * _strncat - conctaenates a string to n characters
 * @dest: the destination of copiied characters
 * @src: the source of copied of characters
 * @n: number of characters to be copied
 * Return: returns a modified string
 */

char *_strncat(char *dest, char *src, int n);
/**
 * _strcat - it concantenates two strings
 * @dest: string to be appended to
 * @src: string to be appended from
 * Return: retursns combined strins
 */

char *_strcat(char *dest, char *src);
/**
 * _strcat_custom - it concantenates two strings
 * @dest: string to be appended to
 * @src: string to be appended from
 * Return: retursns combined strins
 */

char *_strcat_custom(char *dest, char *src);
/**
 * _strpbrk - slices the string and returns the remaining the rest of the str
 * @s: source string to be spiced
 * @accept: the str used to screen s
 *
 * Return: returns the pointer begining for str spliced after char from s
 *         is found
 *         returns null if not found
 */
char *_strpbrk(char *s, char *accept);
/**
 * _strspn - eturns the length of the initial substring of the string
 *           pointed to
 *           by s that is made up of only those character contained in the
 *           string pointed to by accept.
 * @s: string to be scanned
 * @accept: array of chars to be checked
 * Return:  returns the number of characters
 *          in the initial segment of swhich consist
 *          only of characters from ccept
 */
unsigned int _strspn(char *s, char *accept);
/**
 * _strchr - splices the string by returning the matching charcter of s
 * @s: string to be used
 * @c: charcter to be searched
 * Return: returns the first occurnce of c to the end of the string
 *         returns NULL if the character not found
 */
char *_strchr(char *s, char c);
/**
 * _strcpy - copies string from src to des
 * @dest: destination for string to be copied
 * @src: sourc of the string coipied
 * Return: returns copied string
*/
char *_strcpy(char *dest, char *src);
/**
 * _puts - prints stringgs
 * @str: string to be printed
*/
void _puts(char *str);
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c);
/**
 * print_alias - Print all defined aliases.
 * @sh: Pointer to the shell structure.
 * Return: Always 0.
 */
int print_alias(g_var *sh);
/**
 * _memcpy - copies n bytes from memory area src to memory
 *           area dest
 * @dest: destination memory area of src
 * @src: source memory area to be copued
 * @n: number of bytes to be copied
 *
 * Return: returns dest
 */
char *_memcpy(char *dest, char *src, unsigned int n);
/**
 * _memset - it sets the n bytes with  b pointed to by s
 * @s: pointer to memory to be manipulated
 * @b: charcter to be used to manipulate
 * @n: number of bytes to use
 *
 * Return: it returns a pointer to s;
 */
char *_memset(char *s, char b, unsigned int n);
/**
 * _calloc - Allocates memof an array nmemb elements
 *           of size bytes each
 * @nmemb: number of elements to be given memory
 * @size: size of each element
 * Return: returns a pointer to the allocated memory
 */
void *_calloc(unsigned int nmemb, unsigned int size);
/**
 * _realloc - reallocate a memory block using malloc
 * @ptr: pointer of memory to be reallocated
 * @old_size: ptrs old memory size
 * @new_size: ptrs new size
 * Return: returns a pointer to memory f the new allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
/**
 * _getline - gets input from stream
 * @lptr: pointer to buffer to be stored
 * @n: size of buffer
 * @stream: stream to read from
 * Return: returns number of chars read
*/
size_t _getline(char **lptr, size_t *n, FILE *stream);
void shell_prompt(g_var **sh);
/**
 * free_mem - frees memory previousely allocated
 * @bufferr: buffer to be freed
*/
void free_mem(char *bufferr);
/**
 * initialize_shell - Initializes the shell structure.
 * @shell: Pointer to the shell structure.
 * @envp: environment variables array
 */
void initialize_shell(g_var **shell, char **envp);
/**
 * cleanup - clean up the varable used before next iteration.
 * @shell: Pointer to the shell structure to be cleaned.
 */
void cleanup(g_var *shell);
/**
 * exiting - converts str to int status.
 * @shell: stract passed to access the array of commands.
 * Return: returns 0 on succes
 *                 -1 on failuire
 */
int exiting(g_var **shell);
/**
 * sigint_handler - Handles the SIGINT signal.
 * @sig: The signal number.
 */
void sigint_handler(int sig);
/**
 * _strdup - duplicates the string and returns a pointer to new string
 * @str: string to be duplicated
 * Return: returns the duplicates the of the string
 *         returns NULL if ERROR
 */

char *_strdup(char *str);
/**
 * str_contains - checks if a character is contained in a variable
 *
 * @str: the striing to inspect.
 * @ch: the character being ispected.
 *
 * Return: returns true if char found and false if not found.
 *
 */
int str_contains(char *str, char ch);
/**
 * check_single_quote - Add single quotes to a string if not present.
 * @str: Pointer to the string to check.
 * Return: 1 if modified, 0 if not.
 */
int check_single_quote(char **str);
/**
 * cleanup_and_free_tokens - Free the tokens array and perform cleanup.
 * @sh: Pointer to the shell structure.
 */
void cleanup_and_free_tokens(g_var *sh);
/** COMMAND LIST OPERATIONS*/
/**
 * input_check - checks if command is comlete
 * @sh: global variables
*/
void input_check(g_var *sh);
/**
 * free_env - frees an array for tokenization
 * @sh: it has array of environs array to be freed
*/
void free_env(g_var *sh);
/**
 * process_commands - prints contents of the list
 * @head: poiter to the first node cmd list colons
 * @h: poiter to the first node cmd list symbols
 * @sh: gloabal variables
 * Return: returns number of nodes in the lis
 *
*/
size_t process_commands(const cmd_list *h, g_var *sh, cmd_n_list **head);
/**
 * process_cmd_symbols - prints contents of the list
 * @h: poiter to the first node
 * @sh: global variables
 * Return: returns number of nodes in the lis
 *
*/
size_t process_cmd_symbols(const cmd_n_list *h, g_var *sh);
/**
 * free_listint_safe - frees all the node in a list and reset the head to NULL
 *                     in a safe way.
 * @h: pointer of pointer to a list.
 * Return: returns the size of the lst
 */
void free_listint_safe(cmd_n_list **h);
/**
 * free_list - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_list_cmd(cmd_list **h);
/**
 * free_list_pipe - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_list_pipe(ppl **h);
/**
 * refresh - clean up the varable used before next iteration.
 * @shell: Pointer to the shell structure to be cleaned.
 */
void refresh(g_var *shell);
int (*get_built_in(g_var *shell, char *str))(g_var **shell);
/**
 * check_cmd_exist - Checks if a cmd exists in the PATH environment variable.
 *
 * @term_cm: Command to check.
 * Return: The command if it exists, NULL otherwise.
 */

char *check_cmd_exist(char *term_cm);
/**
 * check_symbols - it checks if symbol exists if
 *                   exists breaks the command into list
 * @sh: global variable in struct
 * @head: head of the list;
 *
*/
void check_symbols(g_var **sh, cmd_n_list **head);
/**
 * process_hsh_sym - check availability and validity of  #symbol
 * @sh: global variables
*/
void process_hsh_sym(g_var **sh);
/**
 * add_node_end - adds node at the end of the list
 * @head: its the head of the lis
 * @str: string data to add
 * Return: returns the pointer to address of the added node
*/
cmd_list *add_node_end(cmd_list **head, const char *str);
/**
 * add_node_end - adds node at the end of the list
 * @head: its the head of the lis
 * @str: string data to add
 * @sym: symbol to be tracked
 * Return: returns the pointer to address of the added node
*/
cmd_n_list *add_node_end_sym(cmd_n_list **head, const char *str, char *sym);
/**
 * tokenize - tokenize the string and save them in an arrray
 * @arr: array to be modifieda and save tokens
 * @strn: string to be tokenized
 * @delim: delimeter used to tokenize a string
 * Return: returns size of the string array
*/
int tokenize(char ***arr, char *strn, char *delim);
/**
 * process_tokens - Process tokens in the shell structure.
 * @sh: Pointer to the shell structure.
 * @p: list of pipe commands
 */
void process_tokens(g_var *sh, ppl **p);
/**
 * control_d - Exits a command using CTR + D.
 * @shell: The pointer to struct variables.
 *
 */
void control_d(g_var *shell);
/**
 * _echo - handls ech cmd
 * @sh: global variables pased
 * Return: returns 0 on succes and 1 on failire
*/
int _echo(g_var **sh);
/**
 * _alias - handls alia cmd
 * @sh: global variables pased
 * Return: returns 0 on succes and 1 on failire
*/
int _alias(g_var **sh);
/**
 * _cd - handls cd cmd
 * @sh: global variables pased
 * Return: returns 0 on succes and 1 on failire
*/
int _cd(g_var **sh);
/* END COMMAND OPERATIONS */
/**
 * check_semicolon - it checks if colon exists if
 *                   exists breaks the command into list
 * @sh: global variable in struct
 * @head: head of the list;
 *
 * Return: return 1 if semicolon found and 0 otherwise
*/
int check_semicolon(g_var **sh, cmd_list **head);
/**
 * execute - Executes a command using execve.
 * @shell: The pointer to struct variables to execute.
 * @fin: The array of command arguments.
 * @envp: The array of environment variables.
 * Return: return 2 on error 0 on success
 */
int execute(g_var *shell, char **fin, char **envp);
/**
 * duplicateArray - Duplicates an array of strings.
 * @original: The original array of strings.
 * @size: The size of the array.
 *
 * Return: A duplicated array of strings.
 */
char **duplicateArray(char **original, size_t size);
/**
 * array_sort - it sorts an array of str from
 *              shortest to longest variables.
 * @arr: a pointer to the string to be sorted
 * @size: size of the array.
 * Return: it returns an array of strings.
 */
void array_sort(char *arr[], int size);
/**
 * free_arr - frees an array for tokenization
 * @arr: array to be freed
 * @tokens: number of tokens to be freed
*/
void free_arr(char ***arr, int tokens);
/**
 * addAtBeg - adds string at the begining of the array.
 * @array: Pointer to the array to be manipulated.
 * @size: size of the array
 * @element: string to be added
 */
void addAtBeg(char *array[], int size, const char *element);
/**
 * free_alias - frees an array for alias
 * @arr: array to be freed
 * @tokens: number of tokens to be freed
*/
void free_alias(char **arr, int tokens);
/* ERROR HANDLING*/
/**
 * int_To_Str - Converts an integer to a string.
 * @str: Pointer to the destination string.
 * @num: The integer to convert.
 */
void int_To_Str(char *str, int num);
/**
 * not_found - Handles the "not found" case.
 * @sh: global variables
 * @prog: Name of the program.
 * @comd: Command that was not found.
 * @pid_no: Process ID number.
 * @msg: Error message.
 */

void not_found(g_var *sh, char *prog, char *comd, int pid_no, char *msg);
/**
 * illegal_no - Handles the "illegal number" case.
 * @prog_name: Name of the program.
 * @com: commans that failed
 * @pr_id: Process ID number.
 * @msg: Error message.
 * @str: Command that was not found.
 */
void illegal_no(char *prog_name, char *com, int pr_id, char *msg, char *str);
/**
 * usage_err - Handles the "usage erro" case.
 * @str: error messege
 */
void usage_err(char *str);
/* END ERROR HANDLING */
/* BUILT INS*/
/**
 * _printenv - Gets the value of an environment variable.
 * @sh: The global environment variable to retrieve.
 * Return: 0 if succes , -1 otherwise.
 */
int _printenv(g_var **sh);
/**
 * _setenv - it set environment var for the current proccess
 *
 * @sh: global variable containig variable to be set.
 * Return: returns 0 on success and -1 on error
 */
int _setenv(g_var **sh);
/**
 * _unsetenv - it Remove environment var for the current proccess
 *
 * @sh: gloabal variables.
 * Return: return 0 if success and -1 if faild
 */
int _unsetenv(g_var **sh);
/**
 * _getenv - Gets the value of an environment variable.
 * @var: The environment variable to retrieve.
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *_getenv(char *var);
/* END BUILT INS */
/* STRING TO INT */
/**
 * _atoi - converts string to int
 * @str: string to be converted
 * Return: returns an integer
*/
int _atoi(char *str);
/* END OF STRING TO INT */
/*CHECK STAGES*/
/**
 * hasSymbols - it checks if symbols exists if
 *                   exists breaks the command into list
 * @sh: global variable in struct
 *
 * Return: returns 1 if true and 0 if false
*/
int hasSymbols(g_var **sh);
/*CHECK STAGES*/
/* START EXTRA STRINGS  */
/**
 * str_buff - convert int to str
 * @buf: buffer to be updated
 * @n: number to be converted
 * @len: length of the string
 * Return: returns the updated buffer
*/
char *str_buff(char **buf, int n, int len);
/**
 * int_str - convert int to str
 * @buf: buffer to be updated
 * @n: number to be converted
 * @len: length of the string
 * Return: returns the updated buffer
*/
char *int_str(char *buf, int n, int len);
/**
 * int_len - finds the length of an in
 * @n: integer to find length for
 * Return: returns ength of int
*/
int int_len(int n);
/* END EXTRA STRINGS */
/* PIPES COMMANDS START */
/**
 * ex_pipes - Execute commands with pipes recursively.
 * @sh: Pointer to global variable structure.
 * @pipe: pointer to cmd of pipe list
 */
void ex_pipes(g_var **sh, ppl **pipe);
/**
 * process_pipes - Process commands from the command list.
 * @h: Pointer to the command list.
 * @sh: Pointer to the shell structure.
 * @head: Pointer to the command node list.
 * Return: Number of nodes processed.
 */
size_t process_pipes(const cmd_list *h, g_var *sh, cmd_n_list **head);
/**
 * proc_pip - Process commands from the command list.
 * @pip: Pointer to the command list.
 * @sh: Pointer to the shell structure.
 * @head: Pointer to the command node list.
 * Return: Number of nodes processed.
 */
size_t proc_pip(g_var *sh, cmd_n_list **head, ppl **pip);
/**
 * free_list - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_list(ppl **h);
/**
 * proces_buf - process buffer
 * @sh: global variables
 * @buf: buffer to be processed
*/
void proces_buf(g_var **sh, char *buf);
void rplaceSp(char *str);
/**
 * remove_spaces - remove all white spaces
 * @string: string to remove white spaces
 *
*/
void remove_spaces(char *string);
/**
 * proces_buf - process buffer
 * @sh: global variables
 * @buf: buffer to be processed
*/
void proces_buf(g_var **sh, char *buf);
/**
 * handle_error - Print an error message and exit.
 * @message: The error message to print.
 */
void handle_error(const char *message);
/**
 * free_pip - frees all the node in a list and reset the head to NULL.
 * @h: pointer of pointer to a list.
 */
void free_pip(ppl **h);
/* PIPES COMMANDS END */
#endif /*SHELL_H*/
