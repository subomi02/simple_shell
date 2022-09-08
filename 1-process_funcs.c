#include "shell.h"

/**
 * shell_loop - read a line(user input)
 *			check if the shell should be ran interactively or not
 *			remove comments from line if any
 *			parse or tokenize the read line
 *			execute the parsed command
 *			runs infinitely unless user types exit or CTRL-D
 */

void shell_loop(void)
{
	char *line;
	char **args, **command;
	int status, i = 0, command_type = 0;

	/* handle program interruption if CTRL-C is pressed */
	signal(SIGINT, ctrl_C_func);
	
	do {
		non_interractive();
		_printf(" ($) ", STDOUT_FILENO);
		line = shell_readline();
		remove_comment(line);

		args = tokenize(line, ";");

		while (args[i])
		{
			command = tokenize(args[i++], DELIM);
			if (!(command[0]))
			{
				free(command);
				break;
			}
			command_type = check_cmd_type(command[0]);
			status = shell_execute(command, command_type);
			free(command);
		}
		free(args);

	} while (status);

	free(line);
}


/**
 * non_interractive - runs the shell in non interactive mode
 */

void non_interractive(void)
{
	char **args, **command;
	char *line;
	int i = 0, command_type = 0, status;

	if (isatty(STDIN_FILENO) == 0)
	{
		line = shell_readline();
		remove_comment(line);
		
		args = tokenize(line, ";");
		while (args[i])
		{
			command = tokenize(args[i++], DELIM);
			if (!(command[0]))
			{
				free(command);
				break;
			}
			command_type = check_cmd_type(command[0]);
			status = shell_execute(command, command_type);
			free(command);
		}
		free(args);
		free(line);
		exit(status);
	}
}


/**
 * check_cmd_type - determines the type of the command
 * @command: command to be checked
 *
 * Return: constant variable representing the type of command
 */

int check_cmd_type(char *command)
{
	char *internal_cmd[] = {"exit", "env", NULL};
	char *path = NULL;
	int i = 0;

	while (command[i])
	{
		if (command[i++] == '/')
			return (TERM_CMD);
	}
	for (i = 0; internal_cmd[i]; i++)
	{
		if (_strcmp(command, internal_cmd[i]) == 0)
			return (INTERNAL_CMD);
	}

	path = check_path(command);
	if (path)
	{
		free(path);
		return (PATH_CMD);
	}
	return (INVALID_CMD);
}

/**
 * shell_execute - launches the command to be executed
 * @command: command to be launched
 * @cmd_type: type of the command to be executed
 * 
 * Return: 
 */
int shell_execute(char **command, int cmd_type)
{
	pid_t PID;
	int status;

	if (cmd_type == PATH_CMD || cmd_type == TERM_CMD)
	{
		PID = fork();
		if (PID == 0)
			shell_launch(command, cmd_type);
		else if (PID < 0)
		{
			perror("Error Creating fork");
			return (1);
		}
		else
			wait(&status);
		return (1);
	}
	else
		shell_launch(command, cmd_type);

	return (1);
}

/**
 * _atoi - changes a string to an integer
 * @s: the string to be changed
 *
 * Return: the converted int
 */
int _atoi(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}
