#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_AMOUNT 5
#define BUFFER_LEN 256

typedef struct{
  int num;
  int index;
}numIndex_Struct;

void *factorial(void *arg);

//define global variables
int moving_sum[] = {0,0,0,0,0};
sem_t sem;

int main(void)
{
  char buffer[BUFFER_LEN] = {0}; //holds the user entered values
  pthread_t workers[NUM_AMOUNT]; //create array of threads
  numIndex_Struct num_index_array[NUM_AMOUNT]; //create an array of structs
  sem_init(&sem,0,1); //init the semaphore
  
  //get 5 numbers from the user
  printf("Enter Five numbers (<input> followed by enter)\n");
  for (int i = 0; i < NUM_AMOUNT; i++){
    printf("[%d]>>",i+1);
    fgets(buffer,BUFFER_LEN,stdin); //get the number from the user
    buffer[strlen(buffer) -1] = 0;//remove the newline
    
    //create a struct to store in the struct array
    num_index_array[i].num = atoi(buffer); //store the number
    num_index_array[i].index = i;          //store the current index

  }
  //create a thread for each user entered number
  for (int i = 0; i < NUM_AMOUNT; i++){
    pthread_create(&workers[i], 0, factorial, (void *) &num_index_array[i]);        
  }
  //join all the threads and print contents of moving_sum
  for (int i = 0; i < NUM_AMOUNT; i++){
    pthread_join(workers[i],0);
  }

  //print the contents of moving_sum
  printf("moving_sum[]: ");
  for (int i = 0; i < NUM_AMOUNT; i++){
    printf("%d ",moving_sum[i]);
  }
  printf("\n");
  
  sem_destroy(&sem); //destroy the semaphore
  return 0;
}


void *factorial(void *arg){
  //calculate the factorial of fact
  numIndex_Struct* arg_struct = (numIndex_Struct*)arg;
  int fact = arg_struct->num;
  int index = arg_struct->index;
  int prev_index = index-1;
  int result_fact = 1;
  //calculate the factorial
  for (int i = 0; i < fact; i++){
    result_fact *= (fact - i);
  }
  
  //check if first value
  if(prev_index < 0){
    //Enter the Critical Section******************
    sem_wait(&sem);//take semaphore
    printf("[debug] WRITING \"%d\" TO moving_sum[%d]\n",result_fact,index);
    moving_sum[index] = result_fact;
    sem_post(&sem);//release semaphore
    //end of dCcritical section********************
  }else{
  
    //Enter the Critical Section******************  
    sem_wait(&sem);//take semaphore
    while (moving_sum[prev_index] == 0){
      //wait
      sem_post(&sem);//release semaphore
      sem_wait(&sem);//take semaphore
    }
    //exited while loop- there must be a value in previous index of moving sum
    //semaphore already taken from within while loop
    int prev_val = moving_sum[prev_index];
    printf("[debug] WRITING \"%d\" TO moving_sum[%d]\n",result_fact,index);
    moving_sum[index] = prev_val + result_fact;
    sem_post(&sem);//release semaphore
    //end of dCcritical section********************
  }
}





























