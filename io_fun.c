#include "shell.h"

/**
 * get_history_file - gets file history
 * @info_init: srtuctre to containing arguments
 * Return: allocated string
 */

char *get_history_file(info_t *info_init)
{
	char *buffer, *dir;

	dir = _getenv(info_init, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcon(buffer, "/");
	_strcon(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates or appends to an existing file
 * @info_init: srtuctre to containing arguments
 * Return: 1(success) and -1 otherwise
 */
int write_history(info_t *info_init)
{
	ssize_t fh;
	list_t *node = NULL;
	char *file_name = get_history_file(info_init);

	if (!file_name)
		return (-1);

	fh = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fh == -1)
		return (-1);
	for (node = info_init->history; node; node = node->next)
	{
		_putsfd(node->s, fh);
		_putfd('\n', fh);
	}
	_putfd(BUF_FLUSH, fh);
	close(fh);
	return (1);
}

/**
 * read_history - reads the history from a file
 * @info_init: srtuctre to containing arguments
 * Return: histcount(success) and 0 otherwise
 */
int read_history(info_t *info_init)
{
	int i, end = 0, linec = 0;
	ssize_t fh, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *file_name = get_history_file(info_init);

	if (!file_name)
		return (0);
	fh = open(file_name, O_RDONLY);
	free(file_name);
	if (fh == -1)
		return (0);
	if (!fstat(fh, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fh, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fh);
	i = 0;
	while (i < fsize)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info_init, buffer + end, linec++);
			end = i + 1;
			i++;
		}
	if (end != i)
		build_history_list(info_init, buffer + end, linec++);
	free(buffer);
	info_init->histcount = linec;
	while (info->histcount-- >= HIST_MAX)
		delete_node(&(info_init->history), 0);
	renumber_history(info_init);
	return (info_init->histcount);
}

/**
 * build_history_list - adds an entry to a history linked list
 * @info_init: srtuctre to containing arguments
 * @buffer: buffer
 * @linec: history linecount
 * Return: 0 (success)
 */
int build_history_list(info_t *info_init, char *buffer, int linec)
{
	list_t *node = NULL;

	if (info_init->history)
		node = info_t->history;
	add_node_end(&node, buffer, linec);

	if (!info_init->history)
		info_init->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list after changes
 * @info_init: srtuctre to containing arguments
 * Return: new history count
 */
int renumber_history(info_t *info_init)
{
	list_t *node = info_init->history;
	int n = 0;

	while (node)
	{
		node->n = n++;
		node = node->next;
	}
	return (info_init->histcount = n);
}
