#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int thread_num, nthreads = 16;

    //The statements in this ifdef will only be executed if the compiler supports OpenMP
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    printf("Testing OpenMP, you should see each thread print...\n");
    //This pragma statement parallizes the statements inside this block.
    #pragma omp parallel
    {
        //This pragma statement states that the code inside this block is a critical section.
        #pragma omp critical
        {
          #ifdef _OPENMP
          thread_num = omp_get_thread_num();
          printf("This thread = %d\n", thread_num);
          #endif
        }
    }
    return 0;
}
