#include "shell.h"

/**
 * list_ln - determines length of linked list
 * @q: pointer to first node
 * Return: size of list
 */
size_t list_ln(const list_t *q)
{
	size_t i = 0;

	while (q)
	{
		q = q->nx;
		i++;
	}
	return (i);
}

/**
 * list_to_string - returns an array of strings of the list->str
 * @hd: pointer to first node
 * Return: array of strings
 */
char **list_to_string(list_t *hd)
{
	list_t *nod = hd;
	size_t i = list_ln(hd), j;
	char **strs;
	char *str;

	if (!hd || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nod; nod = nod->nx, i++)
	{
		str = malloc(_stln(nod->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _stcp(str, nod->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_lt - prints all elements of a list_t linked list
 * @q: pointer to first node
 * Return: size of list
 */
size_t print_lt(const list_t *q)
{
	size_t i = 0;

	while (q)
	{
		_puts(convert_nm(q->nm, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(q->str ? q->str : "(nil)");
		_puts("\n");
		q = q->nx;
		i++;
	}
	return (i);
}

/**
 * nod_starts_with - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @prefix: string to match
 * @ch: the next character after prefix to match
 * Return: match node or null
 */
list_t *nod_starts_with(list_t *nod, char *prefix, char ch)
{
	char *pt = NULL;

	while (nod)
	{
		pt = start_with(nod->str, prefix);
		if (pt && ((ch == -1) || (*pt == ch)))
			return (nod);
		nod = nod->nx;
	}
	return (NULL);
}

/**
 * get_nod_index - gets the index of a node
 * @hd: pointer to list head
 * @nod: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_nod_index(list_t *hd, list_t *nod)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == nod)
			return (i);
		hd = hd->nx;
		i++;
	}
	return (-1);
}
