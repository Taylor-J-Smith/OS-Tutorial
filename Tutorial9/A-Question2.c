#include <stdio.h>
#include <math.h>
#include <omp.h>

int main (int argc, char *argv[])
{
	int nthreads;
	nthreads = atoi(argv[1]);
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    int n = 100000000;
    double y[100000000];
    double dx = 1/(n+1);
	double x;
    #pragma omp parallel for private(x)
	for (int i = 0; i < n; i++){
		x = i *dx;
		y[i] = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);
	}
}
