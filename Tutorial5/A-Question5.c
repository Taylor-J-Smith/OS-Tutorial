
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
    // int i=0;
    // int j=0;
    // while((fchar = fgetc(grade_file)) != EOF && j<10){
    //     if(fchar != '\n'){
    //         // add character to grade
    //         printf("%d\n", fchar);
    //         // *grades[j] = *grades[j]*10 + (fchar-'0');
    //         grades[j] = fchar;
    //         printf("%d\n",grades[j]);
    //         i++;
    //     } else {
    //         // next grade
    //         j++;
    //         // end of line restart at begining of line array
    //         i = 0;
    //     }
    // }
    // *grades[j] = *grades[j]*10 + (fchar-'0');

    char buffer[10];

    for (int i = 0; i < 10; i++)
    {

        //prompt for input
        fgets(buffer, 10,grade_file);
        // buffer[strlen(buffer)-1]=0;

        // printf("%s\n",buffer);
        char *end;

        grades[i] = strtol(buffer, &end, 10);
    }

    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", grades[i]);
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