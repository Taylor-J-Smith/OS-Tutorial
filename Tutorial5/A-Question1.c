#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *hello_world(void *arg)
{
  char *str;
  str = (char*) arg;

  sleep((rand() % 4));
  printf("%s: Hello World\n", str);
  return NULL;
}

void *goodbye_world(void *arg)
{
  char *str;
  str = (char*) arg;

  sleep((rand() % 4));
  printf("%s: Goodbye World\n", str);
  return NULL;
}


int main(void)
{
  // Thread object
  pthread_t pth;
  pthread_t pth2;

  // Create the thread.
  pthread_create(&pth, 0, hello_world, (void *) "Thread 1");
  pthread_create(&pth2, 0, goodbye_world, (void *) "Thread 2");

  // wait for our thread to finish before continuing
  pthread_join(pth, 0);
  pthread_join(pth2, 0);

  return 0;
}
