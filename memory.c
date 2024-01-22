#include "shell.h"


/**
 * _cleanup_and_exit - Function used to free up memory and to exit
 * @exit_code: integer value to exit the program with
 * @n: Number of structs that need to free-ing before exiting program
 */
void _cleanup_and_exit(const int exit_code, const int n, ...)
{
	va_list ap;
	command_t *buf = NULL;
	int i;

	exit_codes_t codes[] = {
		{1, "Unable to allocate memory!\n"},
		{2, "Failed to initialize struct usr_input!\n"},
		{3, "Environment variable does not exist!\n"},
		{4, "Failed to generate tokens!\n"},
		{5, "Failed to resize buffer!\n"},
		{6, "Unable to filter string!\n"},
		{7, "Invalid directory when executing command!\n"},
		{100, "Testing!\n"},
		{-1, NULL}
	};

	va_start(ap, n);
	for (i = 0; i < n; i++)
	{
		buf = va_arg(ap, command_t *);
		_cleanup_mem(1, buf);
	}
	va_end(ap);

	for (i = 0; codes[i].msg != NULL; i++)
	{
		if (codes[i].code == exit_code)
		{
			printf("%s", codes[i].msg);
			exit(codes[i].code);
		}
	}
}


/**
 * _cleanup_mem - Free all allocated memory
 * @n: Number of structs of type command_t to free
 * variadic function as it accomodates for more structs to free
 */
void _cleanup_mem(const int n, ...)
{
	va_list ap;
	command_t *buf = NULL;
	int i;
	unsigned int j;

	va_start(ap, n);
	for (i = 0; i < n; i++)
	{
		buf = va_arg(ap, command_t *);
		if (buf)
		{
			if (buf->input != NULL)
			{
				free(buf->input);
				buf->input = NULL;
			}
			if (buf->tokens)
			{
				for (j = 0; buf->tokens[j] != NULL; j++)
				{
					free(buf->tokens[j]);
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
 * _init_memory - Create dynamically allocated space and wipe previous memory
 * @size: total size of dynamic memory
 * Return: void pointer to the created memory
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
 * _resize - Resize previously created dynamic memory and free it
 * after contents have been properly copied over
 *
 * @buf: Double pointer to dynamic memory that needs to be resized
 * @size: constant unsigned int of previous size of dynamic memory
 *
 * Return: New size of the resized array
 */
unsigned int _resize(char **buf, const unsigned int size)
{
	char *tmp = *buf;
	int new_size = size * 2 * sizeof(char);

	*buf = _init_memory(new_size);

	if (!buf)
	{
		return (0);
	}

	_strcpy(*buf, tmp);
	free(tmp);

	return (new_size);
}
