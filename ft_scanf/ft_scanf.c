#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			return (1);
		}
	}
    return (-1);
}

int match_char(FILE *f, char expected)
{
	int	c = fgetc(f);

	if (c == EOF)
		return (-1);
	if (c == expected)
		return (1);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int	c = fgetc(f);
	char	*ptr = va_arg(ap, char *);

	if (c == EOF)
		return (-1);
	
	*ptr = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	sign = 1;
	int num = 0;
	int	c = fgetc(f);
	int	digits = 0;

	if (c == '-')
		sign = -1;
	else if (c == '+')
		sign = 1;
	else
		ungetc(c, f);

	while ((c = fgetc(f)) != EOF)
	{
		if (isdigit(c))
		{
			num = num * 10 + (c - '0');
			digits++;
		}
		else
		{
			ungetc(c, f);
			break;
		}
	}
	if (digits == 0)
	{
		if (c == EOF)
			return (-1);
		else
			return (0);
	}
	int	*ptr = va_arg(ap, int *);
	*ptr = sign * num;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*ptr = va_arg(ap, char *);
	int	i = 0;
	int	c;

	while ((c = fgetc(f)) != EOF && !isspace(c))
	{
		ptr[i] = c;
		i++;
	}
	ptr[i] = 0;
	if (c == EOF && i == 0)
		return (-1);
	if (c != EOF)
		ungetc(c, f);
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

/*
int	main(void)
{
	int	x = 0;
	char	c = 0;
	char	str[20];

	printf("%%d%%c%%s\n");
	ft_scanf("%d%c%s", &x, &c, str);
	printf("Nr: %d | Char: %c | Str: %s\n", x, c, str);
}
*/
