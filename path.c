#include "shell.h"

/**
 * is_cmd - checks if  file is an executable command
 * @info_init: info struct
 * @path: file path
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info_init, char *path)
{
	struct stat st;

	(void)info_init;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates char
 * @pathstr: string PATH
 * @startd: start index
 * @stopd: stop index
 * Return: new buf pointer
 */
char *dup_chars(char *pathstr, int startd, int stopd)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = startd; i < stopd; i++)
		if (pathstr[i] != ':')
			buf[j++] = pathstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in PATH str
 * @info: info struct
 * @paths: string PATH
 * @cmd: cmd to find
 * Return: full path of cmd  or NULL if not found
 */
char *find_path(info_t *info, char *paths, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(cmd) > 2) && start(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paths[j] || paths[j] == ':')
		{
			path = dup_chars(paths, curr_pos, j);
			if (!*path)
				_strcon(path, cmd);
			else
			{
				_strcon(path, "/");
				_strcon(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!paths[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
