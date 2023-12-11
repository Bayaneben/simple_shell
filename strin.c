#include "shell.h"

/**
 * _stln - it returns the length of a string
 * @st: the string whose length to check
 * Return: integer length of string
 */
int _stln(char *st)
{
	int i = 0;

	if (!st)
		return (0);

	while (*st++)
		i++;
	return (i);
}

/**
 * _stcmp - it performs lexicogarphic comparison of two strangs.
 * @st1: the first strang
 * @st2: the second strang
 * Return: negative if st1 < st2, positive if st1 > st2, zero if st1 == st2
 */
int _stcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * start_with - checks if needle starts with haystack
 * @haystack: string to search it
 * @needl: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *haystack, const char *needl)
{
	while (*needl)
		if (*needl++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _stcat - it concatenates two strings
 * @ds: the destination buffer
 * @sr: the source buffer
 * Return: pointer to destination buffer
 */
char *_stcat(char *ds, char *sr)
{
	char *ret = ds;

	while (*ds)
		ds++;
	while (*sr)
		*ds++ = *sr++;
	*ds = *sr;
	return (ret);
}
