#include "shell.h"

/**
 **_memoryset - it fills memory with a constant byte
 *@s: the pointer to the memory area
 *@by: the byte to fill *s with
 *@nb: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memoryset(char *s, char by, unsigned int nb)
{
	unsigned int i;

	for (i = 0; i < nb; i++)
		s[i] = by;
	return (s);
}

/**
 * ffrees - it frees a string of strings
 * @pp: string of strings
 */
void ffrees(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * _realoc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_siz: byte size of previous block
 * @new_siz: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realoc(void *ptr, unsigned int old_siz, unsigned int new_siz)
{
	char *p;

	if (!ptr)
		return (malloc(new_siz));
	if (!new_siz)
		return (free(ptr), NULL);
	if (new_siz == old_siz)
		return (ptr);

	p = malloc(new_siz);
	if (!p)
		return (NULL);

	old_siz = old_siz < new_siz ? old_siz : new_siz;
	while (old_siz--)
		p[old_siz] = ((char *)ptr)[old_siz];
	free(ptr);
	return (p);
}
