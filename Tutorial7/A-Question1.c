#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
	char name[256]; // character array of 256 length 
	int priority; // integer for the process priority 
	int pid; // integer for the process id 
	int runtime; // integer for running time in seconds
} proc;

typedef struct node{
	proc data; // instance of proc struct
	struct node *next; // next node in queue
} queue;

queue *first = NULL;
queue *last = NULL;

void push(proc process);

void readFile();

int main(void){
	// fill queue
	readFile();

	// print queue
	queue *current = first;
	while(current!=NULL){
		printf("name: %s priority: %d pid: %d runtime: %d\n",
			current->data.name,current->data.priority,current->data.pid,current->data.runtime);

		// increment through queue
		current = current->next;
	}

	// free memory
	for(int i=0; i<10; i++){
		queue *temp = first;
		first = first->next;
		free(temp);
	}
}

void push(proc process){
	// create new element of queue
	queue *newq = (queue *) malloc(sizeof(queue));
	newq->data = process;
	newq->next = NULL;

	// empty queue
	if(last!=NULL){
		last->next = newq;
	}
	// increment last to new last process
	last = newq;
}

void readFile(){
	proc *process = (proc *) malloc(sizeof(proc));
	char line[256] = {0};
	FILE *fp = fopen("processes.txt","r");

	// error checking
	if(fp==NULL){
		perror("Error opening file.\n");
		return;
	}

	for(int i=0; i<10; i++){
		fgets(line,256,fp);
		for(int j=0;j<256;j++){process->name[j] = 0;} // zero char array
		strcpy(process->name, strtok(line, ",")); // copy name from file into process
		// assign integer values from file
		process->priority = (int) (strtok(NULL, ",")-'0');
		process->pid = (int) (strtok(NULL, ",")-'0');
		process->runtime = (int) (strtok(NULL, "\n")-'0');

		// push process onto queue
		push(*process);

		// if queue contains no processes
		if(first==NULL){
			first = last;
		}
	}

	fclose(fp);
}