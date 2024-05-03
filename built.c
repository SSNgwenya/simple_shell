#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit_status = 0;

	if (info->argv[1])
	{
		exit_status = atoi(info->argv[1]);
		if (exit_status == 0 && info->argv[1][0] != '0')
		{
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			info->status = 2;
			return (1);
		}
		return (exit_status);
	}
	return (exit_status);
}
/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir;
	int chdir_ret;

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME");
		if (!dir)
			dir = _getenv(info, "PWD");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD");
	}
	else
	{
		dir = info->argv[1];
	}
	if (!dir)
	{
		print_error(info, "Directory not found\n");
		return (1);
	}
	chdir_ret = chdir(dir);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD"));
		_setenv(info, "PWD", dir);
	}
	return (0);
}
/**
 * _myhelp - displays help message
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	(void)info;
	_puts("Shell Help:\n");
	_puts("Type 'exit' to exit the shell\n");
	_puts("Type 'cd' to change the current directory\n");
	_puts("Type 'help' to display this help message\n");
	return (0);
}
