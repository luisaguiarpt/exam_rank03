#include <stdio.h>
#include <stdlib.h>

int	is_valid(int *cols, int *diag1, int *diag2, int r, int c, int n);

void	print_board(int *pos, int n)
{
	int i = 0;
	while (i < n - 1)
		fprintf(stdout, "%d ", pos[i++]);
	fprintf(stdout, "%d\n", pos[i]);
}

void	solve(int *cols, int *diag1, int *diag2, int *pos, int col, int row, int n)
{
	if (row == n)
		print_board(pos, n);
	while (col < n)
	{
		int d1 = col + row;
		int d2 = row - col + n - 1;
		if (is_valid(cols, diag1, diag2, row, col, n))
		{
			cols[col] = diag1[d1] = diag2[d2] = 1;
			pos[row] = col;
			solve(cols, diag1, diag2, pos, 0, row + 1, n);
			cols[col] = diag1[d1] = diag2[d2] = 0;
		}
		col++;
	}
}

int	is_valid(int *cols, int *diag1, int *diag2, int r, int c, int n)
{
	int	d1 = c + r;
	int	d2 = r - c + n - 1;
	if (diag1[d1] || diag2[d2] || cols[c])
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int	n = atoi(av[1]);
	if (n == 1)
	{
		fprintf(stdout, "0\n");
		return (0);
	}
	if (n < 4)
		return (0);

	int	*cols = calloc(sizeof(int), n);
	if (!cols)
		return (1);
	int	*diag1 = calloc(sizeof(int), 2 * n - 1);
	if (!diag1)
		return (1);
	int	*diag2 = calloc(sizeof(int), 2 * n - 1);
	if (!diag2)
		return (1);
	int	*pos = calloc(sizeof(int), n);
	if (!pos)
		return (1);
	solve(cols, diag1, diag2, pos, 0, 0, n);
}

