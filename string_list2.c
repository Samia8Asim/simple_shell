#include "shell.h"
/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i;

	for (i = 0; h != NULL; i++)
		h = h->next;
	return (i);
}
/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **s;
	char *str;

	if (!head || !i)
		return (NULL);
	s = malloc(sizeof(char *) * (i + 1));
	if (!s)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->s) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}

		str = _strcpy(str, node->s);
		s[i] = str;
	}
	s[i] = NULL;
	return (s);
}
/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i;

	for (i = 0; h != NULL; i++)
	{
		_puts(convert_number(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
	}
	return (i);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pre: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *pre, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start(node->s, pre);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i;

	for (i = 0; head != NULL; i++)
	{
		if (head == node)
			return (i);
		head = head->next;
	}
	return (-1);
}
