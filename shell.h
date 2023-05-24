#ifndef _RISHELL_HVI_
#define _RISHELL_HVI_

#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* |f|o|r|r|e|a|d|/|w|r|i|t|e|b|u|f|f|e|r|s| */
#define RIREAD_BUF_SIZEVI 1024
#define RIWRITE_BUF_SIZEVI 1024
#define RIBUF_FLUSHVI -1

/*|f|o|r|c|o|m|m|a|n|d||c|h|a|i|n|i|n|g|*/
#define RICMD_NORMVI	0
#define RICMD_ORVI		1
#define RICMD_ANDVI		2
#define RICMD_CHAINVI	3

/*|f|o|r|c|o|n|v|e|r|t|_number()| */
#define RICONVERT_LOWERCASEVI	1
#define RICONVERT_UNSIGNEDVI	2

/*|1|i|f|u|s|i|n|g|s|y|s|t|e|m|getline()| */
#define RIUSE_GETLINEVI 0
#define RIUSE_STRTOKVI 0

#define RIHIST_FILEVI	".simple_shell_history"
#define RIHIST_MAXVI	4096

extern char **environ;


/**
 * struct riliststrvi -|s|i|n|g|l|y|l|i|n|k|e|d|l|i|s|t|
 * @rinumvi:|t|h|e|n|u|m|b|e|r|f|i|e|l|d|
 * @ristrvi:|a|s|t|r|i|n|g|
 * @rinextvi:|p|o|i|n|t|s|t|o|t||h|e|n|e|x|t|n|o|d||e|
 */
typedef struct riliststrvi
{
	int rinumvi;
	char *ristrvi;
	struct riliststrvi *rinextvi;
} rilist_tvi;

/**
 * struct ripassinfovi -|c|o|n|t|a|i|n|s|p|s|e|u|d|o|-
 * |a|r|g|u|e|m|e|n|t|s|t|o|p|a|s|s|i|n|t|o|a|f|u|n|c|t|i|o|n,
 * |a|l|l|o|w|i|n|g|u|n|i|f|o|r|m|p|r|o|t|o|t|y|p|e|
 * f|o|r|f|u|n|c|t|i|o|n|p|o|i|n|t|e|r|struct
 * @riargvi:|a|s|t|r|i|n|g|g|e|n|e|r|a|t|e|d|f|r|o|m|
 * g|e|t|l|i|n|e|c|o|n|t|a|i|n|i|n|g|a|r|g|u|e|m|e|n|t|s|
 * @riargvvi:|a|n|a|r|r|a|y|o|f|s|t|r|i|n|g|s|g|e|n|e|r|a|t|e|d|f|r|o|m|a|r|g|
 * @ripathvi:|a|s|t|r|i|n|g|p|a|t|h|f|o|r|t|h|e|c|u|r|r|e|n|t|c|o|m|m|a|n|d|
 * @riargcvi:|t|h|e|a|r|g|u|m|e|n|t|c|o|u|n|t|
 * @riline_countvi:|t|h|e|e|r|r|o|r|c|o|u|n|t|
 * @rierr_numvi:|t|h|e|e|r|r|o|r|c|o|d|e|f|o|r|e|x|i|t|(|)|s|
 * @rilinecount_flagvi:|i|f|o|n|c|o|u|n|t|t|h|i|s|l|i|n|e|o|f|i|n|p|u|t|
 * @rifnamevi:|t|h|e|p|r|o|g|r|a|m|f|i|l|e|n|a|m|e|
 * @rienvvi:|l|i|n|k|e|d|l|i|s|t|l|o|c|a|l|c|o|p|y|o|f|e|n|v|i|r|o|n|
 * @rienvironvi:|c|u|s|t|o|m|m|o|d|i|f|i|e|d|c|o|p|y|
 * o|f|e|n|v|i|r|o|n|f|r|o|m|LL|env|
 * @rihistoryvi:|t|h|e|h|i|s|t|o|r|y|n|o|d|e|
 * @rialiasvi:|t|h|e|a|l|i|a|s|n|o|d|e|
 * @rienv_changedvi:|o|n|i|f|e|n|v|i|r|o|n|w|a|s|c|h|a|n|g|e|d|
 * @ristatusvi:|t|h|e|r|e|t|u|r|n|s|t|a|t|u|s|
 * o|f|t|h|e|l|a|s|t|e|x|e|c|'|d|c|o|m|m|a|n|d|
 * @ricmd_bufvi:|a|d|d|r|e|s|s|o|f|p|o|i|n|t|e|r|t|o|c|m|d_|b|u|f,onif|chaining
 * @ricmd_buf_typevi:|CMD_type ||, &&, ;|
 * @rireadfdvi:|t|h|e|fd|f|r|o|m|w|h|i|c|h|t|o|r|e|a|d|l|i|n|e|i|n|p|u|t
 * @rihistcountvi:|t|h|e|h|i|s|t|o|r|y|l|i|n|e|n|u|m|b|e|r|c|o|u|n|t
 */
