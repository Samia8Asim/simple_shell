#include "shell.h"

/**
 * _myhistory - function to display history list.
 * @info_init: srtuctre to containing arguments
 * Return: 0(success)
 */
int _myhistory(info_t *info_init)
{
	print_list(info_init->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info_init: srtuctre to containing arguments
 * @s: alias string
 * Return: 0(success) , 1(error)
 */
int unset_alias(info_t *info_init, char *s)
{
	int ret;
	char *ptr, ch;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(info_init->alias),
			get_node_index(info_init->alias,
				node_starts_with(info_init->alias, s, -1)));
	*ptr = ch;
	return (ret);
}

/**
 * set_alias - function that sets the alias to string
 * @info_init: srtuctre to containing arguments
 * @s: alias string
 * Return: Always 0(success),and 1 if (error)
 */
int set_alias(info_t *info_init, char *s)
{
	char *ptr;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info_init, s));

	unset_alias(info_init, s);
	return (add_node_end(&(info_init->alias), s, 0) == NULL);
}

/**
 * print_alias - function to print the alias string
 * @node: node of alias
 * Return: 0 (success), 1 (error)
 */
int print_alias(list_t *node)
{
	char *b = NULL, *ptr = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		b = node->str;
		while (b <= ptr)
		{
			_putchar(*b);
			b++;
		}
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function to mimics the builtin alias
 * @info: srtuctre to containing arguments
 * Return: 0(success)
 */
int _myalias(info_t *info_init)
{
	list_t *node = NULL;
	int i = 0;
	char *ptr = NULL;

	if (info_init->argc == 1)
	{
		node = info_init->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	i = 1;
	for (info_init->argv[i])
	{
		ptr = _strchr(info_init->argv[i], '=');
		if (p)
			set_alias(info_init, info_init->argv[i]);
		else
			print_alias(node_starts_with(info_init->alias, info_init->argv[i], '='));
		i++;
	}

	return (0);
}
