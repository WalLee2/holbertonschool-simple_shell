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
		if (src[j] == '\n')
			continue;
		dest[j + i] = src[j];
	}

	dest[i + j] = '\0';
}


// void _append_tokens(command_t *usr_input, command_t *paths)
// {
// 	unsigned int new_size = 0;

// 	// for (unsigned int i = 0; i < paths->token_count; i++)
// 	// {
// 	// 	new_size = usr_input->tokens[j]->size + paths->tokens[i]->size + 1;
// 	// 	paths->tokens[i]->size = new_size;
// 	// 	_resize(&paths->tokens[i]->string, new_size);
// 	// 	_append(paths->tokens[i]->string, usr_input->tokens[0]->string);
// 	// }

// 	for (unsigned int i = 0; usr_input->tokens[i]->string != NULL; i++)
// 	{
// 		new_size = usr_input->tokens[j]->size + paths->tokens[i]->size + 1;

// 	}
// }


void _resize_append(command_t *input, char *target)
{
	int new_size = 0;

	printf("In _resize_append\n");
	for (unsigned int i = 0; input->tokens[i] != NULL; i++)
	{
		// new_size = input->tokens[i]->size + 1;
		new_size = _strlen(input->tokens[i]) + _strlen(target) + 1;
		_resize(&input->tokens[i], new_size);
		_append(input->tokens[i], target);
	}
	printf("Finished _resize_append");
}


/**
 * _count_tokens - Count the number of tokens and if there are characters in array
 *
 * @array: Character array to search
 * @target: Any character saying all characters up until this point is a token
 */
unsigned int _count_tokens(char *array, char *target)
{
	unsigned int count = 0, i = 0;

	for (; array[i] != '\0'; i++)
	{
		if(_seek(target, array[i]) || array[i + 1] == '\0')
		{
			count++;
		}
	}
	return (count);
}



// int _check_command(command_t *usr_input, command_t *paths)
// {
// 	int status = 0, i = 0;


// 	for (; paths->tokens[i] != NULL; i++)
// 	{


// 	}
// 	// printf("%s\n", usr_input->tokens[0]);
// 	return (status);
// }

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


// void _prune_paths(command_t *paths)
// {
// 	struct stat st;

// 	unsigned int i, valid_paths = 0;

// 	for (i = 0; i < paths->token_count; i++)
// 	{
// 		printf("%s ", paths->tokens[i]->string);
// 		if (stat(paths->tokens[i]->string, &st) == -1)
// 		{
// 			// free(paths->tokens[i]->string);
// 			printf("Not Found!\n");
// 		}
// 		else
// 		{
// 			printf("Found!\n");
// 			valid_paths++;
// 		}
// 	}
// 	printf("Valid paths count: %i\n", valid_paths);
// 	// paths->token_count = valid_paths;

// 	// for (unsigned int i = 0; i < paths->token_count; i++)
// 	// {
// 	// 	printf("token: %s\n", paths->tokens[i]->string);
// 	// }
// }

/**
 * _seek - Find a character in an array
 *
 * @src: Array to search through
 * @c: Target character to find
 * Return - 1 if found and 0 otherwise
 */
int _seek(char *src, char c)
{
	char special[] = {'\n', '\t', ' '};

	for (int i = 0; src[i] != '\0'; i++)
	{
		if (special[i] == c || src[i] == c)
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
 */
void _strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
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
void tokenize(command_t *input, char *target)
{
	/**
		count number of tokens (characters separated by spaces)
		allocate an array of type token_t based off of number of tokens
		allocate enough space for an array of characters which represents a token
	*/
	char *tmp = NULL;

	input->token_count = _count_tokens(input->input, target);
	printf("token count: %i\n", input->token_count);
	input->tokens = _init_memory(input->token_count * sizeof(char *));


	if (input->tokens == NULL)
	{
		_cleanup_and_exit(1, 1, input);
	}

	tmp = input->input;
	unsigned int i = 0, token_size = 0;

	printf("tmp: %s\n", tmp);
	while (*tmp != '\0')
	{
		input->tokens[i] = _strtok(tmp, target);
		token_size = _strlen(input->tokens[i]);
		printf("i: %i\n", i);
		if (token_size)
		{
			tmp += token_size;
		}
		else
		{
			printf("*tmp: %c", *tmp);
			break;
		}
		if (_seek(target, *tmp))
		{
			tmp++;
		}
		i++;
	}
	input->tokens[i] = NULL;
	for (unsigned int i = 0; i <= input->token_count; i++)
	{
		printf("token [%d]: %s\n", i, input->tokens[i]);
	}
	printf("Finished printing tokens!\n");
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
// char *_strtok(char *src, unsigned int token_size)
char *_strtok(char *src, char *target)
{
	char *new_token = NULL;
	unsigned int i = 0;


	if (!src)
	{
		return (new_token);
	}

	for (; src[i] != '\0'; i++)
	{
		if (_seek(target, src[i]))
		{
			new_token = _init_memory(i + 1 * sizeof(char));
			if (new_token == NULL)
			{
				return (NULL);
			}
			_strncpy_token(new_token, src, i);
			break;
		}
	}
	/*
	Account for the last token where there could be no target character
	that indicates when to stop
	*/
	if (src[i] == '\0' && new_token == NULL)
	{
		new_token = _init_memory(i + 1 * sizeof(char));
		if (new_token == NULL)
		{
			return (NULL);
		}
		_strncpy_token(new_token, src, i);
	}
	printf("new token: %s\n", new_token);
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
