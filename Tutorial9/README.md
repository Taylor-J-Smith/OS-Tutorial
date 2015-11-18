#Tutorial 7 - Wed Nov 4

##Application Questions

1. <OPEN>
2. In Progress- Jeremy
3. <OPEN>
4. <OPEN>
5. <OPEN>


##Conceptual Questions
**1. What are signals, what is their purpose?**
  Signals are a form of inter-process communication. They are used to communicate with processes and inform them that an event has happend or that they should do something.

**2. Explain the following signals: SIGINT, SIGTSTP, SIGCONT ​how can they be used to suspend, resume, and terminate a program?**
  SIGINT - Signal interrupt, this will end the process, just as if exit() was called.
  SIGTSTP - Stop signal, this will suspend the process to be resumed at a later time.
  SIGCONT - Signal continue, this will resume the process that has been suspended.


**3. Explain the following functions: kill(), waitpid()​ how can they be used to terminate a process and wait until it has ended before continuing?**
  The kill function will send a signal to a process, the specific signal and process are specified by the two arguments the function takes. waitpid will suspend a process until the status of the process specified in the arguments becomes available or until a signal is sent to it. You could use kill to send a SIGINT signal to a process to terminate it and then use waitpid passing that process as an argument to wait until it has ended before continuing.

**4. Explain what a linked­list​ (queue) is, what does ​FIFO​ mean? What are the common operations that a linked­list must have?**
  A linked list is a data structure where each element(node) has a data section and a pointer to the next node. FIFO stands for first in first out, which means that whichever node is put into the list first is removed from the list before nodes added after it. Common operations a linked list needs are: Append, Delete.


**5. Explain the structure of a linked­list as implemented in C, explain how would you implement the operations to add and remove values from the queue?**
  In c the linked list is implemented by creating a structure for nodes that has all the data required as well as a pointer to the next element of the list. The list is the initialized by setting the head and tail of the list to NULL. Nodes can then be added to the list by checking if the head is NULL, if it is simply set the new node equal to the head pointer. If it isn't you start at the head and then iterate through until you reach a node whose next pointer is NULL and you set that nodes next to be equal to your new node and set tail equal to your new node. To remove a node from the list, since it is FIFO we only ever need to remove the first node which can be done by setting the value of the head pointer to the next value of the current head pointer.


























