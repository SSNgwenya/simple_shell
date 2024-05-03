#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: Environment variable name
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node)
	{
		if (_strncmp(node->str, name, _strlen(name)) == 0)
			return (node->str + _strlen(name) + 1);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]) == 0)
		return (0);
	else
		return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
	{
		if (_unsetenv(info, info->argv[i]) == 0)
			return (0);
	}

	return (1);
}

/**
 * populate_env_list - populates env linked list with the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	size_t i;
	list_t *node = NULL;

	for (i = 0; environ[i] != NULL; i++)
		add_node_end(&node, _strdup(environ[i]), 0);

	info->env = node;
	return (0);
}
