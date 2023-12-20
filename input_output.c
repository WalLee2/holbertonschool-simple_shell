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
		char *msg = "Unable to allocate memory!\n";
		_cleanup(usr_input, msg, 1);
	}

	while ((read_bytes = read(fd, helper, HELP_SIZE)) > 0)
	{
		total += read_bytes;
		if (total >= buf_size)
		{
			buf_size = _resize(&buf, buf_size);
			if (!buf)
			{
				char *msg = "Unable to allocate memory!\n";
				_cleanup(usr_input, msg, 1);
			}
		}
		if (buf[0] == '\0')
		{
			_strcpy(buf, helper);
		}
		else
		{
			_append(buf, helper);
		}
		if (_seek(helper, '\n'))
			break;
	}
	usr_input->input = buf;

	return (total);
}
