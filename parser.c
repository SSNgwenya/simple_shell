#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(const char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);
	return ((st.st_mode & S_IFREG) != 0);
}
/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
	static char buf[1024];
	int k = 0;

	for (int i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = '\0';
	return (buf);
}
/**
 * find_path - finds this cmd in the PATH string
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(const char *pathstr, const char *cmd)
{
	if (!pathstr)
		return (NULL);

	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (is_cmd(cmd))
			return (strdup(cmd));
	}

	int curr_pos = 0;

	for (int i = 0; pathstr[i] != '\0'; i++)
	{
		if (pathstr[i] == ':' || pathstr[i + 1] == '\0')
		{
			char *path = dup_chars(pathstr,
					curr_pos, i + (pathstr[i + 1] == '\0' ? 1 : 0));
			char *full_path;

			asprintf(&full_path, "%s/%s", path, cmd);
			if (is_cmd(full_path))
				return (full_path);
			free(full_path);
			curr_pos = i + 1;
		}
	}
	return (NULL);
}
