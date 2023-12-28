#include "shell.h"

int main(void)
{

	command_t *usr_input = NULL;

	initialize(&usr_input);
	while (1)
	{
		get_command(usr_input);
		check_command(usr_input);
		/**
		execute();
		**/
	}
	return (0);
}


/**
 * initialize - Write prompt to standard output and allocate memory
 * to collect user input
 *
 * @usr_input: struct that holds user input and tokenized inputs
 */
void initialize(command_t **usr_input)
{
	write(STDOUT_FILENO, "$ ", 2);

	*usr_input = _init_memory(sizeof(command_t));
	if (!(*usr_input))
	{
		_cleanup_and_exit(1, 1, usr_input);
	}
}


/**
 * get_command - Get user input and tokenizes those inputs delimited by a space
 * @usr_input: struct that holds user input and tokenized inputs
 */
void get_command(command_t *usr_input)
{
	char target = ' ';

	if (!usr_input)
	{
		_cleanup_and_exit(2, 1, usr_input);
	}
	usr_input->input_size = _getline(usr_input, STDOUT_FILENO);
	tokenize(usr_input, target);
}

/**
 * check_command - Take tokenized inputs and append them to directory paths
 * found in PATH environment variable
 * Use the stat system call to see if input exists in new directory path
 *
 * @usr_input: struct that holds user input and tokenized inputs
 */
int check_command(command_t *usr_input)
{
	command_t *paths = NULL;
	paths = _init_memory(sizeof(command_t));

	_get_path(paths);
	// _append_tokens(usr_input->tokens, paths->tokens);
	printf("Freeing paths!\n");
	_cleanup_and_exit(100, 2, usr_input, paths);

	/**
	stat()
	*/
	return (1);
}

