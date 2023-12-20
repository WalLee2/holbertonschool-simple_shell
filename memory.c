#include "shell.h"


/**
 * _cleanup - Function used to free up memory if unexpected behavior occurs and we need to exit
 *
 * @buf:  Struct variable containing malloc'd memory
 * @msg:  Error message to print to standard output
 * @exit_code: integer value to exit the program with 
 */
void _cleanup(command_t *buf, const char *msg, const int exit_code)
{
	if (buf)
	{
		if (buf->input)
		{
			free(buf->input);		
		}
		if (buf->tokens)
		{
			for (unsigned int i = 0; i < buf->token_count; i++)
			{
				free(buf->tokens[i]);
			}
			free(buf->tokens);
		}

			free(buf);		
	}
	printf("%s", msg);
	exit(exit_code);
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
