#include "shell.h"

/**
 * is_chain - function to test if current char is a chain delimeter
 * @info_init: srtuctre to containing arguments
 * @buffe: the charater buffer
 * @ptr: current position (in buf)adrdress 
 * Return: 1 (chain delimeter), 0 otherwise
 */
int is_chain(info_t *info_init, char *buffer, size_t *ptr)
{
	size_t i = *ptr;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[j] = 0;
		i++;
		info_init->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info_init->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';') /* found end of this command */
	{
		buffer[i] = 0; /* replace semicolon with null */
		info_init->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * check_chain - checks if should continue chaining based on last status
 * @info_init: srtuctre to containing arguments
 * @buffer: the character buffer
 * @ptr:  current position (in buffer) address 
 * @j: buffer starting position
 * @leng: length of buffer
 */
void check_chain(info_t *info_init, char *buffer, size_t *ptr, size_t j, size_t leng)
{
	size_t i = *ptr;

	if (info_init->cmd_buf_type == CMD_AND)
	{
		if (info_init->status)
		{
			buffer[i] = 0;
			i = leng;
		}
	}
	if (info_init->cmd_buf_type == CMD_OR)
	{
		if (!info_init->status)
		{
			buffer[i] = 0;
			i = leng;
		}
	}

	*ptr = i;
}

/**
 * replace_alias - function that replaces an aliases in the tokenized string
 * @info: srtuctre to containing arguments
 * Return: 1 (replaced), 0 otherwise
 */
int replace_alias(info_t *info_init)
{
	int j;
	list_t *node;
	char *ptr;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with(info_init->alias, info_init->argv[0], '=');
		if (!node)
			return (0);
		free(info_init->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info_init->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - function that replaces variables in the tokenized string
 * @info_init: srtuctre to containing arguments
 * Return: 1(replaced), 0 otherwise
 */
int replace_vars(info_t *info_init)
{
	int j = 0;
	list_t *node;

	for (j = 0; info_init->argv[j]; j++)
	{
		if (info_init->argv[j][0] != '$' || !info_init->argv[j][1])
			continue;

		if (!_strcmp(info_init->argv[j], "$?"))
		{
			replace_string(&(info_init->argv[j]),
					_strdup(convert_number(info_init->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info_init->argv[j], "$$"))
		{
			replace_string(&(info_init->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info_init->env, &info_init->argv[j][1], '=');
		if (node)
		{
			replace_string(&(info_init->argv[j]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info_init->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - function that replaces string
 * @old_str: old string address
 * @new_str: new string
 * Return: 1(replaced), 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
