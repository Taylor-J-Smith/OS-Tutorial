#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef struct{
	char parent[256]; // character array of 256 length 
	char name[256]; // character array of 256 length 
	int priority; // integer for the process priority 
	int memory; // integer for the process id 
} proc;

typedef struct node
{
	proc data;
	struct node *left;
	struct node *right;
} node_t;

char** tokenize2(char *input, char *delim);

//need to add items
int insert(node_t *tree, proc *new_data);

//need to iterate over items
void print_tree(node_t *tree);

void readFile();


int main(void)
{
	node_t *tree = (node_t*)malloc(sizeof(node_t));
	readFile(tree);
	print_tree(tree);
	return 0;
}

int insert(node_t *tree, proc *new_data){
	node_t *temp = (node_t*)malloc(sizeof(node_t));

	//tree is empty
	// printf("Tree Data Name:%s : New Data Parent:%s\n",new_data->name,new_data->parent );

	if (tree == NULL)
	{
		return 0;
	}

	if (strcmp(new_data->parent,"NULL") == 0){
		tree->data = *new_data;
		return 0;
	}

	if (strcmp(tree->data.name,new_data->parent) == 0){
		if (tree->left == NULL){
			//left is empty, insert into left
			temp->data = *new_data;
			tree->left = temp;
			return 1;
		}else if (tree->right == NULL){
			//right is empty, insert into right
			temp->data = *new_data;
			tree->right = temp;
			return 1;
		}
	}else{
		insert(tree->left, new_data);
		insert(tree->right, new_data);
	}
}

void print_tree(node_t *tree){
	if (tree != NULL){
		printf("tree:%s\n", tree->data.name);
		if (tree->left != NULL){
			print_tree(tree->left);
		}

		if(tree->right != NULL){
			print_tree(tree->right);
		}
	}
}

void readFile(node_t *tree){
	proc *process = (proc *) malloc(sizeof(proc));
	char line[256] = {0};
	FILE *fp = fopen("processes_tree.txt","r");

	// error checking
	if(fp==NULL){
		perror("Error opening file.\n");
		return;
	}

	for(int i=0; i<7; i++){
		fgets(line,256,fp);
		for(int j=0;j<256;j++){process->name[j] = 0;} // zero char array
		char **tokenized = tokenize2(line,", ");
		strcpy(process->parent, tokenized[0]);
		strcpy(process->name, tokenized[1]);
		// assign integer values from file		
		process->priority = atoi(tokenized[2]);
		process->memory = atoi(tokenized[3]);
		
		// printf("Process Parent:%s\n",process->parent );
		// printf("Process Name:%s\n",process->name );
		// printf("Process Priority:%s\n",tokenized[2] );
		// printf("Process Memory:%s\n",tokenized[3] );
		// push process onto queue
		insert(tree, process);
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
