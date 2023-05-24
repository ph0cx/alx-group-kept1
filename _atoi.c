#include "shell.h"

/**
 * interactive - function|that|returns|true|if|shell|is|interactive|mode
 * @riinfovi:|represents|struct|address
 *
 * Return:|0|,otherwise|1|if|interactive|mode
 */
int interactive(riinfo_tvi *riinfovi)
{
	return (isatty(STDIN_FILENO) && riinfovi->rireadfdvi <= 2);
}

/**
 * is_delim - Function|that|checks|if|character|is|a|delimeter
 * @ricvi:|represents|the|char|to|check
 * @ridelimvi:|represents|the|delimeter|string
 * Return:|1|if|true|,otherwise|0|if|false
 */
int is_delim(char ricvi, char *ridelimvi)
{
	while (*ridelimvi)
		if (*ridelimvi++ == ricvi)
			return (1);
	return (0);
}

/**
 * _isalpha -|Function|that|checks|for|alphabetic|character
 * @ricvi: |represents|the|character|to|input
 * Return:|0|otherwise,|1|if|c|is|alphabetic
 */

int _isalpha(int ricvi)
{
	if ((ricvi >= 'a' && ricvi <= 'z') || (ricvi >= 'A' && ricvi <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi -|Function|that|converts|a|string|to|an|integer
 * @risvi:|Represnts|the|string|to|be|converted
 * Return: |converted|number|otherwise,0|if|no|numbers|in|string
 */

int _atoi(char *risvi)
{
	int riivi, risignvi = 1, riflagvi = 0, rioutputvi;
	unsigned int riresultvi = 0;

	for (riivi = 0; risvi[riivi] != '\0' && riflagvi != 2; riivi++)
	{
		if (risvi[riivi] == '-')
			risignvi *= -1;

		if (risvi[riivi] >= '0' && risvi[riivi] <= '9')
		{
			riflagvi = 1;
			riresultvi *= 10;
			riresultvi += (risvi[riivi] - '0');
		}
		else if (riflagvi == 1)
			riflagvi = 2;
	}

	if (risignvi == -1)
		rioutputvi = -riresultvi;
	else
		rioutputvi = riresultvi;

	return (rioutputvi);
}
