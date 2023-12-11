#include "shell.h"

/**
 *_eput - it prints an input string
 * @st: the string to be printed
 * Return: Nothing
 */
void _eput(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_eputc(st[i]);
		i++;
	}
}

/**
 * _eputc - write the character c to stderr
 * @ch: The character to get it printed
 * Return: On success 1.
 * On error, -1 is return, and errno is set appropriately.
 */
int _eputc(char ch)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 * _putfdsc - it writes the character ch to given fdsc
 * @ch: The character to print
 * @fdsc: The filedescriptor to write too
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfdsc(char ch, int fdsc)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdsc, buff, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 *_putsfdsc - it prints an input string
 * @st: the string to be printed
 * @fdsc: the filedescriptor to write too
 * Return: the number of chars put
 */
int _putsfdsc(char *st, int fdsc)
{
	int i = 0;

	if (!st)
		return (0);
	while (*st)
	{
		i += _putfdsc(*st++, fdsc);
	}
	return (i);
}
