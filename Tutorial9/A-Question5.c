#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int nthreads = 1;
    if(argc==2){
    	nthreads = (argv[1][0]-'0');
    }
	int n = 100000000;
	long double dx = 1/(((long double) n)+1);
	long double x = 0;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    #pragma omp parallel for private(x)
    for(int i=0; i<n; i++){
    	x = i*dx;
    	long double y = exp(x)*cos(x)*sin(x)*sqrt(5*x+6.0);
    	if(i%1000000==0 && i!=0){
        	#pragma omp critical
        	{
         	 #ifdef _OPENMP
        		FILE *fp = fopen("calculations.txt","a");

        		fprintf(fp, "%d %1.15Lf %1.15Lf\n", i, x, y);

        		fclose(fp);
          	 #endif
        	}
        }
    }
    return 0;
}