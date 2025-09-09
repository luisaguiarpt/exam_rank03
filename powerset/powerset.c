#include <stdlib.h>
#include <stdio.h>

int	get_sum(int *s, int *mask, int size);
void	powerset(int n, int *s, int i, int *mask, int size);
void	print_subset(int size, int *s, int *mask);

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	int n = atoi(av[1]);
	int	size = ac - 2;
	int *s = calloc(sizeof(int), size);
	if (!s)
		return (1);
	int i = 2;
	while (i < ac)
	{
		s[i - 2] = atoi(av[i]);
		i++;
	}
	int	*mask = calloc(sizeof(int), size);
	if (!mask)
	{
		free(s);
		return (1);
	}
	powerset(n, s, 0, mask, size);
}

void	powerset(int n, int *s, int i, int *mask, int size)
{
	int	sum = get_sum(s, mask, size);
	if (sum == n)
		print_subset(size, s, mask);
	while (i < size)
	{
		mask[i] = 1;
		powerset(n, s, i + 1, mask, size);
		mask[i] = 0;
		i++;
	}
}

int	get_sum(int *s, int *mask, int size)
{
	int	sum = 0;
	int i = 0;

	while (i < size)
	{
		sum += mask[i] * s[i];
		i++;
	}
	return (sum);
}

void	print_subset(int size, int *s, int *mask)
{
	int i = 0;
	int first = 1;

	while (i < size)
	{
		if (mask[i] && first)
		{
			printf("%i", s[i]);
			first = 0;
		}
		else if (mask[i])
		{
			printf(" %i", s[i]);
		}
		i++;
	}
	printf("\n");
}
