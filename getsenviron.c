#include "shell.h"

/**
 * get_environ - returns a copy of the environment variables
 * @info: parameter struct
 * Return: pointer to array of environment variables
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: parameter struct
 * @var: the environment variable to remove
 * Return: 1 if deleted, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node;
	size_t index = 0;
	char *p;

	if (!info->env || !var)
		return (0);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: parameter struct
 * @var: the environment variable to set
 * @value: the value to assign to the environment variable
 * Return: 0 on success, 1 on failure
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf;
	list_t *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
