#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_LEN 256

int main(void)
{
  pid_t child1;
  pid_t child2;

  child1 = fork();

  if (child1 == 0){
    //child 1
    sleep(1);
    FILE *child1_file = fopen("child1.txt","r");//open the file for read
    if(child1_file == NULL){
      printf("Error opening file\n");
      exit(1);
    }
    char buffer[BUFFER_LEN] = {0};
    fgets(buffer, BUFFER_LEN, child1_file);
    printf("[child1] %s\n",buffer);
    fclose(child1_file);//close the file
    exit(0);
  }else{
    child2 = fork();
    if (child2 ==0){
      //child 2
      sleep(1);
      FILE *child2_file = fopen("child2.txt","r");//open the file for read
      if(child2_file == NULL){
	printf("Error opening file\n");
	exit(1);
      }
      char buffer[BUFFER_LEN] = {0};
      fgets(buffer, BUFFER_LEN, child2_file);
      printf("[child2] %s\n",buffer);
      fclose(child2_file);//close the file
      exit(0);
    }else{
      //parent process
      FILE *child1_file = fopen("child1.txt","w");
      FILE *child2_file = fopen("child2.txt","w");
      if(child1_file == NULL || child2_file == NULL){
	printf("Error opening file\n");
	exit(1);
      }
      fprintf(child1_file,"child1");
      fprintf(child2_file,"child2");
      
      fclose(child1_file);
      fclose(child2_file);
      wait(NULL);
    }
  }
  
  return 0;
}
