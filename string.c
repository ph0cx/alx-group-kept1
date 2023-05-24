#include "shell.h"

/**
 * _strlen -|r|e|t|u|r|n|s|t|h|e|l|e|n|g|t|h|o|f|a|s|t|r|i|n|g|
 * @risvi:|t|h|e|s|t|r|i|n|g|w|h|o|s|e|l|e|n|g|t|h|t|o|c|h|e|c|k|
 *
 * Return:|i|n|t|e|g|e|r|l|e|n|g|t|h|o|f|s|t|r|i|n|g|
 */
int _strlen(char *risvi)
{
	int riivi = 0;

	if (!risvi)
		return (0);

	while (*risvi++)
		riivi++;
	return (riivi);
}

/**
 * _strcmp -|p|e|r|f|o|r|m|s|l|e|x|i|c|o|g|a|r|p|h|i|c|
 * c|o|m|p|a|r|i|s|o|n|o|f|t|w|o|s|t|r|a|n|g|s|.
 * @ris1vi:|t|h|e|f|i|r|s|t|s|t|r|a|n|g|
 * @ris2vi:|t|h|e|s|e|c|o|n|d|s|t|r|a|n|g|
 *
 * Return:|n|e|g|a|t|i|v|e|i|f|s1 < s2|,
 * |p|o|s|i|t|i|v|e|i|f|s1 > s2|,|z|e|r|o|i|f|s1 == s2|
 */
int _strcmp(char *ris1vi, char *ris2vi)
{
	while (*ris1vi && *ris2vi)
	{
		if (*ris1vi != *ris2vi)
			return (*ris1vi - *ris2vi);
		ris1vi++;
		ris2vi++;
	}
	if (*ris1vi == *ris2vi)
		return (0);
	else
		return (*ris1vi < *ris2vi ? -1 : 1);
}

/**
 * starts_with -|c|h|e|c|k|s|i|f|n|e|e|d|l|e|
 * s|t|a|r|t|s|w|i|t|h|h|a|y|s|t|a|c|k|
 * @rihaystackvi:|s|t|r|i|n|g|t|o|s|e|a|r|c|h|
 * @rineedlevi:|t|h|e|s|u|b|s|t|r|i|n|g|t|o|f|i|n|d|
 *
 * Return:|a|d|d|r|e|s|s|o|f|
 * n|e|x|t|char|o|f|h|a|y|s|t|a|c|k|o|r|NULL|
 */
char *starts_with(const char *rihaystackvi, const char *rineedlevi)
{
	while (*rineedlevi)
		if (*rineedlevi++ != *rihaystackvi++)
			return (NULL);
	return ((char *)rihaystackvi);
}

/**
 * _strcat -|c|o|n|c|a|t|e|n|a|t|e|s|t|w|o|s|t|r|i|n|g|s|
 * @ridestvi:|t|h|e|d|e|s|t|i|n|a|t|i|o|n|b|u|f|f|e|r|
 * @risrcvi:|t|h|e|s|o|u|r|c|e|b|u|f|f|e|r|
 *
 * Return:|p|o|i|n|t|e|r|t|o||d|e|s|t|i|n|a|t|i|o|n|b|u|f|f|e|r|
 */
char *_strcat(char *ridestvi, char *risrcvi)
{
	char *riretvi = ridestvi;

	while (*ridestvi)
		ridestvi++;
	while (*risrcvi)
		*ridestvi++ = *risrcvi++;
	*ridestvi = *risrcvi;
	return (riretvi);
}
