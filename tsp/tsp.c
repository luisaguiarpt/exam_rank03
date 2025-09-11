#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <float.h>

// compute the distance between two points
float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

float	total_dist(float (*array)[2], int *route, ssize_t size)
{
	float	total = 0;
	int	i = 0;

	while (i < size - 1)
	{
		total += distance(array[route[i]], array[route[i + 1]]);
		i++;
	}
	total += distance(array[route[0]], array[route[i]]);
	return (total);
}
void	solve(float (*coords)[2], int *route, ssize_t curr_i, ssize_t size, float *best_dist);

float tsp(float (*coords)[2], ssize_t size)
{
	if (size < 2)
		return (0);
    float best_distance;
	int	*route= calloc(sizeof(int), size);
	if (!route)
		return (-1);

	for (int i = 0; i < size; i++)
		route[i] = i;

	best_distance = total_dist(coords, route, size);
	solve(coords, route, 1, size, &best_distance);
    return (best_distance);
}

void	solve(float (*coords)[2], int *route, ssize_t curr_i, ssize_t size, float *best_dist)
{
	float	dist;
	int	i;
	int	temp;

	if (curr_i == size)
	{
		dist = total_dist(coords, route, size);
		if (dist < *best_dist)
			*best_dist = dist;
		return ;
	}
	i = curr_i;
	while (i < size)
	{
		temp = route[curr_i];
		route[curr_i] = route[i];
		route[i] = temp;
		solve(coords, route, curr_i + 1, size, best_dist);
		route[i] = route[curr_i];
		route[curr_i] = temp;
		i++;
	}
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
		fclose(file);
    printf("%.2f\n", tsp(array, size));
    free(array);
    return (0);
}
