#include "shell.h"

/**
 * clear_info - |Function|that|initializes|info_t|struct
 * @riinfovi: |Represents|the|struct|address
 */

void clear_info(riinfo_tvi *riinfovi)
{
	riinfovi->riargvi = NULL;
	riinfovi->riargvvi = NULL;
	riinfovi->ripathvi = NULL;
	riinfovi->riargcvi = 0;
}

/**
 * set_info - |Function|that|initializes|info_t|struct
 * @riinfovi: |Represents|struct|address
 * @riavvi: |Represents|argument|vector
 */

void set_info(riinfo_tvi *riinfovi, char **riavvi)
{
	int riivi = 0;

	riinfovi->rifnamevi = riavvi[0];
	if (riinfovi->riargvi)
	{
		riinfovi->riargvvi = strtow(riinfovi->riargvi, " \t");
		if (!riinfovi->riargvvi)
		{
			riinfovi->riargvvi = malloc(sizeof(char *) * 2);
			if (riinfovi->riargvvi)
			{
				riinfovi->riargvvi[0] = _strdup(riinfovi->riargvi);
				riinfovi->riargvvi[1] = NULL;
			}
		}
		for (riivi = 0; riinfovi->riargvvi && riinfovi->riargvvi[riivi]; riivi++)
			;
		riinfovi->riargcvi = riivi;

		replace_alias(riinfovi);
		replace_vars(riinfovi);
	}
}

/**
 * free_info -|Function|that|frees|info_t|struct|fields
 * @riinfovi: |Represents|struct|address
 * @riallvi: |Represents|that|true|if|freeing|all|fields
 */

void free_info(riinfo_tvi *riinfovi, int riallvi)
{
	ffree(riinfovi->riargvvi);
	riinfovi->riargvvi = NULL;
	riinfovi->ripathvi = NULL;
	if (riallvi)
	{
		if (!riinfovi->ricmd_bufvi)
			free(riinfovi->riargvi);
		if (riinfovi->rienvvi)
			free_list(&(riinfovi->rienvvi));
		if (riinfovi->rihistoryvi)
			free_list(&(riinfovi->rihistoryvi));
		if (riinfovi->rialiasvi)
			free_list(&(riinfovi->rialiasvi));
		ffree(riinfovi->rienvironvi);
			riinfovi->rienvironvi = NULL;
		bfree((void **)riinfovi->ricmd_bufvi);
		if (riinfovi->rireadfdvi > 2)
			close(riinfovi->rireadfdvi);
		_putchar(RIBUF_FLUSHVI);
	}
}
