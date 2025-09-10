#include <stdio.h>

int	main(void)
{
	int a = 0;
	int b = 0;
	int c = 0;
	int ret = scanf("%d %d %d", &a, &b, &c);
	printf("a: %i | b: %i | c: %i \n", a, b, c);
	printf("Successful reads: %i\n", ret);
}
