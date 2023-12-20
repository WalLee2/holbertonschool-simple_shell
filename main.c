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
		char *msg = "Unable to allocate memory!\n";
		_cleanup(*usr_input, msg, 1);
	}
}


/**
 * get_command - Get user input and tokenizes those inputs delimited by a space
 * @usr_input: struct that holds user input and tokenized inputs
 */
void get_command(command_t *usr_input)
{
	if (!usr_input)
	{
		char *msg = "Failed to initialize struct usr_input!\n";
		_cleanup(usr_input, msg, 2);
	}
	usr_input->input_size = _getline(usr_input, STDOUT_FILENO);
	tokenize(usr_input);
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
	char *msg = "Debugging!\n";
	_cleanup(usr_input, msg, 100);
	/**
	paths =	get_path();
	append_tokens(cmds, paths, tokens);
	stat()
	*/
	return (1);
}

