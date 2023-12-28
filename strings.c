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
		// if (src[j] == '\n')
		// 	continue;
		dest[j + i] = src[j];
	}

	dest[i + 1] = '\0';
}


// void _append_tokens(char **dest, char **src)
// {

// }

/**
 * _count_tokens - Count the number of tokens and if there are characters in array
 *
 * @array: Character array to search
 * @target: Any character saying all characters up until this point is a token
 */
unsigned int _count_tokens(char *array, char target)
{
	unsigned int count = 0, i = 0;
	char flag = '-';

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


unsigned int _get_token_size(char *src, char target)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == target)
		{
			break;
		}
	}
	return (i);
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
 * _strlen - Find the length of a string
 * @src: Character array to find the length of
 * Return - The length of the string
 */
int _strlen(char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		i++;
	}

	return i;
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
		// if (src[i] == '\n')
		// 	continue;
		dest[i] = src[i];
	}

	dest[i] = '\0';
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

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
}

void _strncpy_token(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}


/**
 * _strcmp - Compare and find string needle in haystack.
 *
 * @haystack: String to search
 * @needle: String to find
 *
 * Return - 1 if found, 0 otherwise 
 */
int _strcmp(char *haystack, char *needle)
{
	int found = 1;

	for (int i = 0; needle[i] != '\0'; i++)
	{
		if (haystack[i] != needle[i])
		{
			found = 0;
		}
	}

	return found;
}

/**
 * tokenize - Create tokens, which are character arrays, from inputs given by the user
 *
 * @usr_input - struct that holds a string to search and tokenized strings
 */
void tokenize(command_t *input, char target)
{
	/**
		count number of tokens (characters separated by spaces)
		allocate an array of type token_t based off of number of tokens
		allocate enough space for an array of characters which represents a token
	*/
	char *tmp = NULL;
	int token_size = 0;

	input->token_count = _count_tokens(input->input, target);
	input->tokens = _init_memory(input->token_count * sizeof(char *));
	printf("token_count: %i\n", input->token_count);


	if (input->tokens == NULL)
	{
		_cleanup_and_exit(1, 1, input);
	}


	tmp = input->input;
	for (unsigned int i = 0; i < input->token_count; i++)
	{
		token_size = _get_token_size(tmp, target);
		input->tokens[i] = _strtok(tmp, token_size);
		if (input->tokens[i] == NULL)
		{
			_cleanup_and_exit(1, 1, input);
		}
		
		tmp += token_size;

		// increment the pointer past target to get next token
		if (tmp[0] == target)
		{
			tmp++;
		}
	}

	// for (unsigned int i = 0; i < input->token_count; i++)
	// {
	// 	printf("%s\n", input->tokens[i]);
	// }
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
// char *_strtok(char *src, char target)
char *_strtok(char *src, unsigned int token_size)
{
	char *new_token = NULL;

	// token_size + 1 to account for null terminated string
	new_token = _init_memory(token_size + 1 * sizeof(char));
	if (new_token == NULL)
	{
		return (NULL);
	}
	printf("string: %s\n", src);
	printf("token_size: %i\n", token_size);
	_strncpy_token(new_token, src, token_size);


	return (new_token);
}


void _search_environ(char **dest, char *target)
{
	for (int i = 0; environ[i]; i++)
	{
		if (_strcmp(environ[i], target))
		{
			*dest = environ[i];
			break;
		}
	}
}


char *_filter(char *dest, char *target)
{
	int i = 0;
	while (target[i] != '\0')
	{
		if (target[i] == dest[i])
		{
			i++;
		}
	}

	return (dest + i);
}
