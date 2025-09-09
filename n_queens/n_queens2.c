#include <stdio.h>
#include <stdlib.h>

void	place_queen(int *col, int *diag1, int *diag2, int *pos, int row, int c, int n);
int	is_valid(int *col, int *diag1, int *diag2, int row, int c, int n);

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int n = atoi(av[1]);
	if (n == 1)
	{
		fprintf(stdout, "0\n");
		return (0);
	}
	if (n < 4)
		return (0);
	int	*col = calloc(sizeof(int), n);
	if (!col)
		return (1);
	int *diag1 = calloc(sizeof(int), 2 * n - 1);
	if (!diag1)
	{
		free(col);
		return (1);
	}
	int *diag2 = calloc(sizeof(int), 2 * n - 1);
	if (!diag2)
	{
		free(col);
		free(diag1);
		return (1);
	}
	int	*pos = calloc(sizeof(int), n);
	if (!pos)
	{
		free(col);
		free(diag1);
		free(diag2);
		return (1);
	}
	place_queen(col, diag1, diag2, pos, 0, 0, n);
	free(col);
	free(diag1);
	free(diag2);
	free(pos);
}

void	place_queen(int *col, int *diag1, int *diag2, int *pos, int row, int c, int n)
{
	if (row == n)
	{
		int i = 0;
		while (i < n - 1)
			fprintf(stdout, "%i ", pos[i++]);
		fprintf(stdout, "%i\n", pos[i]);
		return ;
	}
	while (c < n)
	{
		int d1 = row + c;
		int	d2 = row - c + n - 1;
		if (is_valid(col, diag1, diag2, row, c, n))
		{
			diag1[d1] = diag2[d2] = col[c] = 1;
			pos[row] = c;
			place_queen(col, diag1, diag2, pos, row + 1, 0, n);
			diag1[d1] = diag2[d2] = col[c] = 0;
		}
		c++;
	}
}

int	is_valid(int *col, int *diag1, int *diag2, int row, int c, int n)
{
	int d1 = row + c;
	int	d2 = row - c + n - 1;
	if (col[c] || diag1[d1] || diag2[d2])
		return (0);
	return (1);
}
