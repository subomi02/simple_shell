#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _putchar(char);
void shell_loop(void);
void non_interractive(void);
int check_cmd_type(char *command);
int check_cmd_type(char *command);
int _atoi(char *s);
void remove_comment(char *input);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(char *key);
char *check_path(char *file);
void ctrl_C_func(int signum);
char *shell_readline(void);
void shell_launch(char **proccessed_cmd, int cmd_type);
void (*get_func(char *command))(char **);
void env(char **tokenized_command __attribute__((unused)));
void quit(char **tokenized_command);
int is_delimeter(const char *delimeters, char c);
char **tokenize(char *str, const char *delim);
int _strcmp(char *first, char *second);
void free_tokenized(char **tokens);

#endif
