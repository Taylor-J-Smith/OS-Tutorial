
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int *grades[10] = {0};

void read_grades(){
    // open grades file
    FILE *grade_file = fopen("grades.txt","r");

    // stop if unable to open file
    if(grade_file == NULL){
        perror("Error opening file.\n");
        exit(1);
    }

    int j=0;
    fscanf(grade_file, "%d", &grades[0]);
    while(!feof (grade_file) && j<10){
        j++;
        fscanf(grade_file, "%d", &grades[j]);
    }

    fclose(grade_file);
}

int main(int argc, char *argv[]) {

    // Thread object
    //pthread_t pth;
    //pthread_t pth2;

    // Create the thread.
    //pthread_create(&pth, 0, threadFunc, (void *) "Thread 1");
    //pthread_create(&pth2, 0, threadFunc, (void *) "Thread 2");

    // barrier for thread to finish before continuing
    
    read_grades();

    return 0;
}