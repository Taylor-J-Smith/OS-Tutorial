#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct node{
  int val;
  struct node* next;
}node_t;

 
void print_list(node_t *head);
void push(node_t** head, int val); //returns the new head
int pop(node_t **head);
  
int main(){
  node_t *head = NULL;
  push(&head,1);
  push(&head,2);
  push(&head,3);

  pop(&head);
  pop(&head);
  pop(&head);
  pop(&head);
  print_list(head);
  

  return 0;
}

int pop(node_t **head){
  int popped_val = -1;
  node_t* next_node = NULL;

  if (*head == NULL){
    return -1;
  }

  next_node = (*head)->next;
  popped_val = (*head)->val;
  free(*head);
  *head = next_node;

  return popped_val;
}

void push(node_t** head, int val){
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
    printf("%d\n",current->val);
    current = current->next;
  }
}



























