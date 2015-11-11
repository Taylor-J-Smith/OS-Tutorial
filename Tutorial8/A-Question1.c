#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHAR_LENGTH 256

typedef struct{
	char parent[CHAR_LENGTH];
	char name[CHAR_LENGTH];
	int priority;
	int memory;
} proc;

typedef struct tree{
	proc process;
	struct tree *left;
	struct tree *right;
} proc_tree;

int main(void){

	return 0;
}