typedef struct ripassinfovi
{
	char *riargvi;
	char **riargvvi;
	char *ripathvi;
	int riargcvi;
	unsigned int riline_countvi;
	int rierr_numvi;
	int rilinecount_flagvi;
	char *rifnamevi;
	rilist_tvi *rienvvi;
	rilist_tvi *rihistoryvi;
	rilist_tvi *rialiasvi;
	char **rienvironvi;
	int rienv_changedvi;
	int ristatusvi;

	char **ricmd_bufvi; /*pointer|to| cmd; chain buffer,|for|memory mangement*/
	int ricmd_buf_typevi; /*|CMD_type| ||, &&, ; */
	int rireadfdvi;
	int rihistcountvi;
} riinfo_tvi;

#define RIINFO_INITVI \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct ribuiltinvi -|contains|a|builtin|string|and|related|function|
 * @ritypevi:|the|b|u|i|l|t|i|n|c|o|m|m|a|n|d|f|l|a|g|
 * @rifuncvi:|t|h|e|f|u|n|c|t|i|o|n|
 */
typedef struct ribuiltinvi
{
	char *ritypevi;
	int (*rifuncvi)(riinfo_tvi *);
} ribuiltin_tablevi;


/*|s|h|l|o|o|p|.|c|*/
int hsh(riinfo_tvi *, char **);
int find_builtin(riinfo_tvi *);
void find_cmd(riinfo_tvi *);
void fork_cmd(riinfo_tvi *);

/*|p|a|r|s|e|r|.|c|*/
int is_cmd(riinfo_tvi *, char *);
char *dup_chars(char *, int, int);
char *find_path(riinfo_tvi *, char *, char *);

/*|l|o|o|p|h|s|h|.|c|*/
int loophsh(char **);

/*|e|r|r|o|r|s|.|c|*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char ricvi, int rifdvi);
int _putsfd(char *ristrvi, int rifdvi);

/*|s|t|r|i|n|g|.|c| */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*|s|t|r|i|n|g|1|.|c|*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*|e|x|i|t|s|.|c|*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*|t|o|k|e|n|i|z|e|r|.|c|*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/*|r|e|a|l|l|o|c|.|c|*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*|m|e|m|o|r||y|.|c|*/
int bfree(void **);

/*|a|t|o|i|.|c|*/
int interactive(riinfo_tvi *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/*|e|r|r|o|r|s|1|.|c|*/
int _erratoi(char *);
void print_error(riinfo_tvi *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*|b|u|i|l|t|i|n|.|c|*/
int _myexit(riinfo_tvi *);
int _mycd(riinfo_tvi *);
int _myhelp(riinfo_tvi *);

/*|b|u|i|l|t|i|n|1|.|c|*/
int _myhistory(riinfo_tvi *);
int _myalias(riinfo_tvi *);

/*|g|e|t|l|i|n|e|.|c|*/
ssize_t get_input(riinfo_tvi *);
int _getline(riinfo_tvi *, char **, size_t *);
void sigintHandler(int);

/*|g|e|t|i|n|f|o|.|c|*/
void clear_info(riinfo_tvi *);
void set_info(riinfo_tvi *, char **);
void free_info(riinfo_tvi *, int);

/* |e|n|v|i|r|o|n|.|c|*/
char *_getenv(riinfo_tvi *, const char *);
int _myenv(riinfo_tvi *);
int _mysetenv(riinfo_tvi *);
int _myunsetenv(riinfo_tvi *);
int populate_env_list(riinfo_tvi *);

/* |g|e|t|e|n|v|.|c|*/
char **get_environ(riinfo_tvi *);
int _unsetenv(riinfo_tvi *, char *);
int _setenv(riinfo_tvi *, char *, char *);

/*|h|i|s|t|o|r|y|.|c|*/
char *get_history_file(riinfo_tvi *riinfovi);
int write_history(riinfo_tvi *riinfovi);
int read_history(riinfo_tvi *riinfovi);
int build_history_list(riinfo_tvi *riinfovi, char *ribufvi, int rilinecountvi);
int renumber_history(riinfo_tvi *info);

/* |l||i|s|t|s|.|c|*/
rilist_tvi *add_node(rilist_tvi **, const char *, int);
rilist_tvi *add_node_end(rilist_tvi **, const char *, int);
size_t print_list_str(const rilist_tvi *);
int delete_node_at_index(rilist_tvi **, unsigned int);
void free_list(rilist_tvi **);

/*|l|i|s|t|s|1|.|c|*/
size_t list_len(const rilist_tvi *);
char **list_to_strings(rilist_tvi *);
size_t print_list(const rilist_tvi *);
rilist_tvi *node_starts_with(rilist_tvi *, char *, char);
ssize_t get_node_index(rilist_tvi *, rilist_tvi *);

/*|v|a|r|s|.|c|*/
int is_chain(riinfo_tvi *, char *, size_t *);
void check_chain(riinfo_tvi *, char *, size_t *, size_t, size_t);
int replace_alias(riinfo_tvi *);
int replace_vars(riinfo_tvi *);
int replace_string(char **, char *);

#endif
