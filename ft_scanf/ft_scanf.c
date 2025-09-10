#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF && isspace(c))
		;
	if (c == EOF)
		;
	else
		ungetc(c, f);
    return (c);
}

int match_char(FILE *f, char c)
{
	int	ch;

	while ((ch = fgetc(f)) != EOF && c == ch)
		;
	if (ch == EOF)
		;
	else
		ungetc(ch, f);
    return (ch);
}

int scan_char(FILE *f, va_list ap)
{
	char	ch = (char)va_arg(ap, int);
    return (0);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
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

#include <stdio.h>

int	main(void)
{
	printf("Enter a character: ");
	int		d;
	char	c;
	char	*s;
	ft_scanf("%d%c%s", &d, &c, s);
	printf("d: %d\nc: %c\ns: %s\n", d, c, s);
}
