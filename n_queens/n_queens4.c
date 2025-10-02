#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	is_valid(int *diag1, int *diag2, int *cols, int r, int c, int n)
{
	int d1 = r + c;
	int	d2 = r - c + n - 1;
	if (diag1[d1] || diag2[d2] || cols[c])
		return (0);
	return (1);
}

void	print_sol(int *pos, int n)
{
	int	i = 0;
	char	ch;

	while (i < n - 1)
	{
		ch = pos[i] + '0';
		write(1, &ch, 1);
		write(1, " ", 1);
		i++;
	}
	ch = pos[i] + '0';
	write(1, &ch, 1);
	write(1, "\n", 1);
}

void	solve(int *diag1, int *diag2, int *cols, int *pos, int r, int c, int n)
{
	if (c == n && is_valid(diag1, diag2, col, r, c, n))
	{
		print_sol(pos, n);
		return ;
	}
	int	i = c;
	while (i < n)
	{
		solve(diag1, diag2, cols, pos, r + 1, c, n);
		solve(diag1, diag2, cols, pos, r + 1, c, n);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (av[1] == 0)
		return (1);
	int	n = atoi(av[1]);
	int	*diag1 = calloc(sizeof(int), 2 * n - 1);
	if (!diag1)
		return (1);
	int	*diag2 = calloc(sizeof(int), 2 * n - 1);
	if (!diag2)
		return (1);
	int	*cols = calloc(sizeof(int), n);
	if (!cols)
		return (1);
	int	*pos = calloc(sizeof(int), n);
	if (!pos )
		return (1);
	solve(diag1, diag2, cols, pos, 0, 0, n);
}
