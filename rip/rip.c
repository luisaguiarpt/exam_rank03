#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	calc_min(char *str)
{
	int	open = 0;
	int close = 0;
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

void	rip(char *str, int min_to_remove, int already_removed, int curr_i)
{
	if (min_to_remove == already_removed && calc_min(str) == 0)
		puts(str);
	while (str[curr_i])
	{
		char	tmp = str[curr_i];
		str[curr_i] = ' ';
		rip(str, min_to_remove, already_removed + 1, curr_i + 1);
		str[curr_i] = tmp;
		curr_i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	char	*str = av[1];
	int	min_to_remove = calc_min(str);
	rip(str, min_to_remove, 0, 0);
}
