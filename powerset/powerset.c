#include <stdlib.h>
#include <stdio.h>

int	calc_total(int size, int *set, int *mask)
{
	int	tot = 0;

	for (int i = 0; i < size; i++)
		tot += mask[i] * set[i];
	return (tot);
}

void	print_sub(int size, int *set, int *mask)
{
	int	flag = 0;
	for (int i = 0; i < size; i++)
	{
		if (mask[i])
		{
			if (flag)
				printf(" ");
			printf("%d", set[i]);
			flag = 1;
		}
	}
	printf("\n");
}

void	powerset(int curr_i, int n, int size, int *set, int *mask)
{
	if (calc_total(size, set, mask) == n)
		print_sub(size, set, mask);
	for (int i = curr_i; i < size; i++)
	{
		mask[i] = 1;
		powerset(i + 1, n, size, set, mask);
		mask[i] = 0;
	}
}

int	main(int ac, char **av)
{
	if (ac < 3)
		return (1);

	int	n = atoi(av[1]);

	int	size = ac - 2;

	int	*set = calloc(1, sizeof(int) * size);
	if (!set)
		return (1);

	for (int i = 0; i < size; i++)
		set[i] = atoi(av[2 + i]);
	int	*mask = calloc(1, sizeof(int) * size);
	if (!mask)
	{
		free(set);
		return (1);
	}

	powerset(0, n, size, set, mask);
	free(set);
	free(mask);
}
