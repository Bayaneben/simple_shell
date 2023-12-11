#include "shell.h"

/**
 * clear_info - it initializes info_t struct
 * @inf: struct address
 */
void clear_inf(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes info_t struct
 * @inf: struct address
 * @avec: argument vector
 */
void set_inf(inf_t *inf, char **avec)
{
	int i = 0;

	inf->fname = avec[0];
	if (inf->arg)
	{
		inf->argv = sttow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _stdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		replace_alia(inf);
		replace_var(inf);
	}
}

/**
 * free_inf - frees info_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void free_inf(inf_t *inf, int all)
{
	ffrees(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmmd_buff)
			free(inf->arg);
		if (inf->envir)
			free_list(&(inf->envir));
		if (inf->hist)
			free_list(&(inf->hist));
		if (inf->alia)
			free_list(&(inf->alia));
		ffrees(inf->environ);
			inf->environ = NULL;
		bfre((void **)inf->cmmd_buff);
		if (inf->readfdsc > 2)
			close(inf->readfdsc);
		_putchar(BUF_FLUSH);
	}
}
