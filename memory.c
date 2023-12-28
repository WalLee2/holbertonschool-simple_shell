#include "shell.h"


/**
 * _cleanup - Function used to free up memory if unexpected behavior occurs and we need to exit
 *
 * @msg: Error message to print to standard output
 * @exit_code: integer value to exit the program with 
 * @n: Number of structs that need to free-ing before exiting program
 */
// void _cleanup(const char *msg, const int exit_code, command_t *buf)
void _cleanup_and_exit(const int exit_code, const int n, ...)
{
	va_list ap;
	command_t *buf = NULL;

	exit_codes_t codes[] = {
		{1, "Unable to allocate memory!\n"},
		{2, "Failed to initialize struct usr_input!\n"},
		{100, "Testing!\n"},
		{-1, NULL}
	};

	va_start(ap, n);
	for (int i = 0; i < n; i++)
	{
		buf = va_arg(ap, command_t *);
		_clean_up_mem(1, buf);
	}
	va_end(ap);

	for (int i = 0; codes[i].msg != NULL; i++)
	{
		if (codes[i].code == exit_code)
		{
			printf("%s", codes[i].msg);
			exit(codes[i].code);
		}
	}
}

void _clean_up_mem(const int n, ...)
{
	va_list ap;
	command_t *buf = NULL;

	va_start(ap, n);
	for (int i = 0; i < n; i++) 
	{
		buf = va_arg(ap, command_t *);
		if (buf)
		{
			if (buf->input != NULL)
			{
				free(buf->input);
			}
			if (buf->tokens)
			{
				for (unsigned int i = 0; i < buf->token_count; i++)
				{
					free(buf->tokens[i]);
					buf->tokens[i] = NULL;
				}
				free(buf->tokens);
				buf->tokens = NULL;
			}
			free(buf);
			buf = NULL;
		}
	}
	va_end(ap);
}

/**
 * _init_memory - Create dynamically allocated space and properly wipe any previous memory
 *
 * @size: total size of dynamic memory
 *
 * Return - void pointer to the created memory
 */
void *_init_memory(const unsigned int size)
{
	ssize_t i;
	void *new = NULL;
	char *ptr = NULL;

	new = malloc(size);
	if (!new)
		return (NULL);

	ptr = new;
	for (i = 0; i < size; i++)
		ptr[i] = '\0';

	return (new);
}


/**
 * _resize - Resize previously created dynamic memory and free it after contents have been
 * properly copied over
 *
 * @buf: Double pointer to dynamic memory that needs to be resized
 * @size: constant unsigned int of previous size of dynamic memory
 *
 * Return - New size of the resized array 
 */
unsigned int _resize(char **buf, const unsigned int size)
{
	char *tmp = *buf;
	int new_size = size * 2 * sizeof(char);

	*buf = _init_memory(new_size);

	if (!buf)
		return (0);

	_strcpy(*buf, tmp);
	free(tmp);

	return (new_size);
}
