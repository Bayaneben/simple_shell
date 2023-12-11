#include "shell.h"

/**
 * hshel - main shell loop
 * @inf: the parameter & return info struct
 * @avec: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hshel(inf_t *inf, char **avec)
{
	ssize_t r = 0;
	int buildin_ret = 0;

	while (r != -1 && buildin_ret != -2)
	{
		clear_inf(inf);
		if (inter(inf))
			_puts("$ ");
		_eputc(BUF_FLUSH);
		r = get_inp(inf);
		if (r != -1)
		{
			set_inf(inf, avec);
			buildin_ret = find_buildin(inf);
			if (buildin_ret == -1)
				find_cmmd(inf);
		}
		else if (inter(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	write_hist(inf);
	free_inf(inf, 1);
	if (!inter(inf) && inf->status)
		exit(inf->status);
	if (buildin_ret == -2)
	{
		if (inf->err_nm == -1)
			exit(inf->status);
		exit(inf->err_nm);
	}
	return (buildin_ret);
}

/**
 * find_buildin - finds a builtin command
 * @inf: the parameter & return info structs
 * Return: -1 if buildin not found,
 *			0 if buildin executed successfully,
 *			1 if buildin found but not successful,
 *			-2 if buildin signals exit()
 */
int find_buildin(inf_t *inf)
{
	int i, build_in_ret = -1;
	buildin_table buildintbl[] = {
		{"exit", _myexits},
		{"env", _myenvir},
		{"help", _helpme},
		{"history", _myhist},
		{"setenv", _mysetenvir},
		{"unsetenv", _myunsetenvir},
		{"cd", _mycdir},
		{"alias", _myalia},
		{NULL, NULL}
	};

	for (i = 0; buildintbl[i].type; i++)
		if (_stcmp(inf->argv[0], buildintbl[i].type) == 0)
		{
			inf->line_ct++;
			build_in_ret = buildintbl[i].func(inf);
			break;
		}
	return (build_in_ret);
}

/**
 * find_cmmd - it finds a command in PATH
 * @inf: the parameter & return info struct
 * Return: void
 */
void find_cmmd(inf_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->linect_flag == 1)
	{
		inf->line_ct++;
		inf->linect_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_delimeter(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_paths(inf, _getenvir(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmmd(inf);
	}
	else
	{
		if ((inter(inf) || _getenvir(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmmd(inf, inf->argv[0]))
			fork_cmmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * fork_cmmd - it forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 * Return: void
 */
void fork_cmmd(inf_t *inf)
{
	pid_t child_pi;

	child_pi = fork();
	if (child_pi == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pi == 0)
	{
		if (execve(inf->path, inf->argv, get_environment(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}
