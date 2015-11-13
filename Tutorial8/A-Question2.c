#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHAR_LENGTH 256

typedef struct {
  char name[CHAR_LENGTH];
  int priority;
  int pid;
  int address;
  int memory;
  int runtime;
  bool suspended;
} proc;


typedef struct node{
  proc val;
  struct node* next;
}node_t;

typedef struct {
  node_t *head;
  node_t *tail;
}queue;

char** tokenize2(char *input, char *delim); 
void print_list(queue *q1);
//void push(node_t** head, proc val); //returns the new head
void push(queue **q1, proc val);
proc pop(node_t **head);
void readFile();
  
int main(){
  queue *test = (queue *)  malloc(sizeof(queue)); //temp
  test->head = NULL;
  test->tail = NULL;
  node_t *priority = NULL; //queue 1
  node_t *secondary = NULL; //queue 2
  
  //start temp
  proc *p1 = (proc *)malloc(sizeof(proc));
  strcpy(p1->name,"p1");
  p1->priority = 0;
  p1->pid = 33;
  p1->runtime = 5;
  push(&test,*p1);
  
  proc *p2 = (proc *)malloc(sizeof(proc));
  strcpy(p2->name,"p2");
  p2->priority = 0;
  p2->pid = 33;
  p2->runtime = 5;
  push(&test,*p2);
  
  //proc popped = pop(&test);
  //printf("%s\n",popped.name);
  //  push(&test,popped);
  print_list(test);
  //  pop(&test);
  return 0;
  //end temp
  

  return 0;
  readFile(&priority,0);//loads all processes with priority == 0
  readFile(&secondary,1);//loads all processes with priority != 0
  //  print_list(priority);
  //  puts("----");
  //  print_list(secondary);
  
  //create an array of available memory
  int avail_mem[1024] = {0};

  //iterate through all priority processes
  node_t *temp = priority;
  while (temp != NULL){
    pid_t pid = fork();
    if (pid == 0){
      //child process
      puts("child:");
      execlp("./process",NULL);
      exit(0);
    }else if (pid >0){
      //parent process
      temp->val.pid = pid; //set the pid of the process
      //allocate the required memory
      int i = 0;
      temp->val.address = i;
      for (i = 0; i < temp->val.memory; i++){
	avail_mem[i] = 1;
      }
      puts("--------------------------------------------");
      printf("[parent] Executing process: %s, priority: %d, pid: %d, memory: %d, runtime: %d\n",
	     temp->val.name,temp->val.priority,temp->val.pid,temp->val.memory, temp->val.runtime);
      printf("[parent] waiting %d seconds...:\n",temp->val.runtime);
      sleep(temp->val.runtime); //sleep for the needed runtime
      puts("[parent] Sending SIGINT...");
      kill(pid,SIGINT);
      waitpid(pid,0,0);
      //free the allocated memory
      printf("[parent] Current available memory: %dMB\n",freeMemoryAmount(avail_mem,1024));
      printf("[parent] Freeing: %dMB of memory\n",temp->val.memory);
      for (int j = 0; j < temp->val.memory; j++){
	avail_mem[j] = 0;
      }
      //print process to be deleted
      printf("[parent] Deleting process: %s, priority: %d, pid: %d, runtime: %d\n",
	     temp->val.name,temp->val.priority,temp->val.pid,temp->val.runtime);
      //delete process from queue
      temp = temp->next;
      pop(&priority);
    }else{
      //fork failed
    }
  }
    
  //iterate through all the secondary processes
  temp = secondary;
  int memory_index = 0;
  while (secondary != NULL){ //while items in Queue
    proc popped_proc = pop(&secondary);//pop the current process
    //check if there is enough memory for current process
    if (popped_proc.memory <= freeMemoryAmount(avail_mem,1024)){
      printf("Memory amount sufficies, free memory: %dMB\n",freeMemoryAmount(avail_mem,1024));
      //continue
      //alocate the needed memory
      popped_proc.address = memory_index;  //set the address for the memory block
      for (int i = 0; i < popped_proc.memory; i++){
	avail_mem[i+memory_index] = 1;
      }
      memory_index += popped_proc.memory;
      //print process information
      printf("process: %s, priority: %d, pid: %d, memory: %d, runtime: %d\n",
	     popped_proc.name,
	     popped_proc.priority,
	     popped_proc.pid,
	     popped_proc.memory,
	     popped_proc.runtime);
      pid_t pid = fork();
      if (pid == 0){
	//child process
	puts("child:");
	execlp("./process",NULL);
	exit(0);
      }else if(pid > 0){
	//parent process
	if (popped_proc.runtime == 1){
	  printf("[parent] One second left on Process: %s\n",popped_proc.name);
	  //process only has 1 second of runtime left
	  sleep(1);//run for the remaining second
	  kill(pid,SIGINT); //terminate the process
	  waitpid(pid,0,0); //wait for the process
	  //free the avail_mem used by the process
	  for (int i = popped_proc.memory; i>0; i++){
	    avail_mem[i] = 0;
	  }
	  memory_index -= popped_proc.memory;
	}else if (popped_proc.suspended == 1){//check if already suspended process
	  printf("[parent] Resuming process: %s\n",popped_proc.name);
	  kill(pid,SIGCONT);
	  sleep(1); //sleep for once second
	  kill(pid,SIGTSTP);
	  //add the process back on the queue
	  push(&secondary, popped_proc);
	}else{
	  printf("[parent] Creating new process: %s\n",popped_proc.name);
	  //new process to be created
	  popped_proc.pid = pid; //set the process id [TODO: FIX PID]
	  popped_proc.runtime -= 1; //decrement the runtime
	  popped_proc.suspended = 1; //update the suspended boolean
	  sleep(1);
	  kill(pid,SIGTSTP);
	  //add the process back on the queue
	  push(&secondary, popped_proc);
	}
	//	waitpid(pid,0,0);
      }else{
	//fork error
      }
    }else{
      //not enough memory, push back on the queue
      push(&secondary, popped_proc);
    }
  }      
  return 0;
}

