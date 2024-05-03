#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new head of the list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->str = _strdup(str);

	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->num = num;
	new_node->next = *head;
	*head = new_node;

	return (new_node);
}
/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node added
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->str = _strdup(str);

	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}

	new_node->num = num;
	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
		return (new_node);
	}

	list_t *current = *head;

	while (current->next)
		current = current->next;

	current->next = new_node;
	return (new_node);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: number of nodes in the list
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}
/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	list_t *current = *head;
	list_t *prev = NULL;
	unsigned int i = 0;

	while (current && i < index)
	{
		prev = current;
		current = current->next;
		i++;
	}

	if (!current)
		return (0);

	prev->next = current->next;
	free(current->str);
	free(current);
	return (1);
}
/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	if (!head_ptr || !*head_ptr)
		return;

	list_t *current = *head_ptr;
	list_t *next;

	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}

	*head_ptr = NULL;
}
