#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	sort(char *str)
{
	char	tmp;
	int		flag = 1;
	int		i = 0;
	int		swaps = 0;

	while (flag)
	{
		flag = 0;
		i = 0;
		while (str && str[i])
		{
			if (str[i] > str[i + 1] && str[i + 1] != 0)
			{
				tmp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = tmp;
				flag = 1;
				swaps++;
			}
			i++;
		}
	}
	return (swaps);
}

int	is_sorted(char *str)
{
	int	i = 0;
	while (str && str[i])
	{
		if (str[i] > str[i + 1] && str[i + 1] != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

void	swap(char *a, char *b)
{
	char	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	permute(char *str, int curr_i)
{
	if (curr_i == ft_strlen(str))
	{
		puts(str);
		return (1);
	}
	int	i = curr_i;
	while (i < ft_strlen(str))
	{
		swap(&str[i], &str[curr_i]);
		permute(str, curr_i + 1);
		swap(&str[i], &str[curr_i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	char	*str = av[1];
	sort(str);
	permute(str, 0);
}
