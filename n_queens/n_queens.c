#include <stdio.h>
#include <stdlib.h>

int	is_safe(int row, int col, int *board);
void	print_board(int *board, int n);
int	solve(int n, int row, int *board);

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	int	n;
	int	board[10];

	n = atoi(av[1]);
	for (int i = 0; i < n; i++)
		board[i] = 0;
	solve(n, 0, board);
}

void	print_board(int *board, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", board[i]);
		if (i != n)
			printf(" ");
	}
	printf("\n");
}

int	solve(int n, int row, int *board)
{
	if (row == n)
		print_board(board, n);
	for (int col = 0; col < n; col++)
	{
		if (is_safe(row, col, board))
		{
			board[row] = col;
			if (solve(n, row + 1, board))
				return (1);
		}
	}
	return (0);
}

int	is_safe(int row, int col, int *board)
{
	int	i = 0;

	while (i < row)
	{
		if (board[i] == col)
			return (0);
		if (board[i] - i == col - row || board[i] + i == col + row)
			return (0);
		i++;
	}
	return (1);
}
