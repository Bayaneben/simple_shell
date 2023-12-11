#include "shell.h"

/**
 * _stcp - it copies a string
 * @ds: the destination
 * @sr: the source
 * Return: pointer to destination
 */
char *_stcp(char *ds, char *sr)
{
	int i = 0;

	if (ds == sr || sr == 0)
		return (ds);
	while (sr[i])
	{
		ds[i] = sr[i];
		i++;
	}
	ds[i] = 0;
	return (ds);
}

/**
 * _stdup - it duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_stdup(const char *str)
{
	int leng = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		leng++;
	ret = malloc(sizeof(char) * (leng + 1));
	if (!ret)
		return (NULL);
	for (leng++; leng--;)
		ret[leng] = *--str;
	return (ret);
}

/**
 *_puts - it prints an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - it writes the character c to stdout
 * @ch: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buff[j++] = ch;
	return (1);
}
