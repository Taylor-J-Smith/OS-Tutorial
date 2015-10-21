#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_LEN 256
#define NUM_STUDENTS 5

void *bellcurve(void *arg){
  double grade = atof(arg);
  grade = grade*1.5;
  
  printf("%.2f\n",grade);
  
  return NULL;
}

int main(int argc, char *argv[]) {
  char student_grades[NUM_STUDENTS][BUFFER_LEN];
  char buffer[BUFFER_LEN];
  pthread_t workers[NUM_STUDENTS];
  
  printf("Enter the grades for five students:\n");   

  for (int i = 0; i < NUM_STUDENTS; i++){
    printf("Student #%d:",i+1);
    fgets(buffer,BUFFER_LEN,stdin);
    buffer[strlen(buffer) -1] = 0;//remove the newline
    strcpy(student_grades[i],buffer);
  }

  //run all the threads
  for (int i = 0; i < NUM_STUDENTS; i++){
    pthread_create(&workers[i], 0, bellcurve, (void *) student_grades[i]);
    //printf("%s\n",student_grades[i]);
    pthread_join(workers[i],0);
  }

  
  
  return 0;
}





























