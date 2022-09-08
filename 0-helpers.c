#include "shell.h"

/**
 * _putchar - print a character
 * @c: character to print
 * Return: 0
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_str - prints a string
 *
 * @str: pointer to string
 * @fd: file descriptor to print to
 * Return: number of chars printed
 */
int _printf(char *str, int fd)
{
	if (!str)
		return (-1);
	return (write(fd, str, _strlen(str)));
}

/**
 * startsWith - check if s starts with ndl
 *
 * @s: the string to check
 * @ndl: the search string
 * Return: 0 if false
 * else returns the next index after ndl in s
 */
int startsWith(char *s, char *ndl)
{
	int i = 0;

	if (!s || !ndl)
		return (0);
	while (ndl[i])
	{
		if (ndl[i] != s[i])
			return (0);
		i++;
	}
	return (i);
}

/**
 * endsWith - check if s ends with ndl
 *
 * @s: the string to check
 * @ndl: the search string
 * Return: 0 if false
 * else returns the index before ndl in s
 */
int endsWith(char *s, char *ndl)
{
	int i, j;

	if (!s || !ndl)
		return (0);
	i = _strlen(s);
	j = _strlen(ndl);
	if (j > i)
		return (0);
	for (j--,i--; j >=0; j--, i--)
		if (ndl[j] != s[i])
			return (0);
	return (i);
}

/**
 * _strdup - duplicates a string
 *
 * @s: pointer to string
 * Return: pointer to duplicate
 */
char *_strdup(char *s)
{
	int i;
	char *res;

	if (!s)
		return (0);
	res = malloc(_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
