#include "shell.h"

/**
 * _myenv - function that prints the current environment
 * @info_init: srtuctre to containing arguments
 * Return: 0 (success)
 */
int _myenv(info_t *info_init)
{
	print_list_str(info_init->env);
	return (0);
}

/**
 * _getenv: get environment variable value
 * @info_init: srtuctre to containing arguments
 * @vname: name of variable
 * Return: the variable value
 */
char *_getenv(info_t *info_init, const char *vname)
{
	info_t *node = info_init->env;
	char *ptr;

	while (node)
	{
		p = start_with(node->str, vname);
		if (ptr && *ptr)
		{
			return (ptr);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetvenv -  Initialize or modify environment variable
 * @info_init: srtuctre to containing arguments
 * Return: 0(success) 
 */
int _mysetvenv(info_t *info_init)
{
	if (info_init->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}

	if (_setenv(info_init, info_init->argv[1], info_init->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetvenv - function that removes the environmnt variable
 * @info_init: srtuctre to containing arguments
 * Return: 0(success) 
 */
int _myunsetvenv(info_t *info_init)
{
	int i;

	if (info_init->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info_init->argc; i++)
		_unsetenv(info, info_init->argv[i]);

	return (0);
}

/**
 * populate_env_list - function that populates the env linked list
 * @info_init:  srtuctre to containing arguments
 * Return: 0(success)
 */
int populate_env_list(info_t *info_init)
{
	list_t *node = NULL;
	size_t i = 0;

	while (environ[i])
	{
		add_node_end(&node, environ[i], 0);
		i++;
	}
	info_init->env = node;
	return (0);
}
