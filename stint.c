#include "shell.h"

/**
 * inter - returns true if shell is an interactive mode
 * @inf: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfdsc <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @ch: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char ch, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}

/**
 *_isalphabetic - checks for the alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalphabetic(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *stint - convert a string to an integer
 *@st: the string to be converted to an integer
 *Return: 0 if no numbers in string, converted number otherwise
 */

int stint(char *st)
{
	int i, sign = 1, flag = 0, out;
	unsigned int res = 0;

	for (i = 0;  st[i] != '\0' && flag != 2; i++)
	{
		if (st[i] == '-')
			sign *= -1;

		if (st[i] >= '0' && st[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (st[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -res;
	else
		out = res;

	return (out);
}
