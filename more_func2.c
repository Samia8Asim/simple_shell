#include "shell.h"
/**
 * bfree - frees a pointer and NULLs
 * @p: address of the pointer
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
/**
 * interactive - returns true if shell is interactive
 * @info: the address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks if character is a delimeter
 * @c: the char
 * @d: the delimeter
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *d)
{
	while (*d)
		if (*d++ == c)
			return (1);
	return (0);
}
/**
 *_isalpha - checks for alphabetic character
 *@c: The character
 *Return: 1 if c is alphabet, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_atoi - converts string to integer
 *@s: the string
 *Return: 0 if no numbers
 */
int _atoi(char *s)
{
	int i, n = 1, flag = 0, o;
	unsigned int r = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			n *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			r *= 10;
			r += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (n == -1)
		o = -r;
	else
		o = r;

	return (o);
}
