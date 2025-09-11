#include <stdio.h>
#include <unistd.h>

void	solve(char *str, int current_index, int total_to_remove, int already_removed);
int	min_to_remove(char *str);
int	ft_strlen(char *s);

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	char	*str = av[1];
	if (!min_to_remove(str))
	{
		puts(str);
		return (0);
	}
	solve(str, 0, min_to_remove(str), 0);
}

void	solve(char *str, int current_index, int total_to_remove, int already_removed)
{
	if (current_index == ft_strlen(str))
	{
		if (already_removed == total_to_remove && !min_to_remove(str))
			puts(str);
		return ;
	}
	if (already_removed > total_to_remove)
		return ;
	char	temp = str[current_index];
	str[current_index] = ' ';
	solve(str, current_index + 1, total_to_remove, already_removed + 1);
	str[current_index] = temp;
	solve(str, current_index + 1, total_to_remove, already_removed);
}

int	min_to_remove(char *str)
{
	int	open = 0, close = 0;
	int	i = 0;
	
	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

int	ft_strlen(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return (i);
}
