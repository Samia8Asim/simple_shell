#include "shell.h"
/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}
/**
 * _strcmp - comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 * Return: 0, negative, positive
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * start - checks if needle starts with haystack
 * @s: string to search
 * @w: the substring to find
 * Return: address
 */
char *start(const char *s, const char *w)
{
	while (*w)
		if (*w++ != *s++)
			return (NULL);
	return ((char *)s);
}
