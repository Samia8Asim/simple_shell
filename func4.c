#include "shell.h"
/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @d: the delimeter string
 * Return: pointer
 */
char **strtow(char *s, char *d)
{
	int i, j, k, m, n = 0;
	char **r;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_delim(s[i], d) && (is_delim(s[i + 1], d) || !s[i + 1]))
			n++;

	if (n == 0)
		return (NULL);
	r = malloc((1 + n) * sizeof(char *));
	if (!r)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (is_delim(s[i], d))
			i++;
		k = 0;
		while (!is_delim(s[i + k], d) && s[i + k])
			k++;
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
				free(r[k]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			r[j][m] = s[i++];
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}
/**
 * **strtow2 - splits a string to words
 * @st: the input string
 * @d: the delimeter
 * Return: a pointer
 */
char **strtow2(char *st, char d)
{
	int i, j, k, m, n = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != d && st[i + 1] == d) ||
		    (st[i] != d && !st[i + 1]) || st[i + 1] == d)
			n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (st[i] == d && st[i] != d)
			i++;
		k = 0;
		while (st[i + k] != d && st[i + k] && st[i + k] != d)
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
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
