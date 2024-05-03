#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *home_dir = _getenv(info, "HOME=");

	if (!home_dir)
		return (NULL);

	size_t dir_len = _strlen(home_dir);
	size_t file_len = _strlen(HIST_FILE);

	char *history_file = malloc(dir_len + file_len + 2);

	if (!history_file)
	{
		free(home_dir);
		return (NULL);
	}
	_strcpy(history_file, home_dir);
	_strcat(history_file, "/");
	_strcat(history_file, HIST_FILE);

	free(home_dir);
	return (history_file);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);

	FILE *file = fopen(filename, "w");

	free(filename);
	if (!file)
		return (-1);

	list_t *node = info->history;

	while (node)
	{
		fprintf(file, "%s\n", node->str);

		node = node->next;
	}
	fclose(file);
	return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
		return (0);

	FILE *file = fopen(filename, "r");

	free(filename);
	if (!file)
		return (0);

	char line[READ_BUF_SIZE];
	int linecount = 0;

	while (fgets(line, READ_BUF_SIZE, file))
	{
		line[strcspn(line, "\n")] = '\0';
		build_history_list(info, line, linecount++);
	}

	fclose(file);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);

	return (info->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t **head = &(info->history);

	add_node_end(head, buf, linecount);
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
