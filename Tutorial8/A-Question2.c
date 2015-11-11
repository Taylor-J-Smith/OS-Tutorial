#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
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

int main(void)
{

	return 0;
}
