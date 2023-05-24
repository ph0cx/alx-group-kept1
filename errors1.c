#include "shell.h"

/**
 * _erratoi - Function|that|converts|a|string|to|an|integer
 * @risvi:|the|string|value|to|be|converted
 * Return:|-1|on|error|else|0|if|no|converted|numbers|in|string
 *
 */

int _erratoi(char *risvi)
{
	int riivi = 0;
	unsigned long int riresultvi = 0;

	if (*risvi == '+')
		risvi++;  /*|TODO:|why|does|this|make|main|return|255?|*/
	for (riivi = 0;  risvi[riivi] != '\0'; riivi++)
	{
		if (risvi[riivi] >= '0' && risvi[riivi] <= '9')
		{
			riresultvi *= 10;
			riresultvi += (risvi[riivi] - '0');
			if (riresultvi > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (riresultvi);
}

/**
 * print_error - |Function|that|prints|an|error|message
 * @riinfovi:|the|parameter|&|return|info|struct
 * @riestrvi:|string|containing|specified|error|type
 * Return: |-1|on|error|else|0|if|no|converted|numbers|in|string
 *
 */

void print_error(riinfo_tvi *riinfovi, char *riestrvi)
{
	_eputs(riinfovi->rifnamevi);
	_eputs(": ");
	print_d(riinfovi->riline_countvi, STDERR_FILENO);
	_eputs(": ");
	_eputs(riinfovi->riargvvi[0]);
	_eputs(": ");
	_eputs(riestrvi);
}

/**
 * print_d - |function|that|prints|a|decimal|(integer)|number|(base 10)
 * @riinputvi: Represents|the|input
 * @rifdvi: |Represents|the|filedescriptor|to|write|to
 *
 * Return:|number|of|characters|printed
 */

int print_d(int riinputvi, int rifdvi)
{
	int (*__putchar)(char) = _putchar;
	int riivi, ricountvi = 0;
	unsigned int _riabsvi_, ricurrentvi;

	if (rifdvi == STDERR_FILENO)
		__putchar = _eputchar;
	if (riinputvi < 0)
	{
		_riabsvi_ = -riinputvi;
		__putchar('-');
		ricountvi++;
	}
	else
		_riabsvi_ = riinputvi;
	ricurrentvi = _riabsvi_;
	for (riivi = 1000000000; riivi > 1; riivi /= 10)
	{
		if (_riabsvi_ / riivi)
		{
			__putchar('0' + ricurrentvi / riivi);
			ricountvi++;
		}
		ricurrentvi %= riivi;
	}
	__putchar('0' + ricurrentvi);
	ricountvi++;

	return (ricountvi);
}

/**
 * convert_number - |a|clone|of|itoa|converter|function
 * @rinumvi: Represnets|number
 * @ribasevi: Represents|base
 * @riflagsvi: Represents|argument|flags
 *
 * Return:|string
 */

char *convert_number(long int rinumvi, int ribasevi, int riflagsvi)
{
	static char *riarrayvi;
	static char ribuffervi[50];
	char risignvi = 0;
	char *riptrvi;
	unsigned long rinvi = rinumvi;

	if (!(riflagsvi & RICONVERT_UNSIGNEDVI) && rinumvi < 0)
	{
		rinvi = -rinumvi;
		risignvi = '-';

	}
	riarrayvi = riflagsvi & RICONVERT_LOWERCASEVI ?
		"0123456789abcdef" : "0123456789ABCDEF";
	riptrvi = &ribuffervi[49];
	*riptrvi = '\0';

	do	{
		*--riptrvi = riarrayvi[rinvi % ribasevi];
		rinvi /= ribasevi;
	} while (rinvi != 0);

	if (risignvi)
		*--riptrvi = risignvi;
	return (riptrvi);
}

/**
 * remove_comments -|function|that|replaces|first|instance|of|'#'|with|'\0'
 * @ribufvi: RepResnents|the|address|of|the|string|to|modify
 *
 * Return:|always||when|successful;
 */

void remove_comments(char *ribufvi)
{
	int riivi;

	for (riivi = 0; ribufvi[riivi] != '\0'; riivi++)
		if (ribufvi[riivi] == '#' && (!riivi || ribufvi[riivi - 1] == ' '))
		{
			ribufvi[riivi] = '\0';
			break;
		}
}
