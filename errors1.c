#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(const char *s)
{
	unsigned long result = 0;
	int sign = 1;

	if (*s == '+')
		s++;  /* Ignore leading '+' */
	else if (*s == '-')
	{
		sign = -1;
		s++; /* Move past '-' */
	}

	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			result *= 10;
			result += (*s - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		s++;
	}

	return (sign * result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: void
 */
void print_error(const info_t *info, const char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int count = 0;
	unsigned int _abs_, current;
	int __putchar = (fd == STDERR_FILENO) ? _eputchar : _putchar;

	if (input < 0)
	{
		__putchar('-');
		_abs_ = -input;
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	do {
		__putchar('0' + current / 10);
		count++;
		current %= 10;
	} while (_abs_ /= 10);

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
		sign = '-';

	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = "0123456789ABCDEF"[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	while (*buf)
	{
		if (*buf == '#' && (buf == buf || *(buf - 1) == ' '))
		{
			*buf = '\0';
			break;
		}
		buf++;
	}
}
