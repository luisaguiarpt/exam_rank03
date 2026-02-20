#include <stdio.h>
#include <stdlib.h>

int	is_safe(int *board, int row, int col)
{
	int i = 0;
	while (i < col)
	{
		if (board[i] == row)
			return 0;
		if (board[i] - i == row - col || board[i] + i == row + col)
			return 0;
		i++;
	}
	return 1;
}

void	print(int *board, int size)
{
	int i = 0;

	while (i < size)
	{
		if (i)
			printf(" ");
		printf("%d", board[i]);
		i++;
	}
	printf("\n");
}

int	solve(int *board, int col, int size)
{
	if (col == size)
		print(board, size);
	for (int row = 0; row < size; row++)
	{
		board[col] = row;
		if (is_safe(board, row, col))
		{
			if (solve(board, col + 1, size))
				return (1);
		}
	}
	return 0;
}

int	main(int ac, char **av)
{
	if (ac != 2 || !av[1][0])
		return 1;

	int n = atoi(av[1]);

	int	*board = calloc(n, sizeof(int));
	if (!board)
		return 1;
	solve(board, 0, n);
	free(board);
}
