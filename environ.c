#include "shell.h"

/**
 * _myenvir - it prints the current environment
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenvir(inf_t *inf)
{
	print_list_str(inf->envir);
	return (0);
}

/**
 * _getenvir - it gets the value of an environ variable
 * @inf: Structure contain potential arguments. Used to maintain
 * @nam: env var name
 * Return: the value
 */
char *_getenvir(inf_t *inf, const char *nam)
{
	list_t *nod = inf->envir;
	char *pt;

	while (nod)
	{
		pt = start_with(nod->str, nam);
		if (pt && *pt)
			return (pt);
		nod = nod->nx;
	}
	return (NULL);
}

/**
 * _mysetenvir - it initialize a new environment variable,
 *             or modifying an existing one
 * @inf: Structure contain potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenvir(inf_t *inf)
{
	if (inf->argc != 3)
	{
		_eput("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvir(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenvir - it Removes an environment variable
 * @inf: Structure contain potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenvir(inf_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eput("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenvir(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_environment_list - it populates envir linked list
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(inf_t *inf)
{
	list_t *nod = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nod_end(&nod, environ[i], 0);
	inf->envir = nod;
	return (0);
}
