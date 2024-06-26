#include "shell.h"

/**
 * _myhistory - displays the history list with line numbers
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias
 * @info: Parameter struct.
 * @str: The string representing the alias.
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	*p = '\0';
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = '=';
	return (ret);
}

/**
 * set_alias - sets an alias
 * @info: Parameter struct.
 * @str: The string representing the alias.
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias
 * @node: The alias node.
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p;

	if (node)
	{
		p = _strchr(node->str, '=');
		if (p)
		{
			_putchar('\n');
			_puts("alias ");
			_write(1, node->str, p - node->str);
			_puts("='");
			_puts(p + 1);
			_puts("'\n");
			return (0);
		}
	}
	return (1);
}

/**
 * _myalias - displays or sets aliases
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
