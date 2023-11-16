#include "shell.h"

/**
 * clear_info - initializes the struct info_t
 * @info_init: adress of struct
 */
void clear_info(info_t *info_init)
{
	info_init->arg = NULL;
	info_init->argv = NULL;
	info_init->path = NULL;
	info_init->argc = 0;
}

/**
 * set_info - initializes the struct info_t
 * @info_init: adress of struct
 * @avec: argument vector
 */
void set_info(info_t *info_init, char **avec)
{
	int i = 0;

	info_init->fname = avec[0];
	if (info_init->arg)
	{
		info_init->argv = strtow(info_init->arg, " \t");
		if (!info_init->argv)
		{
			info_init->argv = malloc(sizeof(char *) * 2);
			if (info_init->argv)
			{
				info_init->argv[0] = _strdup(info_init->arg);
				info_init->argv[1] = NULL;
			}
		}
		for (i = 0; info_init->argv && info_init->argv[i]; i++)
			;
		info_init->argc = i;
		replace_alias(info_init);
		replace_vars(info_init);
	}
}

/**
 * free_info - free the fields of info_t
 * @info_init:  initializes the struct info_t
 * @allf: true all fields are freed
 */
void free_info(info_t *info_init, int allf)
{
	ffree(info_init->argv);
	info_init->argv = NULL;
	info_init->path = NULL;

	if (allf)
	{
		if (!info_init->cmd_buf)
			free(info_init->arg);
		if (info_init->env)
			free_list(&(info_init->env));
		if (info_init->history)
			free_list(&(info_init->history));
		if (info_init->alias)
			free_list(&(info_init->alias));
		ffree(info_init->environ);
			info_init->environ = NULL;
		bfree((void **)info_init->cmd_buf);
		if (info_init->readfd > 2)
			close(info_init->readfd);
		_putchar(BUF_FLUSH);

	}
}
