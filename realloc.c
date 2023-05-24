#include "shell.h"

/**
 * _memset - |f|i|l|l|s| |m|e|m|o|r|y| |w|i|t|h| |a|
 * |c|o|n|s|t|a|n|t| |b|y|t|e|
 * @risvi: |t|h|e| |p|o|i|n|t|e|r| |t|o| |t|h|e| |m|e|m|o|r|y| |a|r|e|a|
 * @ribvi: |t|h|e| |b|y|t|e| |t|o| |f|i|l|l| |*s| |w|i|t|h|
 * @rinvi: |t|h|e| |a|m|o|u|n|t| |o|f| |b|y|t|e|s| |t|o| |b|e| |f|i|l|l|e|d|
 * Return: |(s)| |a| |p|o|i|n|t|e|r| |t|o| |t|h|e| |m|e|m|o|r|y| |a|r|e|a| |s|
 */
char *_memset(char *risvi, char ribvi, unsigned int rinvi)
{
	unsigned int riivi;

	for (riivi = 0; riivi < rinvi; riivi++)
		risvi[riivi] = ribvi;
	return (risvi);
}

/**
 * ffree - |f|r|e|e|s| |a| |s|t|r|i|n|g| |o|f| |s|t|r|i|n|g|s|
 * @rippvi: |s|t|r|i|n|g| |o|f| |s|t|r|i|n|g|s|
 */
void ffree(char **rippvi)
{
	char **riavi = rippvi;

	if (!rippvi)
		return;
	while (*rippvi)
		free(*rippvi++);
	free(riavi);
}

/**
 * _realloc -|r|e|a|l|l|o|c|a|t|e|s|a|b|l|o|c|k|o|f|m|e|m|o|r|y|
 * @riptrvi:|p|o|i|n|t|e|r|t|o|p|r|e|v|i|o|u|s|m|a|l|l|o|c|c|e|d|b|l|o|c|k|
 * @riold_sizevi:|b|y|t|e|s|i|z|e|o|f|p|r|e|v|i|o|u|s|b|l|o|c|k|
 * @rinew_sizevi:|b|y|t|e|s|i|z|e|o|f||ne|w|b|l|o|c|k|
 *
 * Return:|p|o|i|n|t|e|r|t|o|d|a|ol'block|nameen.
 */
void *_realloc(void *riptrvi, unsigned int riold_sizevi,
	 unsigned int rinew_sizevi)
{
	char *ripvi;

	if (!riptrvi)
		return (malloc(rinew_sizevi));
	if (!rinew_sizevi)
		return (free(riptrvi), NULL);
	if (rinew_sizevi == riold_sizevi)
		return (riptrvi);

	ripvi = malloc(rinew_sizevi);
	if (!ripvi)
		return (NULL);

	riold_sizevi = riold_sizevi < rinew_sizevi ? riold_sizevi : rinew_sizevi;
	while (riold_sizevi--)
		ripvi[riold_sizevi] = ((char *)riptrvi)[riold_sizevi];
	free(riptrvi);
	return (ripvi);
}
