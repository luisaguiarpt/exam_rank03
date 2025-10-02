#include <stdio.h>

int	min_to_remove(char *str)
{
	int	open = 0;
	int	close = 0;
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')' && open > 0)
			open--;
		else if (str[i] == ')')
			close++;
		i++;
	}
	return (open + close);
}

void	rip(char *str, int i, int total_to_remove, int already_removed)
{
	if (min_to_remove(str) == 0)
	{
		puts(str);
		return;
	}
	if (already_removed > total_to_remove)
		return ;
	if (str[i] == '(' || str[i] == ')')
	{
		char	tmp = str[i];
		str[i] = ' ';
		rip(str, i + 1, total_to_remove, already_removed + 1);
		str[i] = tmp;
		rip(str, i + 1, total_to_remove, already_removed);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (av[1] == 0)
		return (0);
	char	*str = av[1];
	rip(str, 0, min_to_remove(str), 0);
}
