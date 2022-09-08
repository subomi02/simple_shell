#include "shell.h"

/**
 * ctrl_C_func - handles the signal raised by CTRL-C
 * @signum: signal number
 */
void ctrl_C_func(int signum)
{
	if (signum == SIGINT)
		_printf("\n($) ", STDIN_FILENO);
}

/**
 * shell_readline - read line from stdin
 *
 * Return: line read
 */

char *shell_readline(void)
{
	int bufsize = RL_BUFSIZE, nRead, position = 0;
	char *buffer = malloc(bufsize * sizeof(char));
	char c;

	if (!buffer)
	{
		perror("Failed to allocate space in memory");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		nRead = read(STDIN_FILENO, &c, 1);

		if (c == '\n' || !nRead || c == EOF)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;

		if (position >= bufsize)
		{
			bufsize += RL_BUFSIZE;
			buffer = _realloc(buffer, RL_BUFSIZE, bufsize);
			if (!buffer)
			{
				perror("Failed to re-allocate a space in memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * shell_launch - executes a command based on it type
 * @proccessed_cmd: processed character array
 * @cmd_type: the type of the command
 */
void shell_launch(char **proccessed_cmd, int cmd_type)
{
	void (*func)(char **command);

	switch (cmd_type)
	{
		case TERM_CMD:
			{
				if (execve(proccessed_cmd[0], proccessed_cmd, NULL) == -1)
				{
					perror(_getenv("PWD"));
					exit(2);
				}
				break;
			}
		case PATH_CMD:
			{
				if (execve(check_path(proccessed_cmd[0]), proccessed_cmd, NULL)
						== -1)
				{
					perror(_getenv("PWD"));
					exit(2);
				}
				break;
			}
		case INTERNAL_CMD:
			{
				func = get_func(proccessed_cmd[0]);
				func(proccessed_cmd);
				break;
			}
		case INVALID_CMD:
			{
			/*	_printf(shellName, STDERR_FILENO); */
				_printf(": 1: ", STDERR_FILENO);
				_printf(proccessed_cmd[0], STDERR_FILENO);
				_printf(": not found\n", STDERR_FILENO);
				exit(127);
			}
	}
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}
