#include "shell.h"
/**
 * _strcon - concatenates two strings
 * @d: the destination buffer
 * @s: the source buffer
 * Return: pointer
 */
char *_strcon(char *d, char *s)
{
	char *r = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (r);
}
/**
 * _strcpy - copies a string
 * @d: the destination
 * @s: the source
 * Return: pointer
 */
char *_strcpy(char *d, char *s)
{
	int i;

	if (d == s || s == 0)
		return (d);
	for (i = 0; s[i] != '\0'; i++)
		d[i] = s[i];
	d[i] = 0;
	return (d);
}
/**
 * _strdup - duplicates a string
 * @s: string to duplicate
 * Return: pointer
 */
char *_strdup(const char *s)
{
	int l = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
		r[l] = *--s;
	return (r);
}
/**
 *_puts - prints an input string
 *@s: string
 * Return: Nothing
 */
void _puts(char *s)
{
	int i;

	if (!s)
		return;
	for (i = 0; s[i] != '\0'; i++)
		_putchar(s[i]);
}
/**
 * _putchar - writes char
 * @c: character
 * Return: 1,-1
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
