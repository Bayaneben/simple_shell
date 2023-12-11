#include "shell.h"

/**
 * _errstint - it converts a string to an integer
 * @st: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _errstint(char *st)
{
	int i = 0;
	unsigned long int res = 0;

	if (*st == '+')
		st++;  /* TODO: why does this make main return 255? */
	for (i = 0;  st[i] != '\0'; i++)
	{
		if (st[i] >= '0' && st[i] <= '9')
		{
			res *= 10;
			res += (st[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - it prints an error message
 * @inf: the parameter & return inf struct
 * @est: string contain specified error type
 * Return: 0 if no number in string, converted number otherwise
 *        -1 on error
 */
void print_err(inf_t *inf, char *est)
{
	_eput(inf->fname);
	_eput(": ");
	print_dc(inf->line_ct, STDERR_FILENO);
	_eput(": ");
	_eput(inf->argv[0]);
	_eput(": ");
	_eput(est);
}

/**
 * print_dc - function prints a decimals (integer) number (base 10)
 * @inp: the input
 * @fdsc: the filedescriptor to write too
 * Return: number of characters printed
 */
int print_dc(int inp, int fdsc)
{
	int (*__putchar)(char) = _putchar;
	int i, ct = 0;
	unsigned int _abs_, curr;

	if (fdsc == STDERR_FILENO)
		__putchar = _eputc;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = inp;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			ct++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	ct++;

	return (ct);
}

/**
 * convert_nm - it is a converter function, a clone of itoa
 * @nm: number
 * @bs: base
 * @flag: argument flag
 * Return: string
 */
char *convert_nm(long int nm, int bs, int flag)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = nm;

	if (!(flag & CONVERT_UNSIGNED) && nm < 0)
	{
		n = -nm;
		sign = '-';

	}
	arr = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % bs];
		n /= bs;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comment - function that replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 * Return: Always 0;
 */
void remove_comment(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
