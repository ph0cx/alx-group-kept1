#include "shell.h"

/**
 * main - Represents entry point
 * @riacvi: Represents arg count
 * @riavvi: Represents arg vector
 *
 * Return: 0 on success, else 1 on error
 */

int main(int riacvi, char **riavvi)
{
	riinfo_tvi riinfovi[] = { RIINFO_INITVI };
	int rifdvi = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (rifdvi)
			: "r" (rifdvi));

	if (riacvi == 2)
	{
		rifdvi = open(riavvi[1], O_RDONLY);
		if (rifdvi == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(riavvi[0]);
				_eputs(": 0: Can't open ");
				_eputs(riavvi[1]);
				_eputchar('\n');
				_eputchar(RIBUF_FLUSHVI);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		riinfovi->rireadfdvi = rifdvi;
	}
	populate_env_list(riinfovi);
	read_history(riinfovi);
	hsh(riinfovi, riavvi);
	return (EXIT_SUCCESS);
}
