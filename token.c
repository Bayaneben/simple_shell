#include "shell.h"

/**
 * **sttow - it splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **sttow(char *str, char *d)
{
	int i, j, k, m, nmwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], d) && (is_delimeter(str[i + 1], d) || !str[i + 1]))
			nmwords++;

	if (nmwords == 0)
		return (NULL);
	s = malloc((1 + nmwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nmwords; j++)
	{
		while (is_delimeter(str[i], d))
			i++;
		k = 0;
		while (!is_delimeter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **sttow2 - it splits a string into words
 * @str: the input string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **sttow2(char *str, char d)
{
	int i, j, l, n, nmwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			nmwords++;
	if (nmwords == 0)
		return (NULL);
	s = malloc((1 + nmwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nmwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		l = 0;
		while (str[i + l] != d && str[i + l] && str[i + l] != d)
			l++;
		s[j] = malloc((l + 1) * sizeof(char));
		if (!s[j])
		{
			for (l = 0; l < j; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[j][n] = str[i++];
		s[j][n] = 0;
	}
	s[j] = NULL;
	return (s);
}
