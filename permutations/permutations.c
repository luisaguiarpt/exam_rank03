#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	swap(char *a, char *b)
{
	char	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort(char *str)
{
	int	i = 0;
	int flag = 1;

	while (flag)
	{
		flag = 0;
		i = 0;
		while (str[i + 1])
		{
			if (str[i] > str[i + 1])
			{
				swap(&str[i], &str[i + 1]);
				flag = 1;
			}
			i++;
		}
	}
}

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return i;
}

void	reverse(char *str)
{
	int	len = ft_strlen(str);
	int i = -1;
	while (++i < len / 2)
		swap(&str[i], &str[len - i - 1]);
}

int	permute(char *str, int len)
{
	int	p = len - 2;
	int	s = len - 1;

	while (str[p] > str[p + 1])
		p--;
	if (p < 0)
		return 0;
	while (str[s] < str[p])
		s--;
	swap(&str[p], &str[s]);
	reverse(&str[p + 1]);
	return 1;
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	char	*str = av[1];
	if (!str[0])
		return 0;
	int	size = ft_strlen(str);

	sort(str);
	printf("%s\n", str);
	while (permute(str, size))
		printf("%s\n", str);
}
