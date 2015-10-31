#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_LEN 256
#define NUM_AMOUNT 5

int total_sum = 0;
sem_t sem;

void save_numbers(char filename[]);
void *factorial(void *arg);
void factorial2(int fact);

int main(void)
{
  //master process
  char filename[] = "numbers.txt";
  save_numbers(filename); //load filename with user numbers

  //create a fork
  pid_t pid = fork();
  if(pid ==0){
    //child process
    printf("child process:\n");//read the numbers from the file

    int line = 0; //holds the current value read from file
    FILE *numbers_file = fopen(filename,"r");
    if(numbers_file == NULL){
      printf("Error opening file\n");
      exit(1);
    }
    int numbers_array[NUM_AMOUNT] = {0}; //holds the numbers read from the file
    pthread_t workers[NUM_AMOUNT]; //holds all the threads started
    //iterate thorugh the file and start a thread factorial for each read number
    for (int i = 0; i < NUM_AMOUNT; i++){
      fscanf(numbers_file, "%d",&numbers_array[i]);//read value in
      //      printf("temp:%d\n",numbers_array[i]);
      //      factorial2(line);
      sem_init(&sem,0,1); //initialize the semaphore
      pthread_create(&workers[i],0,factorial, (void *) numbers_array[i]);      
    }

    //join all the threads -> wait for all threads to finish
    for (int i  = 0; i < NUM_AMOUNT; i++){
      pthread_join(workers[i],0);
    }
    sem_destroy(&sem); //destroy the semaphore
    fclose(numbers_file);//close the open number file

    //total_sum contains the cumulated sum of all the factorials from the threads
    FILE *sum_file = fopen("sum.txt","w");
    if(sum_file == NULL){
      printf("Error opening file\n");
      exit(1);
    }
    fprintf(sum_file,"%d",total_sum);
    fclose(sum_file);//close the file
    
    exit(0);
  }else if(pid > 0){
    //parent process
    wait(NULL);//wait for child to finish
    printf("parent process:\n");
    FILE *sum_file = fopen("sum.txt","r"); //open the sum file for reading
    if(sum_file == NULL){
      printf("Error opening file\n");
      exit(1);
    }
    int get_total_sum = 0;
    fscanf(sum_file, "%d", &get_total_sum);
    printf("[Parent] The total Sum is: %d\n",get_total_sum);
    fclose(sum_file);//close the file
  }else{
    printf("Forking failed with pid %d\n",pid);
  }
  
  return 0;  
}

void save_numbers(char filename[]){
  //reads in 5 numbers from the user and saves them to filename
  char buffer[BUFFER_LEN] = {0};

  //delete any previous data in filename by open for writing and closing
  FILE *numbers_file = fopen(filename,"w");
  fclose(numbers_file);

  //open the file for append
  numbers_file = fopen(filename,"a");
  if(numbers_file == NULL){
    printf("Error opening file\n");
    exit(1);
  }
  //FILE *numbers_file = fopen(filename,"a");
  
  printf("Enter Five numbers (<input> followed by enter)\n");
  for (int i = 0; i < NUM_AMOUNT; i++){
    printf("[%d]>>",i+1);
    fgets(buffer,BUFFER_LEN,stdin);
    //    buffer[strlen(buffer)-1] = 0;                      //remove the newline from last char
    fprintf(numbers_file,"%s",buffer);
  }
  printf("Saved to file \"%s\"\n",filename);
  fclose(numbers_file);
}

void factorial2(int fact){
  //calculate the factorial of fact
  int result_fact = 1;
  for (int i = 0; i < fact; i++){
    result_fact *= (fact - i);
  }
  printf("factorial is %d:\n",result_fact);
}

void *factorial(void *arg){
  //calculate the factorial of fact
  int fact = (int *)arg;
  int result_fact = 1;  
  for (int i = 0; i < fact; i++){
    result_fact *= (fact - i);
  }
  //Enter the Critical Section
  sem_wait(&sem);
  total_sum+=result_fact;
  printf("[Thread] factorial of \"%d\" is \"%d\" ",fact,result_fact);
  printf("and total Sum is \"%d\"\n",total_sum);
  sem_post(&sem);
}
























