#include "shell.h"


/**
 * _append - Add characters to the end of a character array
 *
 * @dest: Character array to add
 * @src: Character array to copy from
 */
void _append(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[j + i] = src[j];
	}

	dest[i + j] = '\0';
}

/**
 * _append - Add characters to the end of a character array up to n bytes
 *
 * @dest: Character array to add
 * @src: Character array to copy from
 * @n: The max number of bytes to be copied from src to dest
 */
void _append_n(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[j + i] = src[j];
	}

	dest[i + j] = '\0';
}
/**
 * _resize_append - function that resizes buffer and appends to the end of a buffer
 * @input: struct containing the pointer to buffer to resize
 * @target: character that indicates when to start appending
 */
int _resize_append(command_t *input, char *target)
{
	int new_size = 0;

	for (unsigned int i = 0; input->tokens[i] != NULL; i++)
	{
		new_size = _strlen(input->tokens[i]) + _strlen(target) + 1;
		new_size = _resize(&input->tokens[i], new_size);
		if (!new_size)
		{
			return (5);
		}
		_append(input->tokens[i], target);
	}
	return (0);
}


/**
 * _count_tokens - Count the number of tokens and if there are characters in array
 *
 * @array: Character array to search
 * @target: Any character saying all characters up until this point is a token
 */
unsigned int _count_tokens(char *array, char *target)
{
	unsigned int count = 0;

	for (int i = 0; array[i] != '\0'; i++)
	{
		if(_seek(target, array[i]) || array[i + 1] == '\0')
		{
			count++;
		}
	}
	return (count);
}



/**
 * _check_directories - if user provides a directory to execute ensure that
 * the directory is in the PATH
 * @paths: struct that holds all directories found in PATH
 * @target: The directory provided by the user to check
 * Return - 1 if directory provided by the user is found in PATH and 0 otherwise.
 */
int _check_directories(command_t *paths, char *target)
{
	int found = 0;
	char *filtered = _init_memory((_strlen(target) + 1) * sizeof(char));

	_strcpy(filtered, target);
	filtered = _reverse_filter_until_c(filtered, '/');


	for (unsigned int i = 0; i < paths->token_count; i++)
	{
		if (_strcmp(paths->tokens[i], filtered))
		{
			found = 1;
		}
	}
	free(filtered);

	return (found);
}

/**
 * _get_token_size - get size of the token up until a target character
 * @src: Source array to search
 * @target: Character array that contains target characters to stop count and return
 * Return - The length of a token
 */
unsigned int _get_token_size(char *src, char *target)
{
	int i = 0;

	for (; src[i] != '\0'; i++)
	{
		for (int j = 0; target[j] != '\0'; j++)
		{
			if (src[i] == target[j])
			{
				return (i);
			}
		}
	}
	return (i);
}


/**
 * _seek - Find a character in an array
 *
 * @src: Array to search through
 * @c: Target character to find
 * Return - 0 if not found 1 if found
 */
int _seek(char *src, char c)
{
	for (int i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == c)
		{
			return (1);
		}
	}
	return (0);
}


/**
 * _strlen - Find the length of a string
 * @src: Character array to find the length of
 * Return - The length of the string
 */
