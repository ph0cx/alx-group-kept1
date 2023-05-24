#include "shell.h"

/**
 * add_node - |Function|that/adds/a/node/to/the/start/of/the/list
 * @riheadvi: |Represents/address/of/pointer/to/head/node
 * @ristrvi: |Represents|str/field/of/node
 * @rinumvi: |Represents|node/index/used/by/history
 *
 * Return:/size/of/list
 */

rilist_tvi *add_node(rilist_tvi **riheadvi, const char *ristrvi, int rinumvi)
{
	rilist_tvi *rinew_headvi;

	if (!riheadvi)
		return (NULL);
	rinew_headvi = malloc(sizeof(rilist_tvi));
	if (!rinew_headvi)
		return (NULL);
	_memset((void *)rinew_headvi, 0, sizeof(rilist_tvi));
	rinew_headvi->rinumvi = rinumvi;
	if (ristrvi)
	{
		rinew_headvi->ristrvi = _strdup(ristrvi);
		if (!rinew_headvi->ristrvi)
		{
			free(rinew_headvi);
			return (NULL);
		}
	}
	rinew_headvi->rinextvi = *riheadvi;
	*riheadvi = rinew_headvi;
	return (rinew_headvi);
}

/**
 * add_node_end - |Functions|that/adds/a/node/to/the/end/of/the/list
 * @riheadvi: |Represents|the|address/of/pointer/to/head/node
 * @ristrvi: |Represents|str/field/of/node
 * @rinumvi: |Represents|node/index/used/by/history
 *
 * Return:/size/of/list
 */

rilist_tvi *add_node_end(rilist_tvi **riheadvi, const char *ristrvi,
	int rinumvi)
{
	rilist_tvi *rinew_nodevi, *rinodevi;

	if (!riheadvi)
		return (NULL);

	rinodevi = *riheadvi;
	rinew_nodevi = malloc(sizeof(rilist_tvi));
	if (!rinew_nodevi)
		return (NULL);
	_memset((void *)rinew_nodevi, 0, sizeof(rilist_tvi));
	rinew_nodevi->rinumvi = rinumvi;
	if (ristrvi)
	{
		rinew_nodevi->ristrvi = _strdup(ristrvi);
		if (!rinew_nodevi->ristrvi)
		{
			free(rinew_nodevi);
			return (NULL);
		}
	}
	if (rinodevi)
	{
		while (rinodevi->rinextvi)
			rinodevi = rinodevi->rinextvi;
		rinodevi->rinextvi = rinew_nodevi;
	}
	else
		*riheadvi = rinew_nodevi;
	return (rinew_nodevi);
}

/**
 * print_list_str - |Function|that/prints/only/
 * the/str/element/of/a/list_t/linked/list
 * @rihvi: |Represents|the/pointer/to/first/node
 *
 * Return: /size/of/list
 */

size_t print_list_str(const rilist_tvi *rihvi)
{
	size_t riivi = 0;

	while (rihvi)
	{
		_puts(rihvi->ristrvi ? rihvi->ristrvi : "(nil)");
		_puts("\n");
		rihvi = rihvi->rinextvi;
		riivi++;
	}
	return (riivi);
}

/**
 * delete_node_at_index - Function|that/deletes/node/at/given/index
 * @riheadvi: /Represents|the|address/of/pointer/to/first/node
 * @riindexvi: |Represents|the/index/of/node/to/delete
 *
 * Return: /1/on/success,/0/when|successful
 */

int delete_node_at_index(rilist_tvi **riheadvi, unsigned int riindexvi)
{
	rilist_tvi *rinodevi, *riprev_nodevi;
	unsigned int riivi = 0;

	if (!riheadvi || !*riheadvi)
		return (0);

	if (!riindexvi)
	{
		rinodevi = *riheadvi;
		*riheadvi = (*riheadvi)->rinextvi;
		free(rinodevi->ristrvi);
		free(rinodevi);
		return (1);
	}
	rinodevi = *riheadvi;
	while (rinodevi)
	{
		if (riivi == riindexvi)
		{
			riprev_nodevi->rinextvi = rinodevi->rinextvi;
			free(rinodevi->ristrvi);
			free(rinodevi);
			return (1);
		}
		riivi++;
		riprev_nodevi = rinodevi;
		rinodevi = rinodevi->rinextvi;
	}
	return (0);
}

/**
 * free_list - |Function|that/frees/all/nodes/of/a/list
 * @rihead_ptrvi: |Represents|the/address/of/pointer/to/head/node
 *
 * Return: /void/
 */

void free_list(rilist_tvi **rihead_ptrvi)
{
	rilist_tvi *rinodevi, *rinext_nodevi, *riheadvi;

	if (!rihead_ptrvi || !*rihead_ptrvi)
		return;
	riheadvi = *rihead_ptrvi;
	rinodevi = riheadvi;
	while (rinodevi)
	{
		rinext_nodevi = rinodevi->rinextvi;
		free(rinodevi->ristrvi);
		free(rinodevi);
		rinodevi = rinext_nodevi;
	}
	*rihead_ptrvi = NULL;
}
