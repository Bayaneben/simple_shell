#include "shell.h"

/**
 * _myexits - to exit the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exit with a given exit status
 *         (0) if inf.argv[0] != "exit"
 */
int _myexits(inf_t *inf)
{
	int exitchecker;

	if (inf->argv[1])  /* If there is an exit arguements */
	{
		exitchecker = _errstint(inf->argv[1]);
		if (exitchecker == -1)
		{
			inf->status = 2;
			print_err(inf, "Illegal number: ");
			_eput(inf->argv[1]);
			_eputc('\n');
			return (1);
		}
		inf->err_nm = _errstint(inf->argv[1]);
		return (-2);
	}
	inf->err_nm = -1;
	return (-2);
}

/**
 * _mycdir - change the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycdir(inf_t *inf)
{
	char *sh, *direct, buffer[1024];
	int chdir_ret;

	sh = getcwd(buffer, 1024);
	if (!sh)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		direct = _getenvir(inf, "HOME=");
		if (!direct)
			chdir_ret = /* TODO: what should this be? */
				chdir((direct = _getenvir(inf, "PWD=")) ? direct : "/");
		else
			chdir_ret = chdir(direct);
	}
	else if (_stcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenvir(inf, "OLDPWD="))
		{
			_puts(sh);
			_putchar('\n');
			return (1);
		}
		_puts(_getenvir(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((direct = _getenvir(inf, "OLDPWD=")) ? direct : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(inf, "can't cd to ");
		_eput(inf->argv[1]), _eputc('\n');
	}
	else
	{
		_setenvir(inf, "OLDPWD", _getenvir(inf, "PWD="));
		_setenvir(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _helpme - changes the current directory of the process
 * @inf: structure contain potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _helpme(inf_t *inf)
{
	char **arg_arr;

	arg_arr = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp is an att_unused workaround */
	return (0);
}