int _strlen(char *src)
{
	int i = 0;

	while (src != NULL && src[i] != '\0')
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
 * Return - 0 on failure and 1 on success
 */
int _strcpy(char *dest, char *src)
{
	int i = 0;

	if (!src)
	{
		return (0);
	}
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (1);
}

/**
 * _strncpy - Copy n number of characters from source array to destination array
 *
 * @dest: Destination array to copy to
 * @src: Source array to copy from
 * @n: Number of characters to copy that can fit in dest array
 * Return - 0 on failure and 1 on success
 */
int _strncpy(char *dest, char *src, int n)
{
	int i = 0;

	if (!src)
	{
		return (0);
	}
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (1);
}

/**
 * _strncpy_token - Copy n number of characters from source to destination array and append '\0'
 * @dest: Destination array to copy to
 * @src: Source array to copy from
 * @n: Number of characters that can fit in destination array
 * Return - 0 on failure and 1 on success
 */
int _strncpy_token(char *dest, char *src, int n)
{
	int i = 0;

	if (!src)
	{
		return (0);
	}
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (1);
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

	for (int i = 0; needle[i] != '\0'; i++)
	{
		if (haystack[i] != needle[i])
		{
			return (0);
		}
	}

	return (1);
}

/**
 * tokenize - Create tokens, which are character arrays, from inputs given by the user
 *
 * @usr_input: struct that holds a string to search and tokenized strings
 * @target: Characters that would indicate the end of a token
 */
void tokenize(command_t *input, char *target)
{
	/**
		count number of tokens (characters separated by target character)
		allocate an array of chars based off of number of tokens
		allocate enough space for an array of characters which represents a token
	*/
	char *tmp = NULL;

	input->token_count = _count_tokens(input->input, target);
	input->tokens = _init_memory((input->token_count + 1) * sizeof(char *));


	if (input->tokens == NULL)
	{
		input->tokens[0] = NULL;
		return;
	}

	tmp = input->input;
	unsigned int i = 0, token_size = 0;

	while (*tmp != '\0' || tmp != NULL)
	{
		input->tokens[i] = _strtok(tmp, target);
		token_size = _strlen(input->tokens[i]);
		if (token_size)
		{
			tmp += token_size;
		}
		else
		{
			break;
		}
		if (_seek(target, *tmp))
		{
			tmp++;
		}
		i++;
	}
	input->tokens[i] = NULL;
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
char *_strtok(char *src, char *target)
{
	char *new_token = NULL, *tmp = NULL;
	unsigned int i = 0;


	if (!src)
	{
		return (new_token);
	}

	tmp = src;
	for (; tmp[i] != '\0'; i++)
	{
		if (_seek(target, tmp[i]))
		{
			new_token = _init_memory((i + 1) * sizeof(char));
			if (new_token == NULL)
			{
				return (NULL);
			}
			if(!(_strncpy_token(new_token, src, i)))
			{
				return (NULL);
			}
			break;
		}
	}
	/*
	Account for the last token where there could be no target character
	that indicates the end of a token
	*/
	if (src[i] == '\0' && new_token == NULL && i > 0)
	{
		new_token = _init_memory((i + 1) * sizeof(char));
		if (new_token == NULL)
		{
			return (NULL);
		}
		if(!(_strncpy_token(new_token, src, i)))
		{
			return (NULL);
		}
	}
	return (new_token);
}


/**
 * _search_environ - Retrieve and search through the current working environment for variables of interest
 * @dest: The pointer to the environment variable of interest
 * @target: The characters that would be in the environment variable of interest
 */
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

/**
 * _filter - Ignore certain words by moving a pointer forward by x amount of characters
 * @dest: string to filter
 * @target: characters to ignore which moves the pointer to string forward
 * Return - NULL if neither dest or target exist. Pointer to the new location in the string otherwise
 */
char *_filter(char *dest, char *target)
{
	int i = 0;
	if (!target || !dest)
	{
		return (NULL);
	}
	while (target[i] != '\0')
	{
		if (target[i] == dest[i])
		{
			i++;
		}
	}

	return (dest + i);
}

/**
 * _reverse_filter_until_c - Ignore characters from the end of a string
 * until a target character is found
 * @dest: The string to evaluate
 * @target: The character to stop appending the null termintor to
 * Return - Pointer to the new string
 */
char *_reverse_filter_until_c(char *dest, char target)
{
	char *tmp = NULL;
	int len = 0;

	len = _strlen(dest);

	tmp = dest;
	for (int i = 0; dest[i] != '\0'; i++)
	{
		tmp++;
	}
	for (int i = len; *tmp != target && i > 0; i--, tmp--)
	{
		dest[i] = '\0';
	}

	return (dest);
}
