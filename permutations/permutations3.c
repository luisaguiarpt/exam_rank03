#include <unistd.h>
#include <stdio.h>


void	sortstr(char *str);
void	gen_perm(char *str, int curr_i, int len);
int	ft_strlen(char *str);
void	swap(char *a, char *b);


int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (av[1] == 0)
		return (0);
	sortstr(av[1]);
	char *str = av[1];
	gen_perm(str, 0, ft_strlen(str) - 1);
}

void	gen_perm(char *str, int curr_i, int len)
{
	if (curr_i == len)
	{
		puts(str);
		return;
	}
	int	i = curr_i;
	while (i <= len)
	{
		swap(&str[i], &str[curr_i]);
		gen_perm(str, curr_i + 1, len);
		swap(&str[i], &str[curr_i]);
		i++;
	}
}

void	sortstr(char *str)
{
	int	i = 1;
	int	flag = 1;

	while (flag)
	{
		flag = 0;
		while (str[i])
		{
			if (str[i - 1] > str[i])
			{
				swap(&str[i], &str[i - 1]);
				flag = 1;
			}
			i++;
		}
	}
}

void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}
