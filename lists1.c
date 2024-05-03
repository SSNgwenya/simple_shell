#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		count++;
		h = h->next;
	}
	return (count);
}
/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t len = list_len(head);

	if (len == 0)
		return (NULL);

	char **strs = malloc(sizeof(char *) * (len + 1));

	if (strs == NULL)
		return (NULL);

	size_t i = 0;

	while (head != NULL)
	{
		strs[i] = strdup(head->str);
		if (strs[i] == NULL)
		{
			for (size_t j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		head = head->next;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		printf("%s\n", h->str ? h->str : "(nil)");
		h = h->next;
		count++;
	}
	return (count);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	while (node != NULL)
	{
		if (strncmp(node->str, prefix, strlen(prefix)) == 0 &&
				(c == -1 || node->str[strlen(prefix)] == c))
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
	ssize_t index = 0;

	while (head != NULL)
	{
		if (head == node)
			return (index);
		index++;
		head = head->next;
	}
	return (-1);
}
