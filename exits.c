#include "shell.h"

/**
 **_strncpy - |Function|that|copies|a|string
 *@ridestvi: |Represents|the|destination|string|to|be|copied|to
 *@risrcvi: |Represents|the|source|string
 *@rinvi: |Represents|the|amount|of|characters|to|be|copied
 *Return: |Returns|the|concatenated|string
 */

char *_strncpy(char *ridestvi, char *risrcvi, int rinvi)
{
	int riivi, rijvi;
	char *risvi = ridestvi;

	riivi = 0;
	while (risrcvi[riivi] != '\0' && riivi < rinvi - 1)
	{
		ridestvi[riivi] = risrcvi[riivi];
		riivi++;
	}
	if (riivi < rinvi)
	{
		rijvi = riivi;
		while (rijvi < rinvi)
		{
			ridestvi[rijvi] = '\0';
			rijvi++;
		}
	}
	return (risvi);
}

/**
 **_strncat - |Function|that|concatenates|two|strings
 *@ridestvi: |Represents|the|first|string
 *@risrcvi: |Represnents|the|second|string
 *@rinvi: |Represents|the|amount|of|bytes|to|be|maximally|used
 *Return: |Returns|the|concatenated|string
 */

char *_strncat(char *ridestvi, char *risrcvi, int rinvi)
{
	int riivi, rijvi;
	char *risvi = ridestvi;

	riivi = 0;
	rijvi = 0;
	while (ridestvi[riivi] != '\0')
		riivi++;
	while (risrcvi[rijvi] != '\0' && rijvi < rinvi)
	{
		ridestvi[riivi] = risrcvi[rijvi];
		riivi++;
		rijvi++;
	}
	if (rijvi < rinvi)
		ridestvi[riivi] = '\0';
	return (risvi);
}

/**
 **_strchr - |Function|locates|a|character|in|a|string
 *@risvi: |Represents|the|string|to|be|parsed
 *@ricvi: |Represents|the|character|to|look|for
 *Return: |'s'|a|pointer|to|the|memory|area|s
 */

char *_strchr(char *risvi, char ricvi)
{
	do {
		if (*risvi == ricvi)
			return (risvi);
	} while (*risvi++ != '\0');

	return (NULL);
}
