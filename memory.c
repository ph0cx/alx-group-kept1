#include "shell.h"

/**
 * bfree - Function that frees a pointer and NULLs the address
 * @riptrvi: Represents the address of the pointer to free
 *
 * Return: 0, else 1 if freed
 */

int bfree(void **riptrvi)
{
	if (riptrvi && *riptrvi)
	{
		free(*riptrvi);
		*riptrvi = NULL;
		return (1);
	}
	return (0);
}
