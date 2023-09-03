#include "shell.h"

void _append(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		if (src[j] == '\n')
			continue;
		dest[j + i] = src[j];
	}

	dest[i + 1] = '\0';
}

int _seek(char *src, char c)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == c)
			return 1;
	}
	return 0;
}

void _strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == '\n')
			continue;
		dest[i] = src[i];
	}

	dest[i + 1] = '\0';
}
