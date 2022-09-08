#include "shell.h"

int is_delimeter(const char *delimeters, char c);

/**
 * tokenize - split a string
 * @str: string to split
 * @delim: charcter to split str
 * Return: pointer to new or NULL
 */
char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];
	char **arr;

	if (str == NULL || !(*str))
		return (NULL);
	/* calc no of words and lengths */
	for (i = 0; str[i]; i++)
	{
		/* skip delimeters */
		if (is_delimeter(delim, str[i]))
			continue;
		/* get the word length */
		j = i;
		while (!is_delimeter(delim, str[i]) && str[i])
			i++;
		if (i > j)
			lens[size++] = i - j;
		if (!str[i])
			break;
	}
	if (!size)
		return (NULL);
	/* create array of strings */
	arr = malloc((size + 1) * sizeof(char *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;
		/* copy the word */
		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimeter(delim, str[i]) && str[i])
			arr[k][j++] = str[i++];
		arr[k++][j] = '\0';
		if (!str[i])
			break;
	}
	arr[size] = NULL;
	return (arr);
}

/**
 * is_delimeter - check if a character is in delimeter
 *
 * @delimeters: pointer to delimeters
 * @c: character to check
 *
 * Return: 1 for true 0 for false
 */
int is_delimeter(const char *delimeters, char c)
{
	int i = 0;

	if (!delimeters)
		return (0);
	while (delimeters[i])
	{
		if (delimeters[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 *_strcmp - compare two strings
 *@first: first string to be compared
 *@second: second string to be compared
 *
 * Return: difference of the two strings
 */

int _strcmp(char *first, char *second)
{
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}
	return (first[i] - second[i]);
}

/**
 * free_tokenized - frees an array of arrays
 *
 * @tokens: pointer to array
 */
void free_tokenized(char **tokens)
{
	int i = 0;

	if (!tokens)
		return;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

/**
 * _strlen - gets the length of a string
 * @s: string pointer
 * Return: string length
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (-1);
	while(s[i])
		i++;
	return (i);
}
