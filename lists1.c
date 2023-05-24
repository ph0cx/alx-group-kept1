#include "shell.h"

/**
 * list_len - |Function|that/determines/length/of/linked/list
 * @rihvi:|Represents|that/pointer/to/first/node
 *
 * Return: /size/of/list
 */

size_t list_len(const rilist_tvi *rihvi)
{
	size_t riivi = 0;

	while (rihvi)
	{
		rihvi = rihvi->rinextvi;
		riivi++;
	}
	return (riivi);
}

/**
 * list_to_strings -|Function|that/returns/an/array/of/strings/of/the/list->str
 * @riheadvi: |Represents|the/pointer/to/first/node
 *
 * Return: /array/of/strings
 */

char **list_to_strings(rilist_tvi *riheadvi)
{
	rilist_tvi *rinodevi = riheadvi;
	size_t riivi = list_len(riheadvi), rijvi;
	char **ristrsvi;
	char *ristrvi;

	if (!riheadvi || !riivi)
		return (NULL);
	ristrsvi = malloc(sizeof(char *) * (riivi + 1));
	if (!ristrsvi)
		return (NULL);
	for (riivi = 0; rinodevi; rinodevi = rinodevi->rinextvi, riivi++)
	{
		ristrvi = malloc(_strlen(rinodevi->ristrvi) + 1);
		if (!ristrvi)
		{
			for (rijvi = 0; rijvi < riivi; rijvi++)
				free(ristrsvi[rijvi]);
			free(ristrsvi);
			return (NULL);
		}

		ristrvi = _strcpy(ristrvi, rinodevi->ristrvi);
		ristrsvi[riivi] = ristrvi;
	}
	ristrsvi[riivi] = NULL;
	return (ristrsvi);
}


/**
 * print_list - |Function|that/prints/all/elements/of/a|list_t|linked|list
 * @rihvi: |Represents|the|pointer|to|first|node
 *
 * Return: |size|of|list
 */

size_t print_list(const rilist_tvi *rihvi)
{
	size_t riivi = 0;

	while (rihvi)
	{
		_puts(convert_number(rihvi->rinumvi, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(rihvi->ristrvi ? rihvi->ristrvi : "(nil)");
		_puts("\n");
		rihvi = rihvi->rinextvi;
		riivi++;
	}
	return (riivi);
}

/**
 * node_starts_with - |Function|that|returns|
 * node|whose|string|starts|with|prefix
 * @rinodevi: |Represents|the|pointer|to|list|head
 * @riprefixvi: |Represents|string|to|match
 * @ricvi: |Represents|the|next|character|after|prefix|to|match
 *
 * Return: |match|node|or|null
 */

rilist_tvi *node_starts_with(rilist_tvi *rinodevi, char *riprefixvi,
	char ricvi)
{
	char *ripvi = NULL;

	while (rinodevi)
	{
		ripvi = starts_with(rinodevi->ristrvi, riprefixvi);
		if (ripvi && ((ricvi == -1) || (*ripvi == ricvi)))
			return (rinodevi);
		rinodevi = rinodevi->rinextvi;
	}
	return (NULL);
}

/**
 * get_node_index - |Function|that|gets|the\index/|of|\a|node
 * @riheadvi: |Represents|pointer|to|list|head
 * @rinodevi: |Represents|pointer|to|the|node
 *
 * Return: |-1, else|index|of|node
 */

ssize_t get_node_index(rilist_tvi *riheadvi, rilist_tvi *rinodevi)
{
	size_t riivi = 0;

	while (riheadvi)
	{
		if (riheadvi == rinodevi)
			return (riivi);
		riheadvi = riheadvi->rinextvi;
		riivi++;
	}
	return (-1);
}
