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

proc pop();

proc delete_name(char *name);

proc delete_pid(int pid);

void readFile();

int main(void){
	// fill queue
	readFile();

	delete_name("emacs");
	delete_pid(12235);

	// pop remaining nodes
	while(first!=NULL){
		queue *temp = first;
		printf("name: %s, priority: %d, pid: %d, runtime: %d\n",
			temp->data.name,temp->data.priority,temp->data.pid,temp->data.runtime);
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

proc pop(){
	proc popped_process;
	queue *temp;

	if(first!=NULL){
		// assign first process in queue to popped process
		popped_process = first->data;
		temp = first;
		// assign first to next node in queue
		first = first->next;
		free(temp);
	}

	return popped_process;
}

proc delete_name(char *name){
	proc deleted_process;
	queue *current = first;
	queue *temp = first;

	while(current!=NULL){
		// delete where name equals current->data.name
		if(strcmp(name,current->data.name)==0){
			if(current==first){
				// found at head of queue, assign first to next node in queue
				first = current->next;
			} else {
				// found after head of queue, assign previous value's next node 
				// to the node after the current node
				temp->next = current->next;
			}

			// retrieve process at current node
			temp = current;
			deleted_process = temp->data;

			free(temp);

			return deleted_process;
		}
		if(current!=first){
			temp = current;
		}
		current = current->next;
	}

	return deleted_process;
}

proc delete_pid(int pid){
	proc deleted_process;
	queue *current = first;
	queue *temp = first;

	while(current!=NULL){
		// delete where pid equals current->data.pid
		if(pid==current->data.pid){
			if(current==first){
				// found at head of queue, assign first to next node in queue
				first = current->next;
			} else {
				// found after head of queue, assign previous value's next node 
				// to the node after the current node
				temp->next = current->next;
			}

			// retrieve process at current node
			temp = current;
			deleted_process = temp->data;

			free(temp);

			return deleted_process;
		}
		if(current!=first){
			temp = current;
		}
		current = current->next;
	}

	return deleted_process;
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