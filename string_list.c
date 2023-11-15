#include "shell.h"
/**
 * add_node - adds a node to the start of the list
 * @h: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_node(list_t **h, const char *str, int num)
{
	list_t *new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->n = num;
	if (str)
	{
		new->s = _strdup(str);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}
/**
 * add_node_end - adds a node to the end of the list
 * @h: address of pointer
 * @s: str field of node
 * @n: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **h, const char *s, int n)
{
	list_t *new, *node;

	if (!h)
		return (NULL);

	node = *h;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->n = n;
	if (s)
	{
		new->s = _strdup(s);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*h = new;
	return (new);
}
/**
 * print_string - prints only the str element of a list_t
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_string(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * delete_node - deletes node at index
 * @h: address of pointer to first node
 * @idx: node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node(list_t **h, unsigned int idx)
{
	list_t *n, *prev_node;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!idx)
	{
		n = *h;
		*h = (*h)->next;
		free(n->s);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (i == idx)
		{
			prev_node->next = n->next;
			free(n->s);
			free(n);
			return (1);
		}
		i++;
		prev_node = n;
		n = n->next;
	}
	return (0);
}
/**
 * free_list - frees all nodes of a list
 * @h: address of pointer
 */
void free_list(list_t **h)
{
	list_t *n, *next, *head;

	if (!h || !*h)
		return;
	head = *h;
	n = head;
	while (n)
	{
		next = n->next;
		free(n->s);
		free(n);
		n = next;
	}
	*h = NULL;
}
