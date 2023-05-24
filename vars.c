#include "shell.h"

/**
 * is_chain -|t|e|s|t|i|f|c|u|r|r|e|n|t|c|h|a|r||i|n|b|
 * u|f|f|e|r|i|s|a|c|h|a|i|n|d|e|l|i|m|e|t|e|r|
 * @riinfovi:|t|h|e|p|a|r|a|m|e|t|e|r|s|t|r|u|c|t|
 * @ribufvi:|t|h|e|c|h|a|r|b|u|f|f|e|r|
 * @ripvi:|a|d|d|r|e|s|s|o|f|c|u|r|r|e|n|t|p|o|s|i|t|i|o|n|i|n|b|u|f|
 *
 * Return:|1|i|f|c|h|a|i|n|d|e|l|i|m|e|t|e|r|,|0|o|t|h|e|r|w|i|s|e|
 */
int is_chain(riinfo_tvi *riinfovi, char *ribufvi, size_t *ripvi)
{
	size_t rijvi = *ripvi;

	if (ribufvi[rijvi] == '|' && ribufvi[rijvi + 1] == '|')
	{
		ribufvi[rijvi] = 0;
		rijvi++;
		riinfovi->ricmd_buf_typevi = RICMD_ORVI;
	}
	else if (ribufvi[rijvi] == '&' && ribufvi[rijvi + 1] == '&')
	{
		ribufvi[rijvi] = 0;
		rijvi++;
		riinfovi->ricmd_buf_typevi = RICMD_ANDVI;
	}
	else if (ribufvi[rijvi] == ';') /*|f|o|u|n|d||e|n|d|o|f|this|co|m|ma|n|d|*/
	{
		ribufvi[rijvi] = 0; /*|r|e|p|l|a|c|e|s|e|m|i|c|o|l|o|n|w|i|t|h|n|u|l|l| */
		riinfovi->ricmd_buf_typevi = RICMD_CHAINVI;
	}
	else
		return (0);
	*ripvi = rijvi;
	return (1);
}

/**
 * check_chain -|c|h|e|c|k|s|w|e|s|h|o|u|l|d|continue
 * |c|h|a|i|n|i|n|g|b|a|s|e|d|o|n|l|a|s|t|s|t|a|t|u|s
 * @riinfovi:|t|h|e|p|a|r|a|m||t|e|r|s|t|r|u|c|t|
 * @ribufvi:|t|h|e|c|h|a|r|b|u|f|f|e|r|
 * @ripvi:|a|d|d|r|e|s|s|o|f|c|u|r|r|e|n|t|p|o|s|i|t|i|o|n|i|n|b|u|f|
 * @riivi: |s|t|a|r|t|i|n|g|p|o|s|i|t|i|o|n|i|n|b|u|f|
 * @rilenvi:|l|e|n|g|t|h|o|f|b|u|f|
 *
 * Return: Void
 */
void check_chain(riinfo_tvi *riinfovi, char *ribufvi, size_t *ripvi,
	size_t riivi, size_t rilenvi)
{
	size_t rijvi = *ripvi;

	if (riinfovi->ricmd_buf_typevi == RICMD_ANDVI)
	{
		if (riinfovi->ristatusvi)
		{
			ribufvi[riivi] = 0;
			rijvi = rilenvi;
		}
	}
	if (riinfovi->ricmd_buf_typevi == RICMD_ORVI)
	{
		if (!riinfovi->ristatusvi)
		{
			ribufvi[riivi] = 0;
			rijvi = rilenvi;
		}
	}

	*ripvi = rijvi;
}

/**
 * replace_alias -|r|e|p|l|a|c|e|s|a|n
 * |a|l|i|a|s|e|s|i|n|t|h|e|t|o|k|e|n|i|z|e|d|s|t|r|i|n|g|
 * @riinfovi:|t|h|e|p|a|r|a|m|e|t|e|r|s|t|r|u|c|t|
 *
 * Return: 1 |i|f|r|e|p|l|a|c|e|d|,| 0 |o|t|h|e|r|w|i|s|e|
 */
int replace_alias(riinfo_tvi *riinfovi)
{
	int riivi;
	rilist_tvi *rinodevi;
	char *ripvi;

	for (riivi = 0; riivi < 10; riivi++)
	{
		rinodevi = node_starts_with(riinfovi->rialiasvi, riinfovi->riargvvi[0], '=');
		if (!rinodevi)
			return (0);
		free(riinfovi->riargvvi[0]);
		ripvi = _strchr(rinodevi->ristrvi, '=');
		if (!ripvi)
			return (0);
		ripvi = _strdup(ripvi + 1);
		if (!ripvi)
			return (0);
		riinfovi->riargvvi[0] = ripvi;
	}
	return (1);
}

/**
 * replace_vars - |r|e|p|l|a|c|e|s|v|a|r|s
 * |i|n|t|h|e|t|o|k|e|n|i|z|e|d|s|t|r|i|n|g|
 * @riinfovi:|t|h|e|p|a|r|a|m|e|t|e|r|s|t|r|u|c|t|
 *
 * Return: 1 |i|f|r|e|p|l|a|c|e|d|,| 0 |o|t|h|e|r|w|i|s|e|
 */
int replace_vars(riinfo_tvi *riinfovi)
{
	int riivi = 0;
	rilist_tvi *rinodevi;

	for (riivi = 0; riinfovi->riargvvi[riivi]; riivi++)
	{
		if (riinfovi->riargvvi[riivi][0] != '$' || !riinfovi->riargvvi[riivi][1])
			continue;

		if (!_strcmp(riinfovi->riargvvi[riivi], "$?"))
		{
			replace_string(&(riinfovi->riargvvi[riivi]),
					_strdup(convert_number(riinfovi->ristatusvi, 10, 0)));
			continue;
		}
		if (!_strcmp(riinfovi->riargvvi[riivi], "$$"))
		{
			replace_string(&(riinfovi->riargvvi[riivi]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		rinodevi = node_starts_with(riinfovi->rienvvi,
			&riinfovi->riargvvi[riivi][1], '=');
		if (rinodevi)
		{
			replace_string(&(riinfovi->riargvvi[riivi]),
					_strdup(_strchr(rinodevi->ristrvi, '=') + 1));
			continue;
		}
		replace_string(&riinfovi->riargvvi[riivi], _strdup(""));

	}
	return (0);
}

/**
 * replace_string -|r|e|p|l|a|c|e|s|s|t|r|i|n|g
 * @rioldvi:|a|d|d|r|e|s|s|o|f||o|l|d||s|t|r|i|n|g|
 * @rinewvi:|n|e|w|s|t|r|i|n|g|
 *
 * Return: 1 |i|f|r|e|p|l|a|c|e|d|,| 0 |o|t|h|e|r|w|i|s|e|
 */
int replace_string(char **rioldvi, char *rinewvi)
{
	free(*rioldvi);
	*rioldvi = rinewvi;
	return (1);
}
