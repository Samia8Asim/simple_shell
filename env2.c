#include "shell.h"

/**
 * get_environ - returns the string copy of environ
 * @info_init: srtuctre to containing arguments
 * Return: 0(success)
 */
char **get_environ(info_t *info_init)
{
	if (!info_init->environ || info_init->env_changed)
	{
		info_init->environ = list_to_strings(info_init->env);
		info_init->env_changed = 0;
	}

	return (info_init->environ);
}

/**
 * _unsetenv - Remove the environment variable
 * @info_init: srtuctre to containing arguments
 * @str_var: property of string env var 
 * Return: 1 if removed, 0 otherwise
 */
int _unsetenv(info_t *info_init, char *str_var)
{
	char *ptr;
	list_t *node = info_init->env;
	size_t i = 0;


	if (!str_var || !node)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, str_var);
		if (ptr && *ptr == '=')
		{
			info_init->env_changed = delete_node_at_index(&(info_init->env), i);
			i = 0;
			node = info_init->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info_init->env_changed);
}

/**
 * _setenv - Initialize or modify environment variable
 * @info: srtuctre to containing arguments
 * @str_var: property of string env var
 * @val: value of string env var
 * Return: 0(success)
 */
int _setenv(info_t *info_init, char *str_var, char *val)
{
	char *ptr;
	char *buffer = NULL;
	list_t *node;


	if (!val || !str_var)
		return (0);

	buffer = malloc(_strlen(str_var) + _strlen(val) + 2);

	if (!buffer)
		return (1);
	_strcpy(buffer, str_var);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	node = info_init->env;
	while (node)
	{
		ptr = starts_with(node->str, str_var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info_init->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info_init->env), buffer, 0);
	free(buffer);
	info_init->env_changed = 1;
	return (0);
}
