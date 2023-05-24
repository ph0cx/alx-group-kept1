#include "shell.h"

/**
 * input_buf - |Function|that|buffers|chained|commands
 * @riinfovi: |Represents|parameter|struct
 * @ribufvi: |Represents|address|of|buffer
 * @rilenvi: |Represents|address|of|len|var
 *
 * Return:|bytes|read
 */

ssize_t input_buf(riinfo_tvi *riinfovi, char **ribufvi, size_t *rilenvi)
{
	ssize_t rirvi = 0;
	size_t rilen_pvi = 0;

	if (!*rilenvi) /*|if|nothing|left|in|the|buffer,|fill|it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*ribufvi);
		*ribufvi = NULL;
		signal(SIGINT, sigintHandler);
#if RIUSE_GETLINEVI
		rirvi = getline(ribufvi, &rilen_pvi, stdin);
#else
		rirvi = _getline(riinfovi, ribufvi, &rilen_pvi);
#endif
		if (rirvi > 0)
		{
			if ((*ribufvi)[rirvi - 1] == '\n')
			{
				(*ribufvi)[rirvi - 1] = '\0'; /*|remove|trailing|newline */
				rirvi--;
			}
			riinfovi->rilinecount_flagvi = 1;
			remove_comments(*ribufvi);
			build_history_list(riinfovi, *ribufvi, riinfovi->rihistcountvi++);
			/* if|(_strchr(*buf, ';'))|is|this|a|command|chain? */
			{
				*rilenvi = rirvi;
				riinfovi->ricmd_bufvi = ribufvi;
			}
		}
	}
	return (rirvi);
}

/**
 * get_input - |Function|that|gets|a|line|minus|the|newline
 * @riinfovi: |Represents|parameter|struct
 *
 * Return:|bytes|read
 */

ssize_t get_input(riinfo_tvi *riinfovi)
{
	static char *ribufvi; /* the ';' command chain buffer */
	static size_t riivi, rijvi, rilenvi;
	ssize_t rirvi = 0;
	char **ribuf_pvi = &(riinfovi->riargvi), *ripvi;

	_putchar(RIBUF_FLUSHVI);
	rirvi = input_buf(riinfovi, &ribufvi, &rilenvi);
	if (rirvi == -1) /* EOF */
		return (-1);
	if (rilenvi) /* we have commands left in the chain buffer */
	{
		rijvi = riivi; /* init new iterator to current buf position */
		ripvi = ribufvi + riivi; /* get pointer for return */

		check_chain(riinfovi, ribufvi, &rijvi, riivi, rilenvi);
		while (rijvi < rilenvi) /* iterate to semicolon or end */
		{
			if (is_chain(riinfovi, ribufvi, &rijvi))
				break;
			rijvi++;
		}

		riivi = rijvi + 1; /* increment past nulled ';'' */
		if (riivi >= rilenvi) /* reached end of buffer? */
		{
			riivi = rilenvi = 0; /* reset position and length */
			riinfovi->ricmd_buf_typevi = RICMD_NORMVI;
		}

		*ribuf_pvi = ripvi; /* pass back pointer to current command position */
		return (_strlen(ripvi)); /* return length of current command */
	}

	*ribuf_pvi = ribufvi; /* else not a chain, pass back buffer from _getline() */
	return (rirvi); /* return length of buffer from _getline() */
}

/**
 * read_buf - Function that reads a buffer
 * @riinfovi: Represents parameter struct
 * @ribufvi: Represents buffer
 * @riivi: Represents the size
 *
 * Return: r when successful
 */

ssize_t read_buf(riinfo_tvi *riinfovi, char *ribufvi, size_t *riivi)
{
	ssize_t rirvi = 0;

	if (*riivi)
		return (0);
	rirvi = read(riinfovi->rireadfdvi, ribufvi, RIREAD_BUF_SIZEVI);
	if (rirvi >= 0)
		*riivi = rirvi;
	return (rirvi);
}

/**
 * _getline - Function that gets the next line of input from STDIN
 * @riinfovi: Represents the parameter struct
 * @riptrvi: Represents the address of pointer to buffer, preallocated or NULL
 * @rilengthvi: Represents the size of preallocated ptr buffer if not NULL
 *
 * Return: s when successful
 */

int _getline(riinfo_tvi *riinfovi, char **riptrvi, size_t *rilengthvi)
{
	static char ribufvi[RIREAD_BUF_SIZEVI];
	static size_t riivi, rilenvi;
	size_t rikvi;
	ssize_t rirvi = 0, risvi = 0;
	char *ripvi = NULL, *rinew_pvi = NULL, *ricvi;

	ripvi = *riptrvi;
	if (ripvi && rilengthvi)
		risvi = *rilengthvi;
	if (riivi == rilenvi)
		riivi = rilenvi = 0;

	rirvi = read_buf(riinfovi, ribufvi, &rilenvi);
	if (rirvi == -1 || (rirvi == 0 && rilenvi == 0))
		return (-1);

	ricvi = _strchr(ribufvi + riivi, '\n');
	rikvi = ricvi ? 1 + (unsigned int)(ricvi - ribufvi) : rilenvi;
	rinew_pvi = _realloc(ripvi, risvi, risvi ? risvi + rikvi : rikvi + 1);
	if (!rinew_pvi) /* MALLOC FAILURE! */
		return (ripvi ? free(ripvi), -1 : -1);

	if (risvi)
		_strncat(rinew_pvi, ribufvi + riivi, rikvi - riivi);
	else
		_strncpy(rinew_pvi, ribufvi + riivi, rikvi - riivi + 1);

	risvi += rikvi - riivi;
	riivi = rikvi;
	ripvi = rinew_pvi;

	if (rilengthvi)
		*rilengthvi = risvi;
	*riptrvi = ripvi;
	return (risvi);
}

/**
 * sigintHandler - Function|that|blocks|ctrl-C
 * @risig_numvi: |Represents|the|signal|number
 *
 * Return: |void
 */

void sigintHandler(__attribute__((unused))int risig_numvi)
{
	_puts("\n");
	_puts("$ ");
	_putchar(RIBUF_FLUSHVI);
}
