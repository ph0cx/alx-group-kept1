#include "shell.h"

/**
 * **strtow -|s|p|l|i|t|s|a|s|t|r|i|n|g|i|n|t|o|w|o|r|d|s|.
 * |R|e|p|e|a|t|d|e|l|i|m|i|t|e|r|s|a|r|e|i|g|n|o|r|e|d|
 * @ristrvi: |t|h|e|i|n|p|u|t|s|t|r|i|n|g|
 * @ridvi:|t|h|e|d|e|l|i|m|e|t|e|r|s|t|r|i|n|g|
 * Return:|a|p|o|i|n|t|e|r|t|o|a|n|a|r|r|a|y|
 * o|f|s|t|r|i|n|g|s|,|o|r|N|U|L|L|o|n|f|a|i|l|u|r|e|
 */

char **strtow(char *ristrvi, char *ridvi)
{
	int riivi, rijvi, rikvi, rimvi, rinumwordsvi = 0;
	char **risvi;

	if (ristrvi == NULL || ristrvi[0] == 0)
		return (NULL);
	if (!ridvi)
		ridvi = " ";
	for (riivi = 0; ristrvi[riivi] != '\0'; riivi++)
		if (!is_delim(ristrvi[riivi], ridvi) && (is_delim(ristrvi[riivi + 1],
		ridvi) || !ristrvi[riivi + 1]))
			rinumwordsvi++;

	if (rinumwordsvi == 0)
		return (NULL);
	risvi = malloc((1 + rinumwordsvi) * sizeof(char *));
	if (!risvi)
		return (NULL);
	for (riivi = 0, rijvi = 0; rijvi < rinumwordsvi; rijvi++)
	{
		while (is_delim(ristrvi[riivi], ridvi))
			riivi++;
		rikvi = 0;
		while (!is_delim(ristrvi[riivi + rikvi], ridvi) && ristrvi[riivi + rikvi])
			rikvi++;
		risvi[rijvi] = malloc((rikvi + 1) * sizeof(char));
		if (!risvi[rijvi])
		{
			for (rikvi = 0; rikvi < rijvi; rikvi++)
				free(risvi[rikvi]);
			free(risvi);
			return (NULL);
		}
		for (rimvi = 0; rimvi < rikvi; rimvi++)
			risvi[rijvi][rimvi] = ristrvi[riivi++];
		risvi[rijvi][rimvi] = 0;
	}
	risvi[rijvi] = NULL;
	return (risvi);
}

/**
 * **strtow2 -|s|p|l|i|t|s|a|s|t|r|i|n|g|i|n|t|o|w|o|r|d|s|
 * @ristrvi:|t|h|e|i|n|p|u|t|s|t|r|i|n|g|
 * @ridvi:|t|h|e|d|e|l|i|m|e|t|e|r|
 * Return:|a|p|o|i|n|t|e|r|t|o|a|n|a|r|r|a|y|
 * o|f|s|t|r|i|n|g|s|,|o|r|N|U|L|L|o|n|f|a|i|l|u|r|e|
 */
char **strtow2(char *ristrvi, char ridvi)
{
	int riivi, rijvi, rikvi, rimvi, rinumwordsvi = 0;
	char **risvi;

	if (ristrvi == NULL || ristrvi[0] == 0)
		return (NULL);
	for (riivi = 0; ristrvi[riivi] != '\0'; riivi++)
		if ((ristrvi[riivi] != ridvi && ristrvi[riivi + 1] == ridvi) ||
				    (ristrvi[riivi] != ridvi && !ristrvi[riivi + 1]) ||
					ristrvi[riivi + 1] == ridvi)
			rinumwordsvi++;
	if (rinumwordsvi == 0)
		return (NULL);
	risvi = malloc((1 + rinumwordsvi) * sizeof(char *));
	if (!risvi)
		return (NULL);
	for (riivi = 0, rijvi = 0; rijvi < rinumwordsvi; rijvi++)
	{
		while (ristrvi[riivi] == ridvi && ristrvi[riivi] != ridvi)
			riivi++;
		rikvi = 0;
		while (ristrvi[riivi + rikvi] != ridvi && ristrvi[riivi + rikvi] &&
		ristrvi[riivi + rikvi] != ridvi)
			rikvi++;
		risvi[rijvi] = malloc((rikvi + 1) * sizeof(char));
		if (!risvi[rijvi])
		{
			for (rikvi = 0; rikvi < rijvi; rikvi++)
				free(risvi[rikvi]);
			free(risvi);
			return (NULL);
		}
		for (rimvi = 0; rimvi < rikvi; rimvi++)
			risvi[rijvi][rimvi] = ristrvi[riivi++];
		risvi[rijvi][rimvi] = 0;
	}
	risvi[rijvi] = NULL;
	return (risvi);
}
