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

/* reading/writing buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getlin() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct ltstr - singly linked list
 * @nm: the number field
 * @str: a string
 * @nx: it points to the next node
 */
typedef struct ltstr
{
	int nm;
	char *str;
	struct ltstr *nx;
} list_t;

/**
 *struct passinf - it contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_ct: the error count
 *@err_nm: the error code for exit()s
 *@linect_flag: if on count this line of input
 *@fname: the program filename
 *@envir: it linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@hist: the history node
 *@alia: the alias node
 *@envir_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmmd_buff_type: CMD_type ||, &&, ;
 *@readfdsc: the fd from which to read line input
 *@histct: the history line number count
 */
typedef struct passinf
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_ct;
	int err_nm;
	int linect_flag;
	char *fname;
	list_t *envir;
	list_t *hist;
	list_t *alia;
	char **environ;
	int envir_changed;
	int status;

	char **cmmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmmd_buff_type; /* CMD_type ||, &&, ; */
	int readfdsc;
	int histct;
} inf_t;

#define INF_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct buildin - contains a builtin string and related function
 *@type: buildin command flag
 *@func: function
 */
typedef struct buildin
{
	char *type;
	int (*func)(inf_t *);
} buildin_table;


/* toem_shloop.c */
int hshel(inf_t *, char **);
int find_buildin(inf_t *);
void find_cmmd(inf_t *);
void fork_cmmd(inf_t *);

/* toem_parser.c */
int is_cmmd(inf_t *, char *);
char *dup_char(char *, int, int);
char *find_paths(inf_t *, char *, char *);

/* loophsh.c */
int loophshell(char **);

/* toem_err.c */
void _eput(char *);
int _eputc(char);
int _putfdsc(char ch, int fdsc);
int _putsfdsc(char *str, int fdsc);

/* toem_strin.c */
int _stln(char *);
int _stcmp(char *, char *);
char *start_with(const char *, const char *);
char *_stcat(char *, char *);

/* toem_strin1.c */
char *_stcp(char *, char *);
char *_stdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exit.c */
char *_stncp(char *, char *, int);
char *_stncat(char *, char *, int);
char *_stchr(char *, char);

/* toem_token.c */
char **sttow(char *, char *);
char **sttow2(char *, char);

/* toem_realoc.c */
char *_memoryset(char *, char, unsigned int);
void ffrees(char **);
void *_realoc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfre(void **);

/* toem_stint.c */
int inter(inf_t *);
int is_delimeter(char, char *);
int _isalphabetic(int);
int _stint(char *);

/* toem_err1.c */
int _errstint(char *);
void print_err(inf_t *, char *);
int print_dc(int, int);
char *convert_nm(long int, int, int);
void remove_comment(char *);

/* toem_buildin.c */
int _myexits(inf_t *);
int _mycdir(inf_t *);
int _helpme(inf_t *);

/* toem_buildin1.c */
int _myhist(inf_t *);
int _myalia(inf_t *);

/*toem_getlin.c */
ssize_t get_inp(inf_t *);
int _getline(inf_t *, char **, size_t *);
void signintHandler(int);

/* toem_getinf.c */
void clear_inf(inf_t *);
void set_inf(inf_t *, char **);
void free_inf(inf_t *, int);


/* toem_environ.c */
char *_getenvir(inf_t *, const char *);
int _myenvir(inf_t *);
int _mysetenvir(inf_t *);
int _myunsetenvir(inf_t *);
int populate_environment_list(inf_t *);

/* toem_getenvir.c */
char **get_environment(inf_t *);
int _unsetenvir(inf_t *, char *);
int _setenvir(inf_t *, char *, char *);

/* toem_hist.c */
char *get_hist_file(inf_t *inf);
int write_hist(inf_t *inf);
int read_hist(inf_t *inf);
int build_hist_list(inf_t *inf, char *buff, int linect);
int renumber_hist(inf_t *inf);

/* toem_list.c */
list_t *add_nod(list_t **, const char *, int);
list_t *add_nod_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_nod_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_list1.c */
size_t list_ln(const list_t *);
char **list_to_string(list_t *);
size_t print_lt(const list_t *);
list_t *nod_starts_with(list_t *, char *, char);
ssize_t get_nod_index(list_t *, list_t *);

/* toem_var.c */
int is_chaine(inf_t *, char *, size_t *);
void check_chaine(inf_t *, char *, size_t *, size_t, size_t);
int replace_alia(inf_t *);
int replace_var(inf_t *);
int replace_str(char **, char *);

#endif
