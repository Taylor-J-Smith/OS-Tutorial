#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define MATRIX_SIZE 1000

int main(void)
{
  int a[MATRIX_SIZE][MATRIX_SIZE];
  int b[MATRIX_SIZE][MATRIX_SIZE];
  int result[MATRIX_SIZE][MATRIX_SIZE];

  printf("Initializing matricies %d X %d...\n",MATRIX_SIZE,MATRIX_SIZE);
  //initialize the matricies
  for (int i = 0; i < MATRIX_SIZE; i++){
    for (int j = 0; j < MATRIX_SIZE; j++){
      a[i][j] = i + j;
      b[i][j] = i + j;
    }
  }

  printf("Multiplying matricies %d X %d...\n",MATRIX_SIZE,MATRIX_SIZE);
  int i, j, k;
  //multiply the matricies
  #pragma omp for private(i,j,k)
  for (i = 0; i < MATRIX_SIZE; i++){
    for (j = 0; j < MATRIX_SIZE; j++){
      int sum = 0;
      for (k = 0; k < MATRIX_SIZE; k++){
	sum += a[i][k] * b[k][j];
      }
      result[i][j] = sum;
    }
  }
    
    puts("---------------COMPLETE---------------");
  /* 
  //@ref http://www.appentra.com/parallel-matrix-matrix-multiplication/
  int i,j,k;
  #pragma omp parallel shared(a,b,result) private(i,j,k) 
    {
      //      #pragma omp for schedule(static)
      for (i=0; i<MATRIX_SIZE; i=i+1){
	for (j=0; j<MATRIX_SIZE; j=j+1){
	  result[i][j]=0.;
	  for (k=0; k<MATRIX_SIZE; k=k+1){
            result[i][j]=(result[i][j])+((a[i][k])*(b[k][j]));
	  }
	}
      }
    }*/

  //print the resulting matrix
    /*    
  for (int i = 0; i < MATRIX_SIZE; i++){
    for (int j = 0; j < MATRIX_SIZE; j++){
      printf("%d ",result[i][j]);
    }
    puts("");
  }
    */

}
