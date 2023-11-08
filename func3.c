#include "shell.h"
/**
 **_strncpy - copies a string
 *@d: the destination
 *@sr: the source
 *@n: the amount of characters to be copied
 *Return: string
 */
char *_strncpy(char *d, char *sr, int n)
{
	int i, j;
	char *s = d;

	i = 0;
	while (sr[i] != '\0' && i < n - 1)
	{
		d[i] = sr[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (s);
}
/**
 **_strncat - concatenat
 *@d: the first string
 *@sr: second string
 *@n: the amount of bytes
 *Return: string
 */
char *_strncat(char *d, char *sr, int n)
{
	int i, j;
	char *s = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (sr[j] != '\0' && j < n)
	{
		d[i] = sr[j];
		i++;
		j++;
	}
	if (j < n)
		d[i] = '\0';
	return (s);
}
/**
 **_strchr - locates a character
 *@s: the string
 *@c: the character to look for
 *Return: pointer
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
