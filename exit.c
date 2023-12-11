#include "shell.h"

/**
 **_stncp - copies a string
 *@ds: the destination string to be copied to
 *@sr: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_stncp(char *ds, char *sr, int n)
{
	int i, j;
	char *st = ds;

	i = 0;
	while (sr[i] != '\0' && i < n - 1)
	{
		ds[i] = sr[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			ds[j] = '\0';
			j++;
		}
	}
	return (st);
}

/**
 **_stncat - it concatenates two strings
 *@ds: the first string
 *@sr: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_stncat(char *ds, char *sr, int n)
{
	int i, j;
	char *st = ds;

	i = 0;
	j = 0;
	while (ds[i] != '\0')
		i++;
	while (sr[j] != '\0' && j < n)
	{
		ds[i] = sr[j];
		i++;
		j++;
	}
	if (j < n)
		ds[i] = '\0';
	return (st);
}

/**
 **_stchr - locates a character in a string
 *@st: the string to be parsed
 *@ch: the character to look for
 *Return: (st) a pointer to the memory area st
 */
char *_stchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
