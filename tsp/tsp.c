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

float	best_dist = FLT_MAX;
float	tmp_dist;

float	calc_dist(float (*cities)[2], ssize_t size)
{
	float dist = 0;
	for (ssize_t i = 0; i < size - 1; i++)
		dist += distance(cities[i], cities[i + 1]);
	dist += distance(cities[size - 1], cities[0]);
	return dist;
}

void	swap(float city1[2], float city2[2])
{
	float	tmp[2];

	tmp[0] = city1[0];
	tmp[1] = city1[1];
	city1[0] = city2[0];
	city1[1] = city2[1];
	city2[1] = tmp[1];
	city2[0] = tmp[0];
}

void	permute(float (*cities)[2], ssize_t start, ssize_t size)
{
	if (start == size)
	{
		tmp_dist = calc_dist(cities, size);
		if (tmp_dist < best_dist)
			best_dist = tmp_dist;
		return ;
	}
	
	for (ssize_t i = start; i < size; i++)
	{
		swap(cities[i], cities[start]);
		permute(cities, start + 1, size);
		swap(cities[i], cities[start]);
	}
}

float tsp(float (*cities)[2], ssize_t size)
{
	permute(cities, 0, size);
    return (best_dist);
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
