#include "shell.h"


void _get_path(command_t *paths)
{
	char *target = "PATH=", *tmp = NULL;

	_search_environ(&tmp, target);
	tmp = _filter(tmp, target);
	paths->input_size = _strlen(tmp);
	// paths->input_size + 1 to account for null termianted string
	paths->input = _init_memory(paths->input_size + 1 * sizeof(char));
	_strcpy(paths->input, tmp);
	// printf("input_size: %i\n", paths->input_size);

	tokenize(paths, ':');

	// printf("token count: %i\n", paths->token_count);
	// printf("token: %s\n", paths->tokens[0]);
	for (unsigned int i = 0; i < paths->token_count; i++)
	{
		printf("token: %s\n", paths->tokens[i]);
	}
}

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
			_append(buf, helper);
		}
		if (_seek(helper, '\n'))
			break;
	}
	usr_input->input = buf;

	return (total);
}
