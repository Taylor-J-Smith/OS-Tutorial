#OS TUT 6 - Oct 28

*Forking*: a way of running a process
Child Starts right on the line after fork() is called
Up to the fork point parent and child share the same memory (aka all variables declared before the fork are shared)

big advantages of semaphores: it has P:wait() V:signal()
* can have more than 1 semaphore as opposed to mutexes
* mutex is binary, has only 1 thread accessing it or not
* Initialize the semaphore as 0;

	sem_wait(&sem);
	//critical section
	sem_post(&sem);
	
factorial
0! = 1


























