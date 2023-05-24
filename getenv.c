#include "shell.h"

/**
 * get_environ - |Function|that|returns|the|string|array|copy|of|our|environ
 * @riinfovi: |The|Structure|containing|potential|arguments|to|maintain
 * function.
 * Return:|Always|return|0|if |successful
 */

char **get_environ(riinfo_tvi *riinfovi)
{
	if (!riinfovi->rienvironvi || riinfovi->rienv_changedvi)
	{
		riinfovi->rienvironvi = list_to_strings(riinfovi->rienvvi);
		riinfovi->rienv_changedvi = 0;
	}

	return (riinfovi->rienvironvi);
}

/**
 * _unsetenv - |Function|that|removes|an|environment|variable
 * @riinfovi: |Represents|potential|arguments|
 * to|maintain|constant|function|prototype.
 * Return: |1|on|delete, else|0|
 * @rivarvi: |Represents|the|string|env|var|property
 */
int _unsetenv(riinfo_tvi *riinfovi, char *rivarvi)
{
	rilist_tvi *rinodevi = riinfovi->rienvvi;
	size_t riivi = 0;
	char *ripvi;

	if (!rinodevi || !rivarvi)
		return (0);

	while (rinodevi)
	{
		ripvi = starts_with(rinodevi->ristrvi, rivarvi);
		if (ripvi && *ripvi == '=')
		{
			riinfovi->rienv_changedvi = delete_node_at_index(&(riinfovi->rienvvi),
				riivi);
			riivi = 0;
			rinodevi = riinfovi->rienvvi;
			continue;
		}
		rinodevi = rinodevi->rinextvi;
		riivi++;
	}
	return (riinfovi->rienv_changedvi);
}

/**
 * _setenv -|Function|that|initialize|a|new|environment|variable,
 * or|modify|an|existing|one
 * @riinfovi: |Represents|the|potential|arguments|
 * to|maintain|constant|function|prototype.
 * @rivarvi: |Represent|the string env var property
 * @rivaluevi:|Reprsents|the|string|env|var|value
 *  Return:|Always|0|if|successful
 */

int _setenv(riinfo_tvi *riinfovi, char *rivarvi, char *rivaluevi)
{
	char *ribufvi = NULL;
	rilist_tvi *rinodevi;
	char *ripvi;

	if (!rivarvi || !rivaluevi)
		return (0);

	ribufvi = malloc(_strlen(rivarvi) + _strlen(rivaluevi) + 2);
	if (!ribufvi)
		return (1);
	_strcpy(ribufvi, rivarvi);
	_strcat(ribufvi, "=");
	_strcat(ribufvi, rivaluevi);
	rinodevi = riinfovi->rienvvi;
	while (rinodevi)
	{
		ripvi = starts_with(rinodevi->ristrvi, rivarvi);
		if (ripvi && *ripvi == '=')
		{
			free(rinodevi->ristrvi);
			rinodevi->ristrvi = ribufvi;
			riinfovi->rienv_changedvi = 1;
			return (0);
		}
		rinodevi = rinodevi->rinextvi;
	}
	add_node_end(&(riinfovi->rienvvi), ribufvi, 0);
	free(ribufvi);
	riinfovi->rienv_changedvi = 1;
	return (0);
}