int freeMemoryAmount(int memory[],int length){
  int freeMemory = 0;
  for (int i = 0; i < length; i++){
    if (memory[i] == 0){
      freeMemory++;
    }
  }
  return freeMemory;
}

proc pop(node_t **head){
  node_t* next_node = NULL;
  proc popped_val;

  //  if (*head == NULL){
  //    printf("Error: Pop on <empty>");
  //  }else{
  if (*head != NULL){  
    next_node = (*head)->next;
    popped_val = (*head)->val;
    free(*head);
    *head = next_node;
  }
  return popped_val;
}

void push(queue **q1, proc val){
  //create a new node
  node_t* newNode = malloc(sizeof(node_t));
  newNode->val = val;
  newNode->next = NULL;

  if ((*q1)->head == NULL && (*q1)->tail == NULL){
    //q1 is empty
    (*q1)->head = newNode;
    (*q1)->tail = newNode;
  }else{
    (*q1)->tail->next = newNode;
    (*q1)->tail = newNode;
  }
}

void print_list(queue *q1){
  //  node_t *current = head;
  node_t *current = q1->head;
  
  //check if list is empty
  if(q1->head == NULL){
    printf("<empty>\n");
    return;
  }
  
  while(current != NULL){
  //temp
  /*  char name[CHAR_LENGTH];
  int priority;
  int pid;
  int address;
  int memory;
  int runtime;
  bool suspended;*/
  //end temp
  printf("process: %s, priority: %d, pid: %d, address: %d, memory: %d, runtime: %d\n",
    current->val.name,
    current->val.priority,
    current->val.pid,
    current->val.address,
    current->val.memory,
    current->val.runtime);
  //iterate to next item
    current = current->next;
  }
}

  void readFile(node_t** head, int priority_filter){
  //if priority_filter = -1 -> load all processes
  //if priority_filter = 0  -> load processes with priority = 0
  //if priority_filter = 1  -> load all processes with priority != 0
  char buffer[CHAR_LENGTH] = {0};
  FILE *f1 = fopen("processes_q5.txt","r");
  if (f1 == NULL){
    perror("Error opening file\n");
    return;    
  }

  for (int i = 0; i < 10; i++){
    fgets(buffer,CHAR_LENGTH, f1);
    proc *temp_proc = (proc *)  malloc(sizeof(proc));
    char **tokenized = tokenize2(buffer,", ");
    //priority is in tokenized[1]
  if ((atoi(tokenized[1]) == 0 && priority_filter == 0)|| //only priority == 0
  (atoi(tokenized[1]) != 0 && priority_filter == 1)|| //only priority != 0
  (priority_filter == -1)) //all
  {
      strcpy(temp_proc->name, tokenized[0]); //name
      temp_proc->priority = atoi(tokenized[1]);//priority
      temp_proc->pid = 0;//pid
      temp_proc->address = 0; //address
      temp_proc->memory = atoi(tokenized[2]); //memory
      temp_proc->runtime = atoi(tokenized[3]);//runtime

      //push process onto queue
      push (head,*temp_proc); 
    }
  }
  fclose(f1);
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

























