#Tutorial 6

##Conceptual Questions 
**1. What is​ fork()​, how does it differ from multi­threading (pthreads)?**
A fork creates a completely new process that looks nearly identical to the parent process that called fork() but with its own memory and its own unique process ID. All the commands are copied to the child process but other than that without any communication they share nothing in common. Threads on the other hand only have separate registers and stacks, but share the code, data and file. Creating a thread is much more lightweight and doesn't have as much memory that needs to be copied.

**2. What is inter­process communication (​IPC​)? Describe methods of performing IPC.**
Since the different processes don't share memory they must communicate with one another via different methods. Inter process communications involve different methods and protocols in order to send information/data from one process to another. Some of methods used to perform IPC include:
>
1. Files: file stored on HDD and can be read by different processes
2. Socket: Data stream that is sent over a network
3. Message queue: Readers/Writers talking to one another via messages in buffers
4. Pipe: Two processes talking with their standard inputs outputs.
5. Semaphore: Locking mechanism (wait/signal) that allows processes to enter critical sections of the code.
6. Shared memory: Different processes are given access and are able to communicated via same memory block.
7. Message passing: Communicating with channels

**3. Provide an explanation of ​semaphores​, how do they work, how do they differ from mutual exclusion**
Semaphores by definition are something that allows and most importantly controls access to share data amongst processes. Semaphores have two functions which allow for mutual exclusion, mainly wait(P) and signal(V) which decrement and increment the value of the semaphore respectively. They differ from mutual exclusion in that they allow processes to que up when they need is as opposed to just sitting in a busy wait until the lock frees up.

**4. Provide an explanation of ​wait (P)​ and ​signal (V)**
When the value of the semaphore is positive (> 0) then that indicates that the semaphore is unlocked and can be used. A value that is 0 or < 0 indicates that the semaphore is locked. A semaphore can also have a list of processes waiting to use it, so if the value is negative, the magnitude represents the amount of processes waiting to use it. *wait(P)* decrements the semaphore value and checks if that value is < 0, if it is then the process that wishes to use it is added to the list of processes waiting, and finally block is called. This is typically called before entering the critical section of a program *signal()* on the other hand increments the semaphore value and and if the semaphore value is <= 0 then it means that the process was on the waiting list and must be removed from the queue list and woken up.

**5. Research the main functions used for semaphores in ​<semaphore.h>​ and explain each function.**

##<semaphore.h>

	int    sem_close(sem_t *sem);
	//used to indicate that the calling process is finished using the named semaphore indicated by sem.
------------------
	
	int    sem_destroy(sem_t *sem);
	//used to destory the unnamed semaphore indicated by sem.
------------------
		
	int    sem_getvalue(sem_t *sem, int *sval());
	//updates the location referenced by the sval argument to have the value of the semaphore referenced by sem without affecting the state of the semaphore.
------------------
	
	int    sem_init(sem_t *sem, int pshared, unsigned int value);
	//used to initialize the semaphore with the argument value. If the argument pshared is a non-zero value then the semaphore is shared between processes.
------------------

	sem_t *sem_open(const char *name, int oflag, ...);
	//establishes a connection between a name semaphore and a process.
------------------
	
	int    sem_post(sem_t *sem);
	//unlocks the semaphore referenced by sem by performing a semaphore unlock operation on that semaphore.
------------------
	
	int    sem_trywait(sem_t *sem);
	//locks the semaphore referenced by sem by performing a semaphore lock operation on that semaphore.
------------------
	
	int    sem_unlink(const char *name);
	//removes the semaphore named by the name argument. 
------------------
	
	int    sem_wait(sem_t *sem);
	//locks the semaphore sem by preforming a semaphore lock operation on that semaphore.
------------------
	
##Application Questions

1. **DONE**
2. **DONE**
3. **DONE**
4. **DONE**
5. **DONE**


























