#Tut 5 - Wed Oct 20

pthread_mutex_t mutex;

//request the lock
pthread_mutex_lock (&mutex);

//release the lock
pthread_mutex_unlock (&mutex);

*thread advantages*
computers nowadays have multiple cores, and can process multiple streams of data at once. Very useful because they can all share the same memory. Multiple processes are going to need IPC which have their own headers and concurrency issues.

barriers: all threads must get to that point before proceeding (like a multiple joins)

























