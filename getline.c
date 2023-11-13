#include "shell.h"

/**
 * input_buf - commands buffers chained
 * @info_init: srtuctre to containing arguments
 * @buffer: buffer address buffer
 * @size: var size ddress
 * Return: bytes
 */
ssize_t input_buf(info_t *info_init, char **buffer, size_t *size)
{
	ssize_t r = 0;
	size_t size_p = 0;

	if (!*size) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &size_p, stdin);
#else
		r = _getline(info_init, buffer, &size_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info_init->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info_init, *buffer, info_init->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*size = r;
				info_init->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_input - function thatgets a line minus the newline
 * @info: srtuctre to containing arguments
 * Return: bytes
 */
ssize_t get_input(info_t *info_init)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, size;
	ssize_t r = 0;
	char **buf_ptr = &(info_init->arg), *ptr;

	_putchar(BUF_FLUSH);
	r = input_buf(info_init, &buffer, &size);
	if (r == -1) /* EOF */
		return (-1);
	if (size)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		ptr = buffer + i; /* get pointer for return */

		check_chain(info_init, buffer, &j, i, size);
		while (j < size) /* iterate to semicolon or end */
		{
			if (is_chain(info_init, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= size) /* reached end of buffer? */
		{
			i = size = 0; /* reset position and length */
			info_init->cmd_buf_type = CMD_NORM;
		}

		*buf_ptr = ptr; /* pass back pointer to current command position */
		return (_strlen(ptr)); /* return length of current command */
	}

	*buf_ptr = buffer; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - function that reads a buffer
 * @info_init: srtuctre to containing arguments
 * @buffer: buffer
 * @size: size
 * Return: r
 */
ssize_t read_buf(info_t *info_init, char *buffer, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(info_init->readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}

/**
 * _getline - function that gets the next line of input
 * @info_init: srtuctre to containing arguments
 * @p:  pointer to buffer address
 * @len: preallocated ptr buffer size
 * Return: s
 */
int _getline(info_t *info_init, char **p, size_t *len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, leng;
	size_t h;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *p;
	if (ptr && len)
		s = *len;
	if (i == leng)
		i = leng = 0;

	r = read_buf(info_init, buffer, &leng);
	if (r == -1 || (r == 0 && leng == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	h = c ? 1 + (unsigned int)(c - buffer) : leng;
	new_ptr = _realloc(ptr, s, s ? s + h : h + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		_strncon(new_ptr, buffer + i, h - i);
	else
		_strncpy(new_ptr, buffer + i, h - i + 1);

	s += h - i;
	i = h;
	ptr = new_ptr;

	if (len)
		*len = s;
	*p = ptr;
	return (s);
}

/**
 * sigintHandler - ctrl-C blocker
 * @s_num: the signal number
 */
void sigintHandler(__attribute__((unused))int s_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
