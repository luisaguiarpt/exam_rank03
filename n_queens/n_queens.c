#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	place_queen(int *columns, int *diag1, int *diag2, int *p, int row, int col, int n);
int	is_valid(int *columns, int *diag1, int *diag2, int row, int col, int n);

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
	else if (n < 4)
		return (0);
	int *columns = calloc(sizeof(int), n);
	if (!columns)
		return (1);
	int	*diag1 = calloc(sizeof(int), (2 * n - 1));
	if (!diag1)
		return (1);
	int	*diag2 = calloc(sizeof(int), (2 * n - 1));
	if (!diag2)
		return (1);
	int	*p = calloc(sizeof(int), n);
	if (!p)
		return (1);
	place_queen(columns, diag1, diag2, p, 0, 0, n);
	free(columns);
	free(diag1);
	free(diag2);
	free(p);
}

void	place_queen(int *columns, int *diag1, int *diag2, int *p, int row, int col, int n)
{
	if (row == n)
	{
		int i = 0;
		while (i < n - 1)
			fprintf(stdout, "%i ", p[i++]);
		fprintf(stdout, "%i\n", p[i]);
		return ;
	}
	int	d1, d2;
	while (col < n)
	{
		d1 = row + col;
		d2 = row - col + n - 1;
		if (is_valid(columns, diag1, diag2, row, col, n))
		{
			columns[col] = diag1[d1] = diag2[d2] = 1;
			p[row] = col;
			place_queen(columns, diag1, diag2, p, row + 1, 0, n);
			columns[col] = diag1[d1] = diag2[d2] = 0;
		}
		col++;
	}
}

int	is_valid(int *columns, int *diag1, int *diag2, int row, int col, int n)
{
	int d1 = row + col;
	int d2 = row - col + n - 1;

	if (diag1[d1] || diag2[d2] || columns[col])
		return (0);
	return (1);
}
