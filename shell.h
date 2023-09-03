#ifndef SHELL_H
#define SHELL_H
#define HELP_SIZE 10

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


/** String functions **/
void _append(char *dest, char *src);
int _seek(char *src, char c);
void _strcpy(char *dest, char *src);

/** Memory functions **/
void *_new_mem(ssize_t n, const unsigned int size);
void *_init_mem(ssize_t n, const unsigned int size);
void _resize(char **buf, ssize_t *size);

/** IO functions **/
ssize_t _getline(char **lineptr, int fd);
void get_input(char *tokens);

/** main functions **/
void get_cmds(char **cmds);


#endif
