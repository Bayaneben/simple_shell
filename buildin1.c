#include "shell.h"

/**
 * _myhist - It displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure contain potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhist(inf_t *inf)
{
	print_lt(inf->hist);
	return (0);
}

/**
 * unset_alia - it can sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alia(inf_t *inf, char *st)
{
	char *pt, ch;
	int ret;

	pt = _stchr(st, '=');
	if (!pt)
		return (1);
	ch = *pt;
	*pt = 0;
	ret = delete_nod_at_index(&(inf->alia),
		get_nod_index(inf->alia, nod_starts_with(inf->alia, st, -1)));
	*pt = ch;
	return (ret);
}

/**
 * set_alia - it sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alia(inf_t *inf, char *st)
{
	char *pt;

	pt = _stchr(st, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alia(inf, st));

	unset_alia(inf, st);
	return (add_nod_end(&(inf->alia), st, 0) == NULL);
}

/**
 * print_alia - it prints an alias string
 * @nod: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alia(list_t *nod)
{
	char *pt = NULL, *ar = NULL;

	if (nod)
	{
		pt = _stchr(nod->str, '=');
		for (ar = nod->str; ar <= pt; ar++)
			_putchar(*ar);
		_putchar('\'');
		_puts(pt + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalia - it mimics the alias builtin (man alias)
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalia(inf_t *inf)
{
	int i = 0;
	char *pt = NULL;
	list_t *nod = NULL;

	if (inf->argc == 1)
	{
		nod = inf->alia;
		while (nod)
		{
			print_alia(nod);
			nod = nod->nx;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		pt = _stchr(inf->argv[i], '=');
		if (pt)
			set_alia(inf, inf->argv[i]);
		else
			print_alia(nod_starts_with(inf->alia, inf->argv[i], '='));
	}

	return (0);
}
