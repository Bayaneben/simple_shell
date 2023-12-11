#include "shell.h"

/**
 * get_environment - it returns the string array copy of our environ
 * @inf: Structure contain potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environment(inf_t *inf)
{
	if (!inf->environ || inf->envir_changed)
	{
		inf->environ = list_to_string(inf->envir);
		inf->envir_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenvir - it Remove an environment variable
 * @inf: Structure contain potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string envir var property
 */
int _unsetenvir(inf_t *inf, char *var)
{
	list_t *nod = inf->envir;
	size_t i = 0;
	char *pt;

	if (!nod || !var)
		return (0);

	while (nod)
	{
		pt = start_with(nod->str, var);
		if (pt && *pt == '=')
		{
			inf->envir_changed = delete_nod_at_index(&(inf->envir), i);
			i = 0;
			nod = inf->envir;
			continue;
		}
		nod = nod->nx;
		i++;
	}
	return (inf->envir_changed);
}

/**
 * _setenvir -it iInitialize a new environment variable,
 *             or modified an existing one
 * @inf: Structure contain potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenvir(inf_t *inf, char *var, char *val)
{
	char *buff = NULL;
	list_t *nod;
	char *pt;

	if (!var || !val)
		return (0);

	buff = malloc(_stln(var) + _stln(val) + 2);
	if (!buff)
		return (1);
	_stcp(buff, var);
	_stcat(buff, "=");
	_stcat(buff, val);
	nod = inf->envir;
	while (nod)
	{
		pt = start_with(nod->str, var);
		if (pt && *pt == '=')
		{
			free(nod->str);
			nod->str = buff;
			inf->envir_changed = 1;
			return (0);
		}
		nod = nod->nx;
	}
	add_nod_end(&(inf->envir), buff, 0);
	free(buff);
	inf->envir_changed = 1;
	return (0);
}
