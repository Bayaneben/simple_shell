#include "shell.h"

/**
 * is_cmmd - it determines if a file is an executable command
 * @inf: the info struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_cmmd(inf_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_char - show duplicates characters
 * @pathst: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_char(char *pathst, int start, int stop)
{
	static char buff[1024];
	int i = 0, l = 0;

	for (l = 0, i = start; i < stop; i++)
		if (pathst[i] != ':')
			buff[l++] = pathst[i];
	buff[l] = 0;
	return (buff);
}

/**
 * find_paths - finds this cmd in the PATH string
 * @inf: the info struct
 * @pathst: the PATH string
 * @cmmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_paths(inf_t *inf, char *pathst, char *cmmd)
{
	int i = 0, curr_posi = 0;
	char *path;

	if (!pathst)
		return (NULL);
	if ((_stln(cmmd) > 2) && start_with(cmmd, "./"))
	{
		if (is_cmmd(inf, cmmd))
			return (cmmd);
	}
	while (1)
	{
		if (!pathst[i] || pathst[i] == ':')
		{
			path = dup_char(pathst, curr_posi, i);
			if (!*path)
				_stcat(path, cmmd);
			else
			{
				_stcat(path, "/");
				_stcat(path, cmmd);
			}
			if (is_cmmd(inf, path))
				return (path);
			if (!pathst[i])
				break;
			curr_posi = i;
		}
		i++;
	}
	return (NULL);
}
