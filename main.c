#include "shell.h"

int main(void)
{

	command_t *usr_input = NULL;
	command_t *paths = NULL;

	initialize(&usr_input, &paths);
	while (1)
	{
		get_command(usr_input);
		get_path(paths);
		// for (unsigned int i = 0; i < usr_input->token_count; i++)
		// {
		// 	printf("usr in: %s\n", usr_input->tokens[i]);
		// }
		// for (unsigned int i = 0; i < paths->token_count; i++)
		// {
		// 	printf("paths: %s\n", paths->tokens[i]);
		// }
		execute(usr_input, paths);
	}
	return (0);
}


/**
 * initialize - Write prompt to standard output and allocate memory
 * to collect user input
 *
 * @usr_input: struct that holds user input and tokenized inputs
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
	printf("get_command character: %s", usr_input->input);
	tokenize(usr_input, target);
}

/**
 * check_command - Take tokenized inputs and append them to directory paths
 * found in PATH environment variable
 * Use the stat system call to see if input exists in new directory path
 *
 * @usr_input: struct that holds user input and tokenized inputs
 */
void execute(command_t *usr_input, command_t *paths)
{
	// char *new = NULL;
	struct stat st;

	_resize_append(paths, usr_input->tokens[0]);

	// char *argv[] = {"/usr/bin/ls", "-la", "/usr/", NULL};
	for (unsigned int i = 0; paths->tokens[i] != NULL; i++)
	{
 		if (stat(paths->tokens[i], &st) == 0)
		{
			printf("%s\n", paths->tokens[i]);
			// free(usr_input->tokens[0]);
			// usr_input->tokens[0] = _init_memory(_strlen(paths->tokens[i]) + 1 * sizeof(char));
			// new = _init_memory(_strlen(paths->tokens[i]) + 1 * sizeof(char));
			// _strcpy(new, paths->tokens[i]);
			// printf("new: %s\n", new);
			for (unsigned int i = 0; i < usr_input->token_count; i++)
			{
				for (int j = 0; usr_input->tokens[i][j] != '\0'; j++)
				{
					printf("%i\n", usr_input->tokens[i][j]);
				}
				printf("\n");
			}
			_run_process(paths->tokens[i], usr_input->tokens);
			// free(new);
			// if (execve(usr_input->tokens[0], usr_input->tokens, NULL) == -1)
			// {
			// 	perror("Error:");
			// }
			break;
		}

	}



	// for (unsigned int i = 0; argv[i] != NULL; i++)
	// {
	// 	printf("token: %s\n", argv[i]);
	// }

	// _append_tokens(usr_input, paths);
	// _prune_paths(paths);


	printf("Freeing paths!\n");
	_cleanup_and_exit(100, 2, usr_input, paths);
}

