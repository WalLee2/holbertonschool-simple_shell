#include "shell.h"

ssize_t _getline(char **lineptr, int fd)
{
	char *buf, helper[HELP_SIZE];
	int rb;
	ssize_t total = 0, buf_size = HELP_SIZE;

	buf = _init_mem(buf_size, sizeof(char));
	if (!buf)
		return (-1);

	while ((rb = read(fd, helper, HELP_SIZE)) > 0)
	{
		total += rb;
		if (total >= buf_size)
		{
			_resize(&buf, &buf_size);
			if (!buf)
				return (-1);
		}
		if (buf[0] == '\0')
			_strcpy(buf, helper);
		else
			_append(buf, helper);
		if (_seek(helper, '\n'))
			break;
	}
	*lineptr = buf;
	return (total);
}
