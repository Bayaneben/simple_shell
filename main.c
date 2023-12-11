#include "shell.h"

/**
 * main - entry point
 * @arc: arg count
 * @avec: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **avec)
{
	inf_t inf[] = { INF_INIT };
	int fdsc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdsc)
		: "r" (fdsc));

	if (arc == 2)
	{
		fdsc = open(avec[1], O_RDONLY);
		if (fdsc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eput(avec[0]);
				_eput(": 0: Can't open ");
				_eput(avec[1]);
				_eputc('\n');
				_eputc(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfdsc = fdsc;
	}
	populate_environment_list(inf);
	read_hist(inf);
	hshel(inf, avec);
	return (EXIT_SUCCESS);
}
