#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @inf: parameter struct
 * Return: allocated string containg history file
 */

char *get_hist_file(inf_t *inf)
{
	char *buff, *direct;

	direct = _getenvir(inf, "HOME=");
	if (!direct)
		return (NULL);
	buff = malloc(sizeof(char) * (_stln(direct) + _stln(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_stcp(buff, direct);
	_stcat(buff, "/");
	_stcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_hist - it creates a file, or appends to an existing file
 * @inf: the parameter structer
 * Return: 1 on success, else -1
 */
int write_hist(inf_t *inf)
{
	ssize_t fdsc;
	char *filename = get_hist_file(inf);
	list_t *nod = NULL;

	if (!filename)
		return (-1);

	fdsc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdsc == -1)
		return (-1);
	for (nod = inf->hist; nod; nod = nod->nx)
	{
		_putsfdsc(nod->str, fdsc);
		_putfdsc('\n', fdsc);
	}
	_putfdsc(BUF_FLUSH, fdsc);
	close(fdsc);
	return (1);
}

/**
 * read_hist - it reads history from file
 * @inf: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_hist(inf_t *inf)
{
	int i, lt = 0, linect = 0;
	ssize_t fdsc, rdln, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_hist_file(inf);

	if (!filename)
		return (0);

	fdsc = open(filename, O_RDONLY);
	free(filename);
	if (fdsc == -1)
		return (0);
	if (!fstat(fdsc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdln = read(fdsc, buff, fsize);
	buff[fsize] = 0;
	if (rdln <= 0)
		return (free(buff), 0);
	close(fdsc);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_hist_list(inf, buff + lt, linect++);
			lt = i + 1;
		}
	if (lt != i)
		build_hist_list(inf, buff + lt, linect++);
	free(buff);
	inf->histct = linect;
	while (inf->histct-- >= HIST_MAX)
		delete_nod_at_index(&(inf->hist), 0);
	renumber_hist(inf);
	return (inf->histct);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linect: the history linecount, histcount
 * Return: Always 0
 */
int build_hist_list(inf_t *inf, char *buff, int linect)
{
	list_t *nod = NULL;

	if (inf->hist)
		nod = inf->hist;
	add_nod_end(&nod, buff, linect);

	if (!inf->hist)
		inf->hist = nod;
	return (0);
}

/**
 * renumber_hist - renumbers the history linked list after changes
 * @inf: Structure contain potential arguments. Used to maintain
 * Return: the new histcount
 */
int renumber_hist(inf_t *inf)
{
	list_t *nod = inf->hist;
	int i = 0;

	while (nod)
	{
		nod->nm = i++;
		nod = nod->nx;
	}
	return (inf->histct = i);
}
