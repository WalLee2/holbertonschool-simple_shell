#include "shell.h"

/**
 * _run_builtin - function to run built in commands
 * @usr_input: struct that holds user input and tokenized inputs
 * @paths: struct that holds all directories found in PATH environment variable
 * Return: 1 means successful run of builtin command and 0 on failure
 */
int _run_builtin(command_t *usr_input, command_t *paths)
{
	if (_strcmp(usr_input->tokens[0], "exit"))
	{
		_cleanup_and_exit(0, 2, usr_input, paths);
		return (1);
	}
	return (0);

}
