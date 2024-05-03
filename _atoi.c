#include "shell.h"

/**
 * interactive - checks if shell is in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && (info->readfd <= 2));
}
/**
 * is_delim - checks if character is a delimiter
 * @c: character to be checked
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}
/**
 * _isalpha - checks for alphabetic character
 * @c: The character to b checked
 * Return: 1 if c is alphabetic, 0 if not
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number othrwise
 */
int _atoi(char *s)
{
	int sign = 1, output = 0;

	while (*s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
			output = output * 10 + (*s - '0');
		else if (output != 0)
			break;
		s++;
	}
	return (sign * output);
}
