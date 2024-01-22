#include "shell.h"

/**
 * main - Initialize structs, get user input,
 * get directories found in PATH environment variable
 * execute command if certain requirements are met
 * Return: Zero when exiting
 */
int main(void)
{

	command_t *usr_input = NULL;
	command_t *paths = NULL;

	while (1)
	{
		initialize(&usr_input, &paths);
		get_command(usr_input);
		get_path(usr_input, paths);
		execute(usr_input, paths);
	}
	return (0);
}


/**
 * initialize - Write prompt to standard output and allocate memory
 * to collect user input
 *
 * @usr_input: struct that holds user input and tokenized inputs
 * @paths: struct that holds all the different types of paths in environment
 */
void initialize(command_t **usr_input, command_t **paths)
{
	write(STDOUT_FILENO, "$ ", 2);

	*paths = _init_memory(sizeof(command_t));
	*usr_input = _init_memory(sizeof(command_t));

	if (!(*usr_input) || !(*paths))
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
	char *target = "\n ";

	if (!usr_input)
	{
		_cleanup_and_exit(2, 1, usr_input);
	}
	usr_input->input_size = _getline(usr_input, STDOUT_FILENO);
	tokenize(usr_input, target);
	if (!usr_input->tokens[0])
	{
		_cleanup_and_exit(4, 1, usr_input);
	}
}


/**
 * get_path - Get the PATH environment variable and add "/" to the end of
 * each string in PATH
 * ex: environment variable PATH=/usr/local/bin:/usr/bin:/bin
 * output: /usr/local/bin/ /usr/bin/ /bin
 * @usr_input: struct that holds user input and tokenized inputs
 * @paths: struct that holds all the different types of paths in environment
 */
void get_path(command_t *usr_input, command_t *paths)
{
	char *tmp = NULL;
	char *target[] = {"PATH=", ":", "/"};
	int status = 0;

	_search_environ(&tmp, target[0]);
	if (!tmp)
	{
		_cleanup_and_exit(3, 2, usr_input, paths);
	}

	tmp = _filter(tmp, target[0]);
	if (!tmp)
	{
		_cleanup_and_exit(6, 2, usr_input, paths);
	}

	paths->input_size = _strlen(tmp);
	paths->input = _init_memory(paths->input_size + 1 * sizeof(char));
	if (!paths->input)
	{
		_cleanup_and_exit(1, 2, usr_input, paths);
	}

	_strcpy(paths->input, tmp);
	tokenize(paths, target[1]);
	if (!paths->tokens[0])
	{
		_cleanup_and_exit(4, 2, usr_input, paths);
	}

	status = _resize_append(paths, target[2]);
	if (status)
	{
		_cleanup_and_exit(status, 2, usr_input, paths);
	}

	/*
	 *	If user gives a path to an executable check the directory to see if
	 *	it's in PATH
	 *	Otherwise append the command to all the directories found in PATH
	 */
	if (_seek(usr_input->tokens[0], target[2][0]))
	{
		if (!(_check_directories(paths, usr_input->tokens[0])))
		{
			_cleanup_and_exit(7, 2, usr_input, paths);
		}
	}
	else
	{
		status = _resize_append(paths, usr_input->tokens[0]);
		if (status)
		{
			_cleanup_and_exit(status, 2, usr_input, paths);
		}
	}
}


/**
 * execute - Take tokenized inputs and append them to directory paths
 * found in PATH environment variable
 * Use the stat system call to see if input exists in new directory path
 *
 * @usr_input: struct that holds user input and tokenized inputs
 * @paths: struct that holds all directories found in PATH environment variable
 */
void execute(command_t *usr_input, command_t *paths)
{
	unsigned int i = 0;
	int executed = 0;
	struct stat st;

	if (_seek(usr_input->tokens[0], '/'))
	{
		_run_process(usr_input->tokens[0], usr_input->tokens);
		executed = 1;
	}
	else
	{
		for (; paths->tokens[i] != NULL; i++)
		{
			if (stat(paths->tokens[i], &st) == 0)
			{
				_run_process(paths->tokens[i], usr_input->tokens);
				executed = 1;
				break;
			}
		}
	}
	if (!executed)
	{
		printf("Command '%s' not found.\n", usr_input->tokens[0]);
	}
	_cleanup_mem(2, usr_input, paths);
}

