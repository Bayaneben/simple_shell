#include "shell.h"

/**
 * add_nod - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @nm: node index used by history
 * Return: size of list
 */
list_t *add_nod(list_t **hd, const char *str, int nm)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memoryset((void *)new_hd, 0, sizeof(list_t));
	new_hd->nm = nm;
	if (str)
	{
		new_hd->str = _stdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->nx = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * add_nod_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @nm: node index used by history
 * Return: size of list
 */
list_t *add_nod_end(list_t **hd, const char *str, int nm)
{
	list_t *new_nod, *nod;

	if (!hd)
		return (NULL);

	nod = *hd;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memoryset((void *)new_nod, 0, sizeof(list_t));
	new_nod->nm = nm;
	if (str)
	{
		new_nod->str = _stdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->nx)
			nod = nod->nx;
		nod->nx = new_nod;
	}
	else
		*hd = new_nod;
	return (new_nod);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @q: pointer to first nod
 * Return: size of list
 */
size_t print_list_str(const list_t *q)
{
	size_t i = 0;

	while (q)
	{
		_puts(q->str ? q->str : "(nil)");
		_puts("\n");
		q = q->nx;
		i++;
	}
	return (i);
}

/**
 * delete_nod_at_index - deletes node at given index
 * @hd: address of pointer to first node
 * @ind: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_nod_at_index(list_t **hd, unsigned int ind)
{
	list_t *nod, *prev_nod;
	unsigned int i = 0;

	if (!hd || !*hd)
		return (0);

	if (!ind)
	{
		nod = *hd;
		*hd = (*hd)->nx;
		free(nod->str);
		free(nod);
		return (1);
	}
	nod = *hd;
	while (nod)
	{
		if (i == ind)
		{
			prev_nod->nx = nod->nx;
			free(nod->str);
			free(nod);
			return (1);
		}
		i++;
		prev_nod = nod;
		nod = nod->nx;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @hd_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_t **hd_ptr)
{
	list_t *nod, *next_nod, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	nod = hd;
	while (nod)
	{
		next_nod = nod->nx;
		free(nod->str);
		free(nod);
		nod = next_nod;
	}
	*hd_ptr = NULL;
}
