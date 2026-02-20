/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 * 
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	if (!str || !str[0])
		return (NULL);

	char	*line = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!line)
		return (NULL);
	int	i = 0;
	while (str[i])
	{
		line[i] = str[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	bytes_read;
	static int	b_pos;
	char		line[70000];
	int			i = 0;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (b_pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			b_pos = 0;
			if (bytes_read <= 0)
				break ;
		}
		line[i++] = buffer[b_pos++];
		if (buffer[b_pos - 1] == '\n')
			break ;
	}
	line[i] = 0;
	if (i == 0 || bytes_read < 0)
		return (NULL);
	return (ft_strdup(line));
}
/*
#include <stdio.h>

int	main(void)
{
	char	*line;
	while ((line = get_next_line(0)))
	{
		printf("%s", line);
		free(line);
	}
}
*/
