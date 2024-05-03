#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *ptr = dest;

	while (n && (*dest++ = *src++))
		n--;
	while (n--)
		*dest++ = '\0';

	return (ptr);
}

/**
 * _strncat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum number of bytes to be copied from src
 * Return: the pointer to the destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	char *ptr = dest;

	while (*dest)
		dest++;
	while (n && (*dest++ = *src++))
		n--;
	if (n == 0)
		*dest = '\0';

	return (ptr);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be searched
 * @c: the character to look for
 * Return: a pointer to the first occurrence of the character c in s,
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
