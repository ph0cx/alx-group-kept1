#include "shell.h"

/**
 * _myenv - Function|prints|the|current|environment
 * @riinfovi: |Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 * Return:|Always|0|when|successful
 */

int _myenv(riinfo_tvi *riinfovi)
{
	print_list_str(riinfovi->rienvvi);
	return (0);
}

/**
 * _getenv - Function|that|gets|the|value|of|an|environ|variable
 * @riinfovi:|Structure|containing|potential|arguments|to|maintain
 * @rinamevi: Represents|env|var|name
 *
 * Return: |the|value
 */

char *_getenv(riinfo_tvi *riinfovi, const char *rinamevi)
{
	rilist_tvi *rinodevi = riinfovi->rienvvi;
	char *ripvi;

	while (rinodevi)
	{
		ripvi = starts_with(rinodevi->ristrvi, rinamevi);
		if (ripvi && *ripvi)
			return (ripvi);
		rinodevi = rinodevi->rinextvi;
	}
	return (NULL);
}

/**
 * _mysetenv -|Function|that|initialize|a|new|environment|variable,
 * or|modify|an|existing|one
 * @riinfovi: |Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 *  Return: |Always|0|when|successful
 */

int _mysetenv(riinfo_tvi *riinfovi)
{
	if (riinfovi->riargcvi != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(riinfovi, riinfovi->riargvvi[1], riinfovi->riargvvi[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -|Function|that|removes|an|environment|variable
 * @riinfovi: |Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 * Return: |Always|0|when|successful
 */

int _myunsetenv(riinfo_tvi *riinfovi)
{
	int riivi;

	if (riinfovi->riargcvi == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (riivi = 1; riivi <= riinfovi->riargcvi; riivi++)
		_unsetenv(riinfovi, riinfovi->riargvvi[riivi]);

	return (0);
}

/**
 * populate_env_list - Function|that|populates|env|linked|list
 * @riinfovi: Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 * Return:|Always|0|if|successful
 */

int populate_env_list(riinfo_tvi *riinfovi)
{
	rilist_tvi *rinodevi = NULL;
	size_t riivi;

	for (riivi = 0; environ[riivi]; riivi++)
		add_node_end(&rinodevi, environ[riivi], 0);
	riinfovi->rienvvi = rinodevi;
	return (0);
}
