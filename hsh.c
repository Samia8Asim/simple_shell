#include "shell.h"

/**
 * hsh - loop of main shell 
 * @info_init: srtuctre to containing arguments
 * @avec: main() argument vector 
 * Return: 0 (success), 1(error)
 */
int hsh(info_t *info_init, char **avec)
{
	ssize_t r = 0;
	int builtinRet = 0;

	while (r != -1 && builtinRet != -2)
	{
		clear_info(info_init);
		if (interactive(info_init))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info_init);
		if (r != -1)
		{
			set_info(info_init, avec);
			builtinRet = find_builtin(info_init);
			if (builtinRet == -1)
				find_cmd(info_init);
		}
		else if (interactive(info_init))
			_putchar('\n');
		free_info(info_init, 0);
	}
	write_history(info_init);
	free_info(info_init, 1);
	if (!interactive(info_init) && info_init->status)
		exit(info_init->status);
	if (builtinRet == -2)
	{
		if (info_init->err_num == -1)
			exit(info_init->status);
		exit(info_init->err_num);
	}
	return (builtinRet);
}

/**
 * find_builtin - function to find builtin command
 * @info_init: srtuctre to containing arguments
 * Return: -1 (builtin not found),
 *		0  (builtin executed successfully),
 * 		1 (builtin found but not successful),
 *		-2 (builtin signals exit())
 */
int find_builtin(info_t *info_init)
{
	int i, builtin_ret = -1;
	built_in_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info_init->argv[0], builtintbl[i].type) == 0)
		{
			info_init->line_count++;
			builtin_ret = builtintbl[i].func(info_init);
			break;
		}
	return (builtin_ret);
}

/**
 * find_cmd - function thar finds a command in PATH
 * @info: srtuctre to containing arguments
 */
void find_cmd(info_t *info_init)
{
	char *path = NULL;
	int j, k;

	info_init->path = info_inti->argv[0];
	if (info_init->linecount_flag == 1)
	{
		info_init->line_count++;
		info_init->linecount_flag = 0;
	}
	for (j = 0, k = 0; info_init->arg[j]; j++)
		if (!is_delim(info_init->arg[j], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info_init, _getenv(info_init, "PATH="), info_init->argv[0]);
	if (path)
	{
		info_init->path = path;
		fork_cmd(info_init);
	}
	else
	{
		if ((interactive(info_init) || _getenv(info_init, "PATH=")
					|| info_init->argv[0][0] == '/') && is_cmd(info_init, info_init->argv[0]))
			fork_cmd(info_init);
		else if (*(info_init->arg) != '\n')
		{
			info_init->status = 127;
			print_error(info_init, "not found\n");
		}
	}
}

/**
 * fork_cmd - function that forks an exec thread to run cmd
 * @info_init: srtuctre to containing arguments
 */
void fork_cmd(info_t *info_init)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{

		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(info_init->path, info_init->argv, get_environ(info_init)) == -1)
		{
			free_info(info_init, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info_init->status));
		if (WIFEXITED(info_init->status))
		{
			info_init->status = WEXITSTATUS(info_init->status);
			if (info_init->status == 126)
				print_error(info_init, "Permission denied\n");
		}
	}
}
