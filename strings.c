#include "shell.h"


/**
 * _append - Add characters to the end of a character array
 *
 * @dest: Character array to add
 * @src: Character array to copy from
 */
void _append(char *dest, char *src)
{
	int i;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (int j = 0; src[j] != '\0'; j++)
	{
		if (src[j] == '\n')
			continue;
		dest[j + i] = src[j];
	}

	dest[i + 1] = '\0';
}


/**
 * _count_tokens - Count the number of tokens and if there are characters in array
 *
 * @array: Character array to search
 * @target: Any character saying all characters up until this point is a token
 */
unsigned int _count_tokens(char *array, char target)
{
	unsigned int count = 0, i = 0;

	for (; array[i] != '\0'; i++)
	{
		if (array[i] == target)
		{
			count++;
		}
	}
	if (i > 0)
	{
		count += 1;
	}
	return (count);
}

/**
 * _seek - Find a character in an array
 *
 * @src: Array to search through
 * @c: Target character to find
 * Return - 1 if found and 0 otherwise
 */
int _seek(char *src, char c)
{
	for (int i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == c)
			return 1;
	}
	return 0;
}


/**
 * _strcpy - Copy one character array to another
 *
 * @dest: Destination array to copy to
 * @src: Source array to copy from
 */
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

/**
 * _strncpy - Copy n number of characters from source array to destination array
 *
 * @dest: Destination array to copy to
 * @src: Source array to copy from
 * @n: Number of characters to copy
 */
void _strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}

	if (i == n - 1)
	{
		dest[i + 1] = '\0';
	}
}


/**
 * tokenize - Create tokens, which are character arrays, from inputs given by the user
 *
 * @usr_input - struct that holds user input and tokenized inputs
 */
void tokenize(command_t *usr_input)
{
	/**
		count number of tokens (characters separated by spaces)
		allocate an array of type token_t based off of number of tokens
		allocate enough space for an array of characters which represents a token
	*/
	char *tmp = NULL;
	char target = ' ';

	usr_input->token_count = _count_tokens(usr_input->input, target);
	usr_input->tokens = _init_memory(usr_input->token_count * sizeof(char *));

	if (usr_input->tokens == NULL)
	{
		char *msg = "Unable to allocate memory!\n";
		_cleanup(usr_input, msg, 1);
	}

	tmp = usr_input->input;
	for (unsigned int i = 0; i < usr_input->token_count; i++)
	{
		usr_input->tokens[i] = _strtok(tmp, target);
		if (usr_input->tokens[i] == NULL)
		{
			char *msg = "Unable to allocate memory!\n";
			_cleanup(usr_input, msg, 1);
		}
	}
}


/**
 * _strtok - Get the size of each token delimited by some target character
 * copy the string into new dynamically allocated memory
 *
 * @src: Array to search
 * @target: Any character saying all characters up until this point is a token
 *	
 * Return - New character array
 */
char *_strtok(char *src, char target)
{
	char *new_token = NULL;
	int token_size = 0;

	for (int i = 0; src[i] != '\0'; i++, token_size++)
	{
		if (src[i] == target)
		{
			break;
		}
	}

	new_token = _init_memory(token_size * sizeof(char));
	if (new_token == NULL)
	{
		return (NULL);
	}
	_strncpy(new_token, src, token_size);
	src += token_size;

	return (new_token);
}

