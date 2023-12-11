#include "shell.h"

/**
 * is_chaine - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pt: address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chaine(inf_t *inf, char *buff, size_t *pt)
{
	size_t j = *pt;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*pt = j;
	return (1);
}

/**
 * check_chaine - it checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pt: address of current position in buff
 * @i: starting position in buff
 * @ln: length of buff
 * Return: Void
 */
void check_chaine(inf_t *inf, char *buff, size_t *pt, size_t i, size_t ln)
{
	size_t j = *pt;

	if (inf->cmmd_buff_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = ln;
		}
	}
	if (inf->cmmd_buff_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = ln;
		}
	}

	*pt = j;
}

/**
 * replace_alia - it replaces an aliases in the tokenized string
 * @inf: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alia(inf_t *inf)
{
	int i;
	list_t *nod;
	char *pt;

	for (i = 0; i < 10; i++)
	{
		nod = nod_starts_with(inf->alia, inf->argv[0], '=');
		if (!nod)
			return (0);
		free(inf->argv[0]);
		pt = _stchr(nod->str, '=');
		if (!pt)
			return (0);
		pt = _stdup(pt + 1);
		if (!pt)
			return (0);
		inf->argv[0] = pt;
	}
	return (1);
}

/**
 * replace_var - it replaces vars in the tokenized string
 * @inf: the parameter structs
 * Return: 1 if replaced, 0 otherwise
 */
int replace_var(inf_t *inf)
{
	int i = 0;
	list_t *nod;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_stcmp(inf->argv[i], "$?"))
		{
			replace_str(&(inf->argv[i]),
				_stdup(convert_nm(inf->status, 10, 0)));
			continue;
		}
		if (!_stcmp(inf->argv[i], "$$"))
		{
			replace_str(&(inf->argv[i]),
				_stdup(convert_nm(getpid(), 10, 0)));
			continue;
		}
		nod = nod_starts_with(inf->envir, &inf->argv[i][1], '=');
		if (nod)
		{
			replace_str(&(inf->argv[i]),
				_stdup(_stchr(nod->str, '=') + 1));
			continue;
		}
		replace_str(&inf->argv[i], _stdup(""));

	}
	return (0);
}

/**
 * replace_str - it replaces string
 * @olds: address of old strings
 * @news: new strings
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **olds, char *news)
{
	free(*olds);
	*olds = news;
	return (1);
}
