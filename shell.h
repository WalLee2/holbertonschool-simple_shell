#ifndef SHELL_H
#define SHELL_H
#define HELP_SIZE 10

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

extern char **environ;

/**
 * struct commands - struct that holds input strings to be made into tokens for further action
 * @input: string to tokenize
 * @input_size: character count of input string
 * @tokens: input string turned into an array of strings
 * @token_count: total number of tokens
 */
typedef struct commands {
	char *input;
	unsigned int input_size;
	char **tokens;
	unsigned int token_count;
} command_t;

/**
 * exit_codes - struct that holds all exit codes and failure mode messages
 * @code: Integer code that is the reason for failure
 * @msg: Reason for failure in English
 */
typedef struct exit_codes {
	int code;
	char *msg;
} exit_codes_t;


// typedef struct token {
// 	char *str;
// 	unsigned int size;
// }

/** String functions **/
void _append(char *dest, char *src);
unsigned int _count_tokens(char *array, char target);
unsigned int _get_token_size(char *src, char target);
int _seek(char *src, char c);
void _strcpy(char *dest, char *src);
void _strncpy(char *dest, char *src, int n);
void _strncpy_token(char *dest, char *src, int n);
int _strlen(char *src);
void tokenize(command_t *usr_input, char target);
// char *_strtok(char *src, char target);
char *_strtok(char *src, unsigned int token_size);
int _strcmp(char *haystack, char *needle);
void _search_environ(char **dest, char *target);
char *_filter(char *dest, char *target);



/** Memory functions **/
void *_new_mem(const unsigned int size);
void *_init_memory(const unsigned int size);
unsigned int _resize(char **buf, const unsigned int size);
void _cleanup_and_exit(const int exit_code, const int n, ...);
void _clean_up_mem(const int n, ...);

/** IO functions **/
ssize_t _getline(command_t *lineptr, int fd);
void _get_path(command_t *paths);

/** main functions **/
void initialize(command_t **usr_input);
void get_command(command_t *usr_input);
int check_command(command_t *usr_input);


#endif
