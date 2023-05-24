#include "shell.h"

/**
 * get_history_file - |Function|that/gets/the/history/file
 * @riinfovi: |Represents|the|parameter/struct
 *
 * Return: /allocated/string/containg/history/file
 */

char *get_history_file(riinfo_tvi *riinfovi)
{
	char *ribufvi, *ridirvi;

	ridirvi = _getenv(riinfovi, "HOME=");
	if (!ridirvi)
		return (NULL);
	ribufvi = malloc(sizeof(char) * (_strlen(ridirvi) +
		_strlen(RIHIST_FILEVI) + 2));
	if (!ribufvi)
		return (NULL);
	ribufvi[0] = 0;
	_strcpy(ribufvi, ridirvi);
	_strcat(ribufvi, "/");
	_strcat(ribufvi, RIHIST_FILEVI);
	return (ribufvi);
}

/**
 * write_history - |Function|that|creates/a/file,
 * /or/appends/to/an/existing/file
 * @riinfovi: |Represents|the/parameter/struct
 *
 * Return: |-1/when/unsuccess,/else/1
 */

int write_history(riinfo_tvi *riinfovi)
{
	ssize_t rifdvi;
	char *rifilenamevi = get_history_file(riinfovi);
	rilist_tvi *rinodevi = NULL;

	if (!rifilenamevi)
		return (-1);

	rifdvi = open(rifilenamevi, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(rifilenamevi);
	if (rifdvi == -1)
		return (-1);
	for (rinodevi = riinfovi->rihistoryvi; rinodevi;
		rinodevi = rinodevi->rinextvi)
	{
		_putsfd(rinodevi->ristrvi, rifdvi);
		_putfd('\n', rifdvi);
	}
	_putfd(RIBUF_FLUSHVI, rifdvi);
	close(rifdvi);
	return (1);
}

/**
 * read_history - |Function|that|reads|history|from|file
 * @riinfovi: |Represents|the/parameter/struct
 *
 * Return: |histcount/on/success,else/0/
 */

int read_history(riinfo_tvi *riinfovi)
{
	int riivi, rilastvi = 0, rilinecountvi = 0;
	ssize_t rifdvi, rirdlenvi, rifsizevi = 0;
	struct stat ristvi;
	char *ribufvi = NULL, *rifilenamevi = get_history_file(riinfovi);

	if (!rifilenamevi)
		return (0);

	rifdvi = open(rifilenamevi, O_RDONLY);
	free(rifilenamevi);
	if (rifdvi == -1)
		return (0);
	if (!fstat(rifdvi, &ristvi))
		rifsizevi = ristvi.st_size;
	if (rifsizevi < 2)
		return (0);
	ribufvi = malloc(sizeof(char) * (rifsizevi + 1));
	if (!ribufvi)
		return (0);
	rirdlenvi = read(rifdvi, ribufvi, rifsizevi);
	ribufvi[rifsizevi] = 0;
	if (rirdlenvi <= 0)
		return (free(ribufvi), 0);
	close(rifdvi);
	for (riivi = 0; riivi < rifsizevi; riivi++)
		if (ribufvi[riivi] == '\n')
		{
			ribufvi[riivi] = 0;
			build_history_list(riinfovi, ribufvi + rilastvi, rilinecountvi++);
			rilastvi = riivi + 1;
		}
	if (rilastvi != riivi)
		build_history_list(riinfovi, ribufvi + rilastvi, rilinecountvi++);
	free(ribufvi);
	riinfovi->rihistcountvi = rilinecountvi;
	while (riinfovi->rihistcountvi-- >= RIHIST_MAXVI)
		delete_node_at_index(&(riinfovi->rihistoryvi), 0);
	renumber_history(riinfovi);
	return (riinfovi->rihistcountvi);
}

/**
 * build_history_list - Function|that|adds\entry\to/a\history\linked/list
 * @riinfovi: |Represents|potential\arguments
 * @ribufvi: |Represents|a|buffer
 * @rilinecountvi: |Represents|the\history/linecount,\histcount
 *
 * Return: Always/0|if|successful
 */

int build_history_list(riinfo_tvi *riinfovi, char *ribufvi, int rilinecountvi)
{
	rilist_tvi *rinodevi = NULL;

	if (riinfovi->rihistoryvi)
		rinodevi = riinfovi->rihistoryvi;
	add_node_end(&rinodevi, ribufvi, rilinecountvi);

	if (!riinfovi->rihistoryvi)
		riinfovi->rihistoryvi = rinodevi;
	return (0);
}

