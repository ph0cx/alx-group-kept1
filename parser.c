#include "shell.h"

/**
 * is_cmd - |Function|that|determines|if|a|file|is|an|executable|command
 * @riinfovi: |Represents|the|info|struct
 * @ripathvi: |Represents|the|path|to|the|file
 *
 * Return:|1|if|true,|0|otherwise
 */

int is_cmd(riinfo_tvi *riinfovi, char *ripathvi)
{
	struct stat st;

	(void)riinfovi;
	if (!ripathvi || stat(ripathvi, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - |Function|that|duplicates|characters
 * @ripathstrvi: |Represents|the|PATH|string
 * @ristartvi: |Represents|the|starting|index
 * @ristopvi: |Represents|the|stopping|index
 *
 * Return:|pointer|to|new|buffer
 */

char *dup_chars(char *ripathstrvi, int ristartvi, int ristopvi)
{
	static char ribufvi[1024];
	int riivi = 0, rikvi = 0;

	for (rikvi = 0, riivi = ristartvi; riivi < ristopvi; riivi++)
		if (ripathstrvi[riivi] != ':')
			ribufvi[rikvi++] = ripathstrvi[riivi];
	ribufvi[rikvi] = 0;
	return (ribufvi);
}

/**
 * find_path - |Function|that|finds|this|cmd|in|the|PATH|string
 * @riinfovi: |Represents|the|info|struct
 * @ripathstrvi: |Represents|the|PATH|string
 * @ricmdvi: |Represents|the|cmd|to|find
 *
 * Return: |NULL|, else|full|path|of|cmd|if|found
 */

char *find_path(riinfo_tvi *riinfovi, char *ripathstrvi, char *ricmdvi)
{
	int riivi = 0, ricurr_posvi = 0;
	char *ripathvi;

	if (!ripathstrvi)
		return (NULL);
	if ((_strlen(ricmdvi) > 2) && starts_with(ricmdvi, "./"))
	{
		if (is_cmd(riinfovi, ricmdvi))
			return (ricmdvi);
	}
	while (1)
	{
		if (!ripathstrvi[riivi] || ripathstrvi[riivi] == ':')
		{
			ripathvi = dup_chars(ripathstrvi, ricurr_posvi, riivi);
			if (!*ripathvi)
				_strcat(ripathvi, ricmdvi);
			else
			{
				_strcat(ripathvi, "/");
				_strcat(ripathvi, ricmdvi);
			}
			if (is_cmd(riinfovi, ripathvi))
				return (ripathvi);
			if (!ripathstrvi[riivi])
				break;
			ricurr_posvi = riivi;
		}
		riivi++;
	}
	return (NULL);
}
