#include "shell.h"

/**
 * is_cmd - determines an executable command file
 * @info_init: srtuctre to containing arguments
 * @path: the file path
 * Return: 1 (true), 0 (false)
 */
int is_cmd(info_t *info_init, char *path)
{
	struct stat st;

	(void)info_init;
	if (stat(path, &st) || !path)
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function to duplicates characters
 * @str_path: the string of the path
 * @startidx: the starting index
 * @stopidx: the stopping index
 * Return:  new buffer pointer
 */
char *dup_chars(char *str_path, int startidx, int stopidx)
{
	int i = 0, k = 0;
	static char buffer[1024];

	k = 0;
	i = startidx;
	while (i < stopidx)
	{
		if (str_path[i] != ':')
			buffer[k++] = str_path[i];
		i++;
	}
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - function to find cmd in the PATH string
 * @info_init: srtuctre to containing arguments
 * @str_path: string of the path
 * @cmd: cmd to be find
 * Return: full path of cmd or NULL if not found
 */
char *find_path(info_t *info_init, char *str_path, char *cmd)
{
	char *path;
	int i = 0, pos = 0;

	if (!str_path)
		return (NULL);
	if ((_strlen(cmd) > 2) && start(cmd, "./"))
	{
		if (is_cmd(info_init, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			path = dup_chars(str_path, pos, i);
			if (!*path)
				_strcon(path, cmd);
			else
			{
				_strcon(path, "/");
				_strcon(path, cmd);
			}
			if (is_cmd(info_init, path))
				return (path);
			if (!str_path[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}
