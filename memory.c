#include "shell.h"

void *_new_mem(ssize_t n, const unsigned int size)
{
	void *tmp = malloc(n * size);

	return ((tmp ? tmp : NULL));
}

void *_init_mem(ssize_t n, const unsigned int size)
{
	ssize_t i;
	void *new;
	char *ptr;

	new = _new_mem(n, size);
	if (!new)
		return (NULL);

	ptr = new;
	for (i = 0; i < n; i++)
		ptr[i] = '\0';

	return (new);
}

void _resize(char **buf, ssize_t *size)
{
	char *tmp = *buf;

	*size *= 2;
	*buf = _init_mem(*size, sizeof(char));
	_strcpy(*buf, tmp);
	free(tmp);
}
