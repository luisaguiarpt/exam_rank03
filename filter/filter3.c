#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50 
#endif

char	*get_input(void);
int	is_match(char *needle, size_t needle_len, char *hay, size_t hay_len);

int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	char	*filter= av[1];
	if (av[1] == 0)
		return (0);
	char	*str = get_input();
	if (!str)
	{
		perror("Error");
		return (1);
	}
	size_t	filter_len = strlen(filter);
	size_t	i = 0;
	size_t	j = 0;
	while (str[i])
	{
		if (is_match(filter, filter_len, &str[i], filter_len))
		{
			j = 0;
			while (j < filter_len)
			{
				write(1, "*", 1);
				j++;
			}
			i += j;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

char	*get_input(void)
{
	ssize_t	r = 1;

	char	*buf = NULL;
	size_t	tot_len = BUFFER_SIZE + 1;
	size_t	read_len = 0;
	while (r > 0)
	{
		buf = realloc(buf, tot_len);
		if (!buf)
			return (NULL);
		r = read(0, &buf[read_len], BUFFER_SIZE);
		if (r < 0)
			return (NULL);
		if (r == 0)
			break;
		read_len += r;
		buf[read_len] = 0;
		tot_len += BUFFER_SIZE;
	}
	return (buf);
}

int	is_match(char *needle, size_t needle_len, char *hay, size_t hay_len)
{
	if (memmem(hay, hay_len, needle, needle_len) != 0)
		return (1);
	return (0);
}
