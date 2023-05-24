#include "shell.h"

/**
 * _myhistory - Function|that||displays|the|history|list,|one|command|by|line,
 * preceded|with|line|numbers,|starting|at|0.
 * @riinfovi: |Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 *  Return: |Always|0|when|successful
 */

int _myhistory(riinfo_tvi *riinfovi)
{
	print_list(riinfovi->rihistoryvi);
	return (0);
}

/**
 * unset_alias - Function|that|sets|alias|to|string
 * @riinfovi: Represents|parameter|struct
 * @ristrvi: Represents|the|string|alias
 *
 * Return:|Always|0|on|success,|1|on|error
 */

int unset_alias(riinfo_tvi *riinfovi, char *ristrvi)
{
	char *ripvi, ricvi;
	int riretvi;

	ripvi = _strchr(ristrvi, '=');
	if (!ripvi)
		return (1);
	ricvi = *ripvi;
	*ripvi = 0;
	riretvi = delete_node_at_index(&(riinfovi->rialiasvi),
		get_node_index(riinfovi->rialiasvi, node_starts_with(riinfovi->rialiasvi,
			ristrvi, -1)));
	*ripvi = ricvi;
	return (riretvi);
}

/**
 * set_alias - Function|that|sets|alias|to|string
 * @riinfovi: Represents|parameter|struct
 * @ristrvi: Represents|the|string|alias
 *
 * Return: 1|on|error|else|,1|on success
 */

int set_alias(riinfo_tvi *riinfovi, char *ristrvi)
{
	char *ripvi;

	ripvi = _strchr(ristrvi, '=');
	if (!ripvi)
		return (1);
	if (!*++ripvi)
		return (unset_alias(riinfovi, ristrvi));

	unset_alias(riinfovi, ristrvi);
	return (add_node_end(&(riinfovi->rialiasvi), ristrvi, 0) == NULL);
}

/**
 * print_alias - Function|that|prints|an|alias|string
 * @rinodevi: Represnts|the|alias|node
 *
 * Return:|1|on|error|else|,1|on success
 */

int print_alias(rilist_tvi *rinodevi)
{
	char *ripvi = NULL, *riavi = NULL;

	if (rinodevi)
	{
		ripvi = _strchr(rinodevi->ristrvi, '=');
		for (riavi = rinodevi->ristrvi; riavi <= ripvi; riavi++)
		_putchar(*riavi);
		_putchar('\'');
		_puts(ripvi + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Function|that|mimics|the|alias|builtin|(man|alias)
 * @riinfovi:|Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 * Return: |Always|0|when|successful
 */

int _myalias(riinfo_tvi *riinfovi)
{
	int riivi = 0;
	char *ripvi = NULL;
	rilist_tvi *rinodevi = NULL;

	if (riinfovi->riargcvi == 1)
	{
		rinodevi = riinfovi->rialiasvi;
		while (rinodevi)
		{
			print_alias(rinodevi);
			rinodevi = rinodevi->rinextvi;
		}
		return (0);
	}
	for (riivi = 1; riinfovi->riargvvi[riivi]; riivi++)
	{
		ripvi = _strchr(riinfovi->riargvvi[riivi], '=');
		if (ripvi)
			set_alias(riinfovi, riinfovi->riargvvi[riivi]);
		else
			print_alias(node_starts_with(riinfovi->rialiasvi,
				riinfovi->riargvvi[riivi], '='));
	}

	return (0);
}
