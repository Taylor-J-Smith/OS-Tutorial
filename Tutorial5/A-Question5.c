#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_GRADES 10

int grades[NUM_GRADES] = {0};
int total_grade = 0;
int total_bellcurve = 0;

pthread_barrier_t barr1;
pthread_barrier_t barr2;
pthread_mutex_t mutex;

void* read_grades(){
    // open grades file
    FILE *grade_file = fopen("grades.txt","r");

    // stop if unable to open file
    if(grade_file == NULL){
        perror("Error opening file.\n");
        exit(1);
    }

    for(int j=0; j<10; j++){
        fscanf(grade_file, "%d", &grades[j]);
    }

    fclose(grade_file);

    pthread_barrier_wait(&barr1);

    return NULL;
}

void* save_bellcurve(void *arg){
    int *grade = (int *) arg;

    // Lock the mutex
    pthread_mutex_lock(&mutex);
 
    total_grade += *grade;
    *grade = *grade * 1.5;
    total_bellcurve += *grade;

    // Unlock the mutex
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barr2);
    return NULL;
}

int main() {

    /**
     * Read in grades
     */

    // Thread object
    pthread_t read;

    if(pthread_barrier_init(&barr1, 0, 2)){
        printf("Could not initialize barrier.\n");
    }

    // Create the thread.
    pthread_create(&read, 0, read_grades, (void *) "Read");

    // barrier for thread to finish before continuing
    int rc = pthread_barrier_wait(&barr1);///////////////////////////////////////////////////Barrier
    if(rc!=0 && rc!=PTHREAD_BARRIER_SERIAL_THREAD){
        printf("Could not wait on barrier.\n");
    }

    /**
     * bellcurve
     */

     // Initialize the barrier
    if(pthread_barrier_init(&barr2, 0, sizeof(grades)/sizeof(grades[0])+1)){
        printf("Could not initialize barrier.\n");
    }
    // Initialize the mutex
    if(pthread_mutex_init(&mutex, NULL))
    {
        printf("Unable to initialize a mutex\n");
        return -1;
    }

    pthread_t bell[NUM_GRADES];
    for(int i=0; i<NUM_GRADES; i++){
        pthread_create(&bell[i], 0, save_bellcurve, (void *) &grades[i]);
    }

    rc = pthread_barrier_wait(&barr2);///////////////////////////////////////////////////////Barrier
    if(rc!=0 && rc!=PTHREAD_BARRIER_SERIAL_THREAD){
        printf("Could not wait on barrier.\n");
    }
    // Clean up the mutex
    pthread_mutex_destroy(&mutex);

    printf("Pre-Bellcurve Grade Total: %d, Pre-Bellcurve Grade Average: %d\n", total_grade, (total_grade/NUM_GRADES));
    printf("Post-Bellcurve Grade Total: %d, Post-Bellcurve Grade Average: %d\n", total_bellcurve, (total_bellcurve/NUM_GRADES));

    FILE *bellcurved_grades = fopen("bellcurved_grades.txt", "w");

    for(int i=0; i<NUM_GRADES; i++){
        fprintf(bellcurved_grades, "%d\n", grades[i]);
    }

    fclose(bellcurved_grades);
    return 0;
}