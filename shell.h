
#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*  command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*  convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num:  number field
 * @str:  string
 * @next: pointer to the next node
 ***/
typedef struct liststr
{
		int num;
			char *str;
				struct liststr *next;
} list_t;

/**
 ** struct passinfo -This contains pseudo-arguments to pass into the function,
 ** allowing uniform prototype for function pointer struct
 ** @arg: String generated from getline containing the arguments
 ** @argv: Array of strings generated from arg
 ** @path: String path for the current command
 ** @argc: Argument count
 ** @line_count: An error count
 ** @err_num: An error code for exit()s
 ** @linecount_flag: When on count this line of input
 ** @fname: Program filename
 ** @env: linked-list local copy of the environ
 ** @environ: custom modified copy of the environ from LL env
 ** @history: History node
 ** @alias: Alias node
 ** @env_changed: on when environ is changed
 ** @status:  Return status of the last exec'd command
 ** @cmd_buf: The address of pointer to cmd_buf, on if chaining
 ** @cmd_buf_type: CMD_type ||, &&, ;
 ** @readfd: fd from  to read line input
 ** @histcount:  history line number count
 ***/
typedef struct passinfo
{
		char *arg;
			char **argv;
				char *path;
					int argc;
						unsigned int line_count;
							int err_num;
								int linecount_flag;
									char *fname;
										list_t *env;
											list_t *history;
												list_t *alias;
													char **environ;
														int env_changed;
															int status;

																char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
																	int cmd_buf_type; /* CMD_type ||, &&, ; */
																		int readfd;
																			int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 **/
typedef struct builtin
{
		char *type;
			int (*func)(info_t *);
} builtin_table;


/* _shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* _cmd_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* _error_handling.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* _string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* _string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* _exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* _tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* _realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* _history_file.c */
int bfree(void **);

/* _utils.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* _error1_handling.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* _builtins.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* _builtins1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*_get_line.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* _get_info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* _environment.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* _get_environ.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* _history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* _ls.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* _ls1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* _vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

