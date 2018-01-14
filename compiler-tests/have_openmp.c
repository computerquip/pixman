#include <stdio.h>

extern unsigned int lcg_seed;
#pragma omp threadprivate(lcg_seed)
unsigned int lcg_seed;

unsigned function(unsigned a, unsigned b)
{
	lcg_seed ^= b;
	return ((a + b) ^ a ) + lcg_seed;
}

int main(int argc, char **argv)
{
	int i;
	int n1 = 0, n2 = argc;
	unsigned checksum = 0;
	int verbose = argv != NULL;
	unsigned (*test_function)(unsigned, unsigned);
	test_function = function;
	
	#pragma omp parallel for reduction(+:checksum) default(none) \
					shared(n1, n2, test_function, verbose)
					
	for (i = n1; i < n2; i++)
	{
		unsigned crc = test_function (i, 0);
		if (verbose)
			printf ("%d: %08X\n", i, crc);
		checksum += crc;
	}
	
	printf("%u\n", checksum);
	return 0;
}