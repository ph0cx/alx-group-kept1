#include "shell.h"

/**
 * _strcpy -|c|o|p|i|e|s|a|s|t|r|i|n|g|
 * @ridestvi:|t|h|e|d|e|s|t|i|n|a|t|i|o|n|
 * @risrcvi:|t|h|e|s|o|u|r|c|e|
 *
 * Return:|p|o|i|n|t|e|r|t|o|d|e|s|t|i|n|a|t|i|o|n|
 */
char *_strcpy(char *ridestvi, char *risrcvi)
{
	int riivi = 0;

	if (ridestvi == risrcvi || risrcvi == 0)
		return (ridestvi);
	while (risrcvi[riivi])
	{
		ridestvi[riivi] = risrcvi[riivi];
		riivi++;
	}
	ridestvi[riivi] = 0;
	return (ridestvi);
}

/**
 * _strdup -|d|u|p|l|i|c|a|t|e|s|a|s|t|r|i|n|g|
 * @ristrvi:|t|h|e||s|t|r|i|n|g|t|o|d|u|p|l|i|c|a|t|e|
 *
 * Return:|p|o|i|n|t|e|r||t|o||
 * t|h|e|d|u|p|l|i|c|a|t|e|d|s|t|r|i|n|g|
 */
char *_strdup(const char *ristrvi)
{
	int rilengthvi = 0;
	char *riretvi;

	if (ristrvi == NULL)
		return (NULL);
	while (*ristrvi++)
		rilengthvi++;
	riretvi = malloc(sizeof(char) * (rilengthvi + 1));
	if (!riretvi)
		return (NULL);
	for (rilengthvi++; rilengthvi--;)
		riretvi[rilengthvi] = *--ristrvi;
	return (riretvi);
}

/**
 * _puts - prints an input string
 * @ristrvi: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *ristrvi)
{
	int riivi = 0;

	if (!ristrvi)
		return;
	while (ristrvi[riivi] != '\0')
	{
		_putchar(ristrvi[riivi]);
		riivi++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @ricvi: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ricvi)
{
	static int riivi;
	static char ribufvi[RIWRITE_BUF_SIZEVI];

	if (ricvi == RIBUF_FLUSHVI || riivi >= RIWRITE_BUF_SIZEVI)
	{
		write(1, ribufvi, riivi);
		riivi = 0;
	}
	if (ricvi != RIBUF_FLUSHVI)
		ribufvi[riivi++] = ricvi;
	return (1);
}
