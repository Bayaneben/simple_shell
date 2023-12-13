#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @ln: address of len var
 * Return: bytes read
 */
ssize_t input_buff(inf_t *inf, char **buff, size_t *ln)
{
	ssize_t r = 0;
	size_t ln_p = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfre((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, signintHandler);
#if USE_GETLINE
		r = getline(buff, &ln_p, stdin);
#else
		r = _getline(inf, buff, &ln_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->linect_flag = 1;
			remove_comment(*buff);
			build_hist_list(inf, *buff, inf->histct++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*ln = r;
				inf->cmmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_inp - it gets a line minus the newline
 * @inf: parameter struct
 * Return: bytes read
 */
ssize_t get_inp(inf_t *inf)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t i, j, ln;
	ssize_t r = 0;
	char **buff_p = &(inf->arg), *pt;

	_putchar(BUF_FLUSH);
	r = input_buff(inf, &buff, &ln);
	if (r == -1) /* EOF */
		return (-1);
	if (ln)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		pt = buff + i; /* get pointer for return */
		check_chaine(inf, buff, &j, i, ln);
		while (j < ln) /* iterate to semicolon or end */
		{
			if (is_chaine(inf, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= ln) /* reached end of buffer? */
		{
			i = ln = 0; /* reset position and length */
			inf->cmmd_buff_type = CMD_NORM;
		}

		*buff_p = pt; /* pass back pointer to current command position */
		return (_stln(pt)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buff(inf_t *inf, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->readfdsc, buff, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated ptr buffer if not NULL
 * Return: st
 */
int _getline(inf_t *inf, char **ptr, size_t *leng)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, ln;
	size_t k;
	ssize_t r = 0, s = 0;
	char *pt = NULL, *new_pt = NULL, *ch;

	pt = *ptr;
	if (pt && leng)
		s = *leng;
	if (i == ln)
		i = ln = 0;

	r = read_buff(inf, buff, &ln);
	if (r == -1 || (r == 0 && ln == 0))
		return (-1);

	ch = _stchr(buff + i, '\n');
	k = ch ? 1 + (unsigned int)(ch - buff) : ln;
	new_pt = _realoc(pt, s, s ? s + k : k + 1);
	if (!new_pt) /* MALLOC FAILURE! */
		return (pt ? free(pt), -1 : -1);

	if (s)
		_stncat(new_pt, buff + i, k - i);
	else
		_stncp(new_pt, buff + i, k - i + 1);

	s += k - i;
	i = k;
	pt = new_pt;

	if (leng)
		*leng = s;
	*ptr = pt;
	return (s);
}

/**
 * signintHandler - blocks ctrl-C
 * @sign_nm: the signal numbers
 * Return: void
 */
void signintHandler(__attribute__((unused))int sign_nm)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
