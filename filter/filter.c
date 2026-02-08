#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define BUFFER_SIZE 8192 

int	main(int ac, char **av)
{
	char	buffer[BUFFER_SIZE];
	char	*ptr_match;
	char	*ptr_buffer;
	ssize_t	chunk;
	size_t	pattern_len;
	size_t	i;
	size_t	res_len = 0;
	char	*pattern;

	if (ac != 2 || !av[1] || !av[1][0])
		return (1);

	pattern = av[1];
	pattern_len = strlen(pattern);
	
	while ((chunk = read(0, buffer + res_len, sizeof(buffer) - res_len)) > 0)
	{
		res_len += chunk;
		ptr_buffer = buffer;

		while ((ptr_match = memmem(ptr_buffer, res_len - (ptr_buffer - buffer), pattern, pattern_len)))
		{
			write(1, ptr_buffer, ptr_match - ptr_buffer);

			i = 0;
			while (i++ < pattern_len)
				write(1, "*", 1);
			
			ptr_buffer = ptr_match + pattern_len;
		}
		res_len -= (ptr_buffer - buffer);

		memmove(buffer, ptr_buffer, res_len);
	}
	if (chunk < 0)
	{
		perror("Error");
		return (1);
	}
	write(1, buffer, res_len);
	return (0);
}
