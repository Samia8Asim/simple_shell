#include "shell.h"
/**
 **_memset - fills memory
 *@s: the pointer to the memory area
 *@y: the byte
 *@n: amount of bytes
 *Return: pointer
 */
char *_memset(char *s, char y, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = y;
	return (s);
}
/**
 * ffree - frees a string of strings
 * @s: string of strings
 */
void ffree(char **s)
{
	char **a = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(a);
}
/**
 * _realloc - reallocates
 * @p: pointer to previous
 * @o_size: byte size of previous one
 * @n_size: byte size of new one
 * Return: pointer
 */
void *_realloc(void *p, unsigned int o_size, unsigned int n_size)
{
	char *r;

	if (!p)
		return (malloc(n_size));
	if (!n_size)
		return (free(p), NULL);
	if (n_size == o_size)
		return (p);

	r = malloc(n_size);
	if (!r)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		r[o_size] = ((char *)p)[o_size];
	free(p);
	return (r);
}
