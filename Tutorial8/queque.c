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


char** tokenize2(char *input, char *delim); 
void print_list(node_t *head);
void push(node_t** head, proc val); //returns the new head
void pop(node_t **head);
void readFile();
  
int main(){
  node_t *priority = NULL; //queue 1
  node_t *secondary = NULL; //queue 2

  /*  proc *p1 = (proc *)malloc(sizeof(proc));
  strcpy(p1->name,"p1");
  p1->priority = 0;
  p1->pid = 33;
  p1->runtime = 5;

  //  push(&priority,*p1);*/

  readFile(&priority);
  print_list(priority);
  return 0;
}

void pop(node_t **head){
  node_t* next_node = NULL;

  if (*head == NULL){
    printf("Error: Pop on <empty>");
    return;
  }

  next_node = (*head)->next;
  proc popped_val = (*head)->val;
  free(*head);
  *head = next_node;
  //  return popped_val;
}

void push(node_t** head, proc val){
  node_t* newNode = malloc(sizeof(node_t));
  newNode->val = val;
  newNode->next = *head;
  *head = newNode;
}

void print_list(node_t *head){
  node_t *current = head;
  //check if list is empty
  if(head == NULL){
    printf("<empty>\n");
    return;
  }
  
  while(current != NULL){
  printf("process: %s, priority: %d, pid: %d, runtime: %d\n",
    current->val.name,current->val.priority,current->val.pid,current->val.runtime);
  //    printf("%d\n",current->val);
    current = current->next;
  }
}

void readFile(node_t** head){
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
    strcpy(temp_proc->name, tokenized[0]);
    // assign integer values from file		
    temp_proc->priority = atoi(tokenized[1]);
    temp_proc->pid = 0;
    temp_proc->memory = atoi(tokenized[2]);
    temp_proc->runtime = atoi(tokenized[3]);

    //push process onto queue
    push (head,*temp_proc);
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

























