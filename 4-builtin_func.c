#include "shell.h"

/**
 *env - prints the current_environnement
 *@tokenized_command: command entered
 *
 *Return: void
 */

void env(char **tokenized_command __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_printf(environ[i], STDOUT_FILENO);
		_printf("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 * @tokenized_command: command entered
 *
 * Return: void
 */

void quit(char **tokenized_command)
{
	int num_token = 0, arg;

	for (; tokenized_command[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free_tokenized(tokenized_command);
		exit(1);
	}
	else if (num_token == 2)
	{
		arg = _atoi(tokenized_command[1]);
		if (arg == -1)
		{
		/*	_printf(shellName, STDERR_FILENO); */
			_printf(": 1: exit: Illegal number: ", STDERR_FILENO);
			_printf(tokenized_command[1], STDERR_FILENO);
			_printf("\n", STDERR_FILENO);
			exit(2);
		}
		else
		{
			free_tokenized(tokenized_command);
			exit(arg);
		}
	}
	else
		_printf("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
