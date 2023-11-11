#include "shell.h"
/**
 *_eputs - prints an input string
 * @s: the string to be printed
 */
void _eputs(char *s)
{
	int i;

	if (!s)
		return;
	for (i = 0; s[i] != '\0'; i++)
		_eputchar(s[i]);
}
/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(2, buf, r);
		r = 0;
	}
	if (c != BUF_FLUSH)
		buf[r++] = c;
	return (1);
}
/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @f: The filedescriptor to write
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int f)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(f, buf, r);
		r = 0;
	}
	if (c != BUF_FLUSH)
		buf[r++] = c;
	return (1);
}
/**
 *_putsfd - prints an input string
 * @s: the string to be printed
 * @f: the filedescriptor to write
 * Return: the number of chars
 */
int _putsfd(char *s, int f)
{
	int d = 0;

	if (!s)
		return (0);
	while (*s)
	{
		d += _putfd(*s++, f);
	}
	return (d);
}
