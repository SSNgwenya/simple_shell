#include "shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(const char *str)
{
	if (!str)
		return;
	while (*str)
		_eputchar(*str++);
}
/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int index;

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE - 1)
	{
		write(STDERR_FILENO, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}
/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int index;

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE - 1)
	{
		write(fd, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}
/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(const char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += _putfd(*str++, fd);
	}
	return (count);
}
