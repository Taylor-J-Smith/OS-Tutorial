
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

    char fchar;
    int i=0;
    int j=0;
    while((fchar = fgetc(grade_file)) != EOF && j<10){
        if(fchar != '\n'){
            // add character to grade
            printf("%d\n", fchar);
            // *grades[j] = *grades[j]*10 + (fchar-'0');
            *grades[j] = *grades[j]*10 + (fchar-'0');
            printf("%d\n",grades[j] );
            i++;
        } else {
            // next grade
            j++;
            // end of line restart at begining of line array
            i = 0;
        }
    }
    *grades[j] = *grades[j]*10 + (fchar-'0');

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