#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

int	ft_match(char *str, char *substr);
void	write_ast(int len);
void	ft_filter(char *line, char *sub);

int	main(int ac, char **av)
{
	char	*line;
	int		r = 1;
	int		i = 0;
	int		total_len;

	if (ac != 2)
		return (1);
	if (av[1][0] == 0)
		return (1);
	
	line = malloc(sizeof(char));
	if (!line)
	{
		perror("Error");
		return (1);
	}
	line[i] = 0;
	total_len = BUFFER_SIZE + 1;
	while (r > 0)
	{
		line = realloc(line, total_len);
		if (!line)
		{
			perror("Error");
			return (1);
		}
		r = read(0, &line[i], BUFFER_SIZE);
		if (r < 0)
		{
			perror("Error");
			return (1);
		}
		total_len += BUFFER_SIZE;
		i += r;
	}
	line[i] = 0;
	ft_filter(line, av[1]);
	free(line);
	return (0);
}

void	ft_filter(char *line, char *sub)
{
	int	i = 0;
	int	len = strlen(sub);

	while (line[i])
	{
		if (ft_match(&line[i], sub))
		{
			write_ast(len);
			i += len;
		}
		else
		{
			write(1, &line[i], 1);
			i++;
		}
	}
}

void	write_ast(int len)
{
	int i = 0;

	while (i < len)
	{
		write(1, "*", 1);
		i++;
	}
}

int	ft_match(char *str, char *substr)
{
	int	i;

	i = 0;
	while (str[i] == substr[i] && str[i])
	{
		if (substr[i + 1] == 0) 
			return (1);
		i++;
	}
	return (0);
}
