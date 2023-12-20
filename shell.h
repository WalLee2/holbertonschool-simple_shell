#ifndef SHELL_H
#define SHELL_H
#define HELP_SIZE 10

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


typedef struct commands {
	char *input;
	unsigned int input_size;
	char **tokens;
	unsigned int token_count;
} command_t;

/** String functions **/
void _append(char *dest, char *src);
unsigned int _count_tokens(char *array, char target);
int _seek(char *src, char c);
void _strcpy(char *dest, char *src);
void tokenize(command_t *usr_input);
char *_strtok(char *src, char target);

/** Memory functions **/
void *_new_mem(const unsigned int size);
void *_init_memory(const unsigned int size);
unsigned int _resize(char **buf, const unsigned int size);
void _cleanup(command_t *buf, const char *msg, const int exit_code);

/** IO functions **/
ssize_t _getline(command_t *lineptr, int fd);

/** main functions **/
void initialize(command_t **usr_input);
void get_command(command_t *usr_input);
int check_command(command_t *usr_input);


#endif
