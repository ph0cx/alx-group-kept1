#include "shell.h"

/**
 * _eputs -|Function|that|prints|an|input|string
 * @ristrvi: |Represents|the|string|to|be|printed
 *
 * Return: |void|
 */

void _eputs(char *ristrvi)
{
	int riivi = 0;

	if (!ristrvi)
		return;
	while (ristrvi[riivi] != '\0')
	{
		_eputchar(ristrvi[riivi]);
		riivi++;
	}
}

/**
 * _eputchar -|Functions|that|writes|the|character|c|to|stderr
 * @ricvi: |Represents|the|character|to|print
 *
 * Return: |1|when successful,|when|on|error|-1|is|returned
*	|and|errno|is|set|appropriately.
 */

int _eputchar(char ricvi)
{
	static int riivi;
	static char ribufvi[RIWRITE_BUF_SIZEVI];

	if (ricvi == RIBUF_FLUSHVI || riivi >= RIWRITE_BUF_SIZEVI)
	{
		write(2, ribufvi, riivi);
		riivi = 0;
	}
	if (ricvi != RIBUF_FLUSHVI)
		ribufvi[riivi++] = ricvi;
	return (1);
}

/**
 * _putfd - |Function|thatwrites|the|character|c|to|given|fd
 * @ricvi: |The|character|value|to|print
 * @rifdvi: |The|file|descriptor|value|to|write|to
 *
 * Return:|On|error|-1|returned|but|1|when|success|1|
 * and|errno|is|set|appropriately.
 */

int _putfd(char ricvi, int rifdvi)
{
	static int riivi;
	static char ribufvi[RIWRITE_BUF_SIZEVI];

	if (ricvi == RIBUF_FLUSHVI || riivi >= RIWRITE_BUF_SIZEVI)
	{
		write(rifdvi, ribufvi, riivi);
		riivi = 0;
	}
	if (ricvi != RIBUF_FLUSHVI)
		ribufvi[riivi++] = ricvi;
	return (1);
}

/**
 * _putsfd - |Function|that|prints|an|input|string
 * @ristrvi:|the|string|value|to|be|printed
 * @rifdvi:|the|filedescriptor|value|to|write|to
 *
 * Return:|the|number|of|chars|put
 */

int _putsfd(char *ristrvi, int rifdvi)
{
	int riivi = 0;

	if (!ristrvi)
		return (0);
	while (*ristrvi)
	{
		riivi += _putfd(*ristrvi++, rifdvi);
	}
	return (riivi);
}
