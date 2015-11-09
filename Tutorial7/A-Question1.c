#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char** tokenize2(char *input, char *delim);

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
		char **tokenized = tokenize2(line,", ");
		strcpy(process->name, tokenized[0]);
		// assign integer values from file		
		process->priority = atoi(tokenized[1]);
		process->pid = atoi(tokenized[2]);
		process->runtime = atoi(tokenized[3]);
		
		// push process onto queue
		push(*process);

		// if queue contains no processes
		if(first==NULL){
			first = last;
		}
	}

	fclose(fp);
}

char** tokenize2(char *input, char *delim){
  //takes an input string with some delimiter and returns an array
  //with all the tokens split by the provided delimiter

  //Sample usage:
  //char buffer[] = "a b c";
  //char **user_output;
  //user_output = tokenize(buffer, " ");

  char** tokens = 0;
  size_t num_elements = 0;
  size_t tokens_index  = 0; //keep tracks of the  tokens offset when adding them
  char* input_cpy = input;
  char *input_cpy2 = malloc(1 + strlen(input)); //used with strtok
  if (input_cpy2){
    strcpy(input_cpy2, input);
  }else{
    printf("error copying input\n");
  }

  //iterate through the intput and count # of delims
  while (*input_cpy != NULL){
    if (*delim == *input_cpy){
      num_elements++;
    }input_cpy++;
  }

  num_elements++; //for last object
  num_elements++; //for null terminating value

  //create enough memory for all the elements
  tokens = malloc(sizeof(char*) * num_elements);
  char* token = strtok(input_cpy2, delim);
  while (token){
    //store the token in the tokens array
    *(tokens + tokens_index++) = strdup(token);   //strdup duplicates the string
    token = strtok(0, delim); //next token
  }
  //finally add null value at the end
  *(tokens + tokens_index) = 0;
  return tokens;
}
