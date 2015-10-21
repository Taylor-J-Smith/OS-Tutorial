#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_LEN 256
#define NUM_STUDENTS 5

typedef struct {
  char name[BUFFER_LEN];
  double grade;
}student;

void *bellcurve(void *arg){
  student* currStudent = (student*)arg;
  
  printf("%s,%.2f\n",currStudent->name,currStudent->grade*1.5);
  
  return NULL;
}

int main(int argc, char *argv[]) {
  //  char student_grades[NUM_STUDENTS][BUFFER_LEN];
  student students[NUM_STUDENTS];
  char buffer[BUFFER_LEN];
  pthread_t workers[NUM_STUDENTS];
  
  printf("Enter the grades for five students:\n");   

  for (int i = 0; i < NUM_STUDENTS; i++){
    printf("Student #%d name:",i+1);//get the name
    fgets(buffer,BUFFER_LEN,stdin);
    buffer[strlen(buffer) -1] = 0;//remove the newline
    strcpy(students[i].name, buffer);
    printf("Student #%d grade:",i+1);//get the grade
    fgets(buffer,BUFFER_LEN,stdin);
    buffer[strlen(buffer) -1] = 0;//remove the newline
    students[i].grade = atof(buffer);
  }

  //run all the threads
  for (int i = 0; i < NUM_STUDENTS; i++){
    pthread_create(&workers[i], 0, bellcurve, (void *) &students[i]);
    //printf("%s\n",student_grades[i]);
    pthread_join(workers[i],0);
  }

  
  
  return 0;
}



























































