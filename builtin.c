#include "shell.h"

/**
 * _myexit - |Function|that|exits|the|shell
 * @riinfovi: |Structure|containing|potential|arguments to|maintain
 * constant|function|prototype.
 * Return: |0|if info.argv[0] != "exit".
 * |exits|with|a|given|exit|status
 */

int _myexit(riinfo_tvi *riinfovi)
{
	int riexitcheckvi;

	if (riinfovi->riargvvi[1]) /*|If|there|is|an|exit|arguement */
	{
		riexitcheckvi = _erratoi(riinfovi->riargvvi[1]);
		if (riexitcheckvi == -1)
		{
			riinfovi->ristatusvi = 2;
			print_error(riinfovi, "Illegal number: ");
			_eputs(riinfovi->riargvvi[1]);
			_eputchar('\n');
			return (1);
		}
		riinfovi->rierr_numvi = _erratoi(riinfovi->riargvvi[1]);
		return (-2);
	}
	riinfovi->rierr_numvi = -1;
	return (-2);
}

/**
 * _mycd - |Function|that|changes|the|current|directory|of|the|process
 * @riinfovi: |Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 * Return: |Always|0
 */

int _mycd(riinfo_tvi *riinfovi)
{
	char *risvi, *ridirvi, ribuffervi[1024];
	int richdir_retvi;

	risvi = getcwd(ribuffervi, 1024);
	if (!risvi)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!riinfovi->riargvvi[1])
	{
		ridirvi = _getenv(riinfovi, "HOME=");
		if (!ridirvi)
			richdir_retvi = /*|TODO:|what|exactly|should|this|be?|*/
				chdir((ridirvi = _getenv(riinfovi, "PWD=")) ? ridirvi : "/");
		else
			richdir_retvi = chdir(ridirvi);
	}
	else if (_strcmp(riinfovi->riargvvi[1], "-") == 0)
	{
		if (!_getenv(riinfovi, "OLDPWD="))
		{
			_puts(risvi);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(riinfovi, "OLDPWD=")), _putchar('\n');
		richdir_retvi = /*|TODO:|what|exactly|should|this|be?|*/
			chdir((ridirvi = _getenv(riinfovi, "OLDPWD=")) ? ridirvi : "/");
	}
	else
		richdir_retvi = chdir(riinfovi->riargvvi[1]);
	if (richdir_retvi == -1)
	{
		print_error(riinfovi, "can't cd to ");
		_eputs(riinfovi->riargvvi[1]), _eputchar('\n');
	}
	else
	{
		_setenv(riinfovi, "OLDPWD", _getenv(riinfovi, "PWD="));
		_setenv(riinfovi, "PWD", getcwd(ribuffervi, 1024));
	}
	return (0);
}

/**
 * _myhelp -Function|that|changes|the|current|directory|of|the|process
 * @riinfovi:|Structure|containing|potential|arguments|to|maintain
 * constant|function|prototype.
 * Return: |Always|0|if|successful
 */

int _myhelp(riinfo_tvi *riinfovi)
{
	char **riarg_arrayvi;

	riarg_arrayvi = riinfovi->riargvvi;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*riarg_arrayvi); /*|temp|att_unused|workaround */
	return (0);
}
