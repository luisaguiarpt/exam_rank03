#include <stdio.h>

char	*sortstr(char *str);
int		str_len(char *str);
void	gen_perm(char *str, int i, int len);
void	swap(char *a, char *b);

int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (av[1] == 0)
		return (0);
	char	*str = sortstr(av[1]);
	int		len = str_len(str);
	gen_perm(str, 0, len - 1);
}

void	gen_perm(char *str, int curr_i, int len)
{
	if (curr_i == len)
	{
		puts(str);
		return ;
	}
	int i = curr_i;
	while (i <= len)
	{
		swap(&str[i], &str[curr_i]);
		gen_perm(str, curr_i + 1, len);
		swap(&str[i], &str[curr_i]);
		i++;
	}
}

void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	*sortstr(char *str)
{
	int		len = str_len(str);
	int		i = 0;
	int		flag = 1;
	char	tmp;

	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < len - 1)
		{
			if (str[i] > str[i + 1])
			{
				tmp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = tmp;
				flag = 1;
			}
			i++;
		}
	}
	return (str);
}

int		str_len(char *str)
{
	size_t	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
