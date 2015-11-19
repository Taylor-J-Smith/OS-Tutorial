#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int nthreads = argc;
	int n = 100;//000000;
	double dx = 1/(n+1);
	double x = 0;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    #pragma omp parallel for private(x)
    for(int i=0; i<n; i++){
    	x = i*dx;
    	double y = exp(x)*cos(x)*sin(x)*sqrt(5*x+6.0);
    	if(1){
        	#pragma omp critical
        	{
         	 #ifdef _OPENMP
        		FILE *fp = fopen("calculations.txt","w");

        		fprintf(fp, "%d %5.7f %5.7f", i, x, y);

        		fclose(fp);
          	#endif
        	}
        }
    }
    return 0;
}