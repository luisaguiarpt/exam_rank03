#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

char	*read_input(void);
int	is_match(char *str, char *sub);

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (av[1] == 0)
		return (1);
	char *filter = av[1];
	char	*str = read_input();
	int i = 0;
	while (str[i])
	{
		if (is_match(&str[i], filter))
		{
			size_t j = -1;
			while (++j < strlen(filter))
				write(1, "*", 1);
			i += j;
		}
		else
			write(1, &str[i++], 1);
	}
}

char	*read_input(void)
{
	int	r = 1;
	char *buf = NULL;
	buf = realloc(buf, BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	size_t	tot_len = 0;
	while (r > 0)
	{
		r = read(0, &buf[tot_len], BUFFER_SIZE);
		if (r < 0)
			return (NULL);
		if (r == 0)
			break;
		tot_len += r;
		buf[tot_len] = 0;
		buf = realloc(buf, tot_len + BUFFER_SIZE + 1);
	}
	return (buf);
}

int	is_match(char *str, char *sub)
{
	int	i = 0;

	while (str[i] && sub[i])
	{
		if (str[i] == sub[i])
		{
			i++;
			if (sub[i] == 0)
				return (1);
		}
		else
			return (0);
	}
	return (1);
}
