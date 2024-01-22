#include "shell.h"


/**
 * _getline - Get all characters entered by a user
 *
 * @usr_input: struct that holds user input and tokenized inputs
 * @fd: File descriptor used to read characters from standard input
 *
 * Return - Total bytes read from standard input
 */
ssize_t _getline(command_t *usr_input, int fd)
{
	char *buf = NULL;
	char helper[HELP_SIZE] = {0};
	int read_bytes = 0;
	unsigned int buf_size = HELP_SIZE, total = 0;


	buf = _init_memory(buf_size * sizeof(char));
	if (!buf)
	{
		_cleanup_and_exit(1, 1, usr_input);
	}

	while ((read_bytes = read(fd, helper, HELP_SIZE)) > 0)
	{
		total += read_bytes;
		if (total >= buf_size)
		{
			buf_size = _resize(&buf, buf_size);
			if (!buf)
			{
				_cleanup_and_exit(1, 1, usr_input);
			}
		}
		if (buf[0] == '\0')
		{
			_strcpy(buf, helper);
		}
		else
		{
			_append_n(buf, helper, read_bytes);
		}
		if (_seek(helper, '\n'))
			break;
	}
	usr_input->input = buf;
	return (total);
}


/**
 * _run_process - run a command in a child process
 * @command: The command to be ran
 * @args: Array that holds user input
 */
void _run_process(char *command, char **args)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("Child process returned -1!\n");
	}
	if (child == 0)
	{
		if (execve(command, args, NULL) == -1)
		{
			perror("An error occurred when executing!\n");
		}
	}
	else
	{
		wait(&status);
	}
}