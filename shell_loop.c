#include "shell.h"

/**
 * hsh -|m|a|i|n|s|h|e|l|l|l|o|o|p|
 * @riinfovi:|t|h|e|p|a|r|a|m|e|t|e|r|&|r|e|t|u|r|n|i|n|f|o|struct|
 * @riavvi:|t|h|e|a|r|g|u|m|e|n|t|v|e|c|t|o|r|f|r|o|m|m|a|i|n|(|)|
 *
 * Return: 0 |o|n| |success|, 1 |o|n| |error|, o|r e|r|r|o|r c|o|d|e
 */
int hsh(riinfo_tvi *riinfovi, char **riavvi)
{
	ssize_t rirvi = 0;
	int ribuiltin_retvi = 0;

	while (rirvi != -1 && ribuiltin_retvi != -2)
	{
		clear_info(riinfovi);
		if (interactive(riinfovi))
			_puts("$ ");
		_eputchar(RIBUF_FLUSHVI);
		rirvi = get_input(riinfovi);
		if (rirvi != -1)
		{
			set_info(riinfovi, riavvi);
			ribuiltin_retvi = find_builtin(riinfovi);
			if (ribuiltin_retvi == -1)
				find_cmd(riinfovi);
		}
		else if (interactive(riinfovi))
			_putchar('\n');
		free_info(riinfovi, 0);
	}
	write_history(riinfovi);
	free_info(riinfovi, 1);
	if (!interactive(riinfovi) && riinfovi->ristatusvi)
		exit(riinfovi->ristatusvi);
	if (ribuiltin_retvi == -2)
	{
		if (riinfovi->rierr_numvi == -1)
			exit(riinfovi->ristatusvi);
		exit(riinfovi->rierr_numvi);
	}
	return (ribuiltin_retvi);
}

/**
 * find_builtin -|f|i|n|d|s|a|b|u|i|l|t|i|n|c|o|m|m|a|n|d|
 * @riinfovi:|t|h|e|p|a|r|a|m|e|t|e|r|&|r|e|t|u|r|n|i|n|f|o|struct|
 *
 * Return: -1 |i|f| |b|u|i|l|t|i|n| |n|o|t| |f|o|u|n|d|,
 * 0 |if| |b|u|i|l|t|i|n| e|x|e|c|u||t|e|d| |s|u|c|c|e|s|s|f|u|l|l|y|,
 * 1 |if| |b|u|i|l|t|i|n| |f|o|u|n|d| |b|u|t |n|o|t| |s|u|c|c|e|s|s|f|u|l,
 * 2 |if| |b|u|i|l|t|i|n| |s|i|g|n|a|l|s| |exit()|
 */
int find_builtin(riinfo_tvi *riinfovi)
{
	int riivi, ribuilt_in_retvi = -1;
	ribuiltin_tablevi ribuiltintblvi[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (riivi = 0; ribuiltintblvi[riivi].ritypevi; riivi++)
		if (_strcmp(riinfovi->riargvvi[0], ribuiltintblvi[riivi].ritypevi) == 0)
		{
			riinfovi->riline_countvi++;
			ribuilt_in_retvi = ribuiltintblvi[riivi].rifuncvi(riinfovi);
			break;
		}
	return (ribuilt_in_retvi);
}

/**
 * find_cmd -|f|i|n|d|s|a|c|o|m|m|a|n|d|i|n|PATH|
 * @riinfovi:|t|h|e|p|a|r|a|m|e|t|e|r|&|r|e|t|u|r|n| info |struct|
 *
 * Return: void
 */
void find_cmd(riinfo_tvi *riinfovi)
{
	char *ripathvi = NULL;
	int riivi, rikvi;

	riinfovi->ripathvi = riinfovi->riargvvi[0];
	if (riinfovi->rilinecount_flagvi == 1)
	{
		riinfovi->riline_countvi++;
		riinfovi->rilinecount_flagvi = 0;
	}
	for (riivi = 0, rikvi = 0; riinfovi->riargvi[riivi]; riivi++)
		if (!is_delim(riinfovi->riargvi[riivi], " \t\n"))
			rikvi++;
	if (!rikvi)
		return;

	ripathvi = find_path(riinfovi, _getenv(riinfovi, "PATH="),
	riinfovi->riargvvi[0]);
	if (ripathvi)
	{
		riinfovi->ripathvi = ripathvi;
		fork_cmd(riinfovi);
	}
	else
	{
		if ((interactive(riinfovi) || _getenv(riinfovi, "PATH=")
					|| riinfovi->riargvvi[0][0] == '/') && is_cmd(riinfovi,
					riinfovi->riargvvi[0]))
			fork_cmd(riinfovi);
		else if (*(riinfovi->riargvi) != '\n')
		{
			riinfovi->ristatusvi = 127;
			print_error(riinfovi, "not found\n");
		}
	}
}

/**
 * fork_cmd - |f|o|r|k|s| |a| |a|n| |e|x|e|c| |t|h|r|e|a|d| |t|o| |r|u|n| |cmd|
 * @riinfovi: |t|h|e |p|a|r|a|m|e|t|e|r| |&| |r|e|t|u|r|n| |info| |struct|
 *
 * Return: void
 */
void fork_cmd(riinfo_tvi *riinfovi)
{
	pid_t richild_pidvi;

	richild_pidvi = fork();
	if (richild_pidvi == -1)
	{
		/*TODO:|P|U|T|E|R|R|O|R|F|U|N|C|T|I|O|N */
		perror("Error:");
		return;
	}
	if (richild_pidvi == 0)
	{
		if (execve(riinfovi->ripathvi, riinfovi->riargvvi,
		get_environ(riinfovi)) == -1)
		{
			free_info(riinfovi, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO:|P|U|T|E|R|R|O|R|F|U|N|C|T|I|O|N */
	}
	else
	{
		wait(&(riinfovi->ristatusvi));
		if (WIFEXITED(riinfovi->ristatusvi))
		{
			riinfovi->ristatusvi = WEXITSTATUS(riinfovi->ristatusvi);
			if (riinfovi->ristatusvi == 126)
				print_error(riinfovi, "Permission denied\n");
		}
	}
}
