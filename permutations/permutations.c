#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str);
void	sort_string(char *str);
void	swap_char(char *a, char *b);

void	strcopy(char *dest, char *orig);
int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (av[1][0] == 0)
		return (1);
	if (av[1][1] == 0)
	{
		write(1, av[1], 1);
		return (0);
	}
	char	*str = malloc(sizeof(char) * (ft_strlen(av[1]) + 1));
	if (!str)
		return (1);
	strcopy(str, av[1]);
	sort_string(str);
	printf("%s\n", str);
}

void	next_permutation(char *str)
{
	int	i, j = 0;

	while (str[i] < str[i + 1])
}

void	strcopy(char *dest, char *orig)
{
	int i = 0;

	while (orig[i])
	{
		dest[i] = orig[i];
		i++;
	}
	dest[i] = 0;
}

void	sort_string(char *str)
{
	int	i = 0;
	int	flag = 1;

	while (str[i] && str[i + 1] && flag)
	{
		flag = 0;
		while (str[i] && str[i + 1])
		{
			if (str[i] > str[i + 1])
			{
				swap_char(&str[i], &str[i + 1]);
				flag = 1;
			}
			i++;
		}
		i = 0;
	}
}

void	swap_char(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}
