#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8192
#endif

void	replace(char *str, size_t size, char *pattern)
{
	size_t	pattern_len = strlen(pattern);
	size_t	i = 0;
	char	*match;

	while (i < size)
	{
		if ((match = memmem(str + i, pattern_len, pattern, pattern_len)))
		{
			for (size_t j = 0; j < pattern_len; j++)
				str[i + j] = '*';
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	size_t	accumulated = 0;

	if (ac != 2 || av[1][0] == 0)
		return 1;

	char	*pattern = av[1];
	size_t	pattern_len = strlen(pattern);

	while ((bytes_read = read(0, buffer + accumulated, sizeof(buffer) - accumulated)) > 0)
	{
		accumulated += bytes_read;
		if (accumulated < pattern_len)
			continue;
		replace(buffer, accumulated - pattern_len, pattern);
		write(1, buffer, accumulated - pattern_len);
		memmove(buffer, buffer + accumulated - pattern_len, accumulated - pattern_len);
		accumulated = pattern_len;
	}
	if (bytes_read < 0)
	{
		perror("Error");
		return 1;
	}
	if (accumulated > 0)
	{
		replace(buffer, accumulated, pattern);
		write(1, buffer, accumulated);
	}
	return 0;
}

