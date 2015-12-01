/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

#define DATA_SIZE 10000
#define CHUNK_SIZE 100

void master(int n_proc)
{
  double data[DATA_SIZE] = { 0 };    // The data to send
  double chunk[CHUNK_SIZE] = { 0 };  // The chunk to store results
  double results[DATA_SIZE] = { 0 }; // The final calculations
  int total_chunks = DATA_SIZE / CHUNK_SIZE;
  double total = 0;
  int n_sent = 0, n_recv = 0;        // The number of the data chunks sent/recv
  int proc = 0;                      // The process that returned data
  MPI_Status status;                 // MPI status struct

  // Populate the data to send to slaves
  for (int i = 0; i < DATA_SIZE; ++i)
    {
      data[i] = i;
    }

  // "Map" the data to slave processes
  // i MUST start from 1, since MASTER is process 0!
  for (int i = 1; i < n_proc; ++i)
    {
      // Send CHUNK_SIZE of data to each process initially
      // Sends data, of type double to process 'i'
      //MPI_Sends sends the Chunk data size to the specified process that is indicated by the dest parameter on this case i. Included in the message data is also the tag of the message, which in our case is n_sent indicating what number chunk is being sent. This allows the Master to keep track of what process got what chunk so when it pieces everything back together it knows the correct order.
      MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_DOUBLE, i, 
	       n_sent, MPI_COMM_WORLD);
      n_sent++;
    }

  // Receive EACH of the chunks from the slave processes
  for (int i = 0; i < total_chunks; ++i)
    {
      // Receive the computed chunk back from the slave
      //Once the processes have executed their chunk, the MPI_recv will take that computed chunk and check which process completed it as well as what chunk number was completed. These are both obtained from the status by calling MPI_SOURCE and MPI_Tag respectively. 
      MPI_Recv(chunk, CHUNK_SIZE, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
	       MPI_COMM_WORLD, &status);
      // Get the process that sent the data and send it the next chunk
      proc = status.MPI_SOURCE;
      n_recv = status.MPI_TAG;
        
      // Copy the results from the slave into the results array
      for (int i = 0; i < CHUNK_SIZE; ++i)
        {
	  results[n_recv*CHUNK_SIZE + i] = chunk[i];
        }

      if (n_sent < total_chunks)
        {
	  //if any chunks are still left to be sent and there are available processes a message will the sent to the designated dest process (proc) as well as the tag which indicates which chunk number is to be completed for bookkeeping purposes.
	  MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_DOUBLE, proc, 
		   n_sent, MPI_COMM_WORLD);
	  n_sent++;
        }
    }

  // Send all the slave processes STOP signal, (TAG of CHUNK_SIZE)
  for (int i = 1; i < n_proc; ++i)
    {
      //Once all the processes have computed all the chunks, then the master process sends and message with MPI_Send to let the processes know that they are not longer needed. This is done by sending the CHUNK_SIZE, or 100 as the tag to indicate termination.
      MPI_Send(chunk, CHUNK_SIZE, MPI_DOUBLE, i, 
	       CHUNK_SIZE, MPI_COMM_WORLD);
    }

  for (int i = 1; i < DATA_SIZE; ++i)
    {
      if (data[i] < 1)
        {
	  printf("ERROR, DATA ZERO AT INDEX %d\n", i);
        }
    }
  // "Reduce" and calculate the final summation
  for (int i = 0; i < DATA_SIZE; ++i)
    {
      total += results[i];
    }

  printf("The final sum of the calculation: %f\n", total);
}


void slave(int proc_id)
{
  double chunk[CHUNK_SIZE] = { 0 };  // The chunk to receive for calculations
  double result[CHUNK_SIZE] = { 0 }; // The results
  int n_recv = 0;                    // The number of the data chunk received
  MPI_Status status;                 // MPI status struct

  // Receive the chunk to calculate from MASTER
  //The slave/process/computer takes the message sent by the master process and obtains the tag from status.MPI_TAG in order to keep track of what chunk is being worked on. If n_recv == CHUNK_SIZE then that is a signal from the master that the process is to terminate, and the below while loop will not execute.
  MPI_Recv(chunk, CHUNK_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  n_recv = status.MPI_TAG;

  // Calculate all results provided until "STOP" signal recieved (CHUNK_SIZE)
  while (n_recv < CHUNK_SIZE)
    {
      // Perform our "calculation" to return back to MASTER
      for (int i = 0; i < CHUNK_SIZE; ++i)
        {
	  result[i] = chunk[i] * chunk[i];
        }

      // Send the results back to MASTER, include in TAG the chunk that was calculated
      //Once the initial chunk has been computed and put into result, it is then sent off back to the master along with the index number, or n_recv to allow the master to place it in the correct location in the overall results of the computation
      MPI_Send(result, CHUNK_SIZE, MPI_DOUBLE, MASTER, n_recv, MPI_COMM_WORLD);
        
      // Wait for the next chunk of data to be received
      //Once an iteration of receiving, calculation and sending is done, the process then waits again for information to be sent by the master along with all the necessary information similar to above (ie. the index n_recv). If the n_recv == CHUNK_SIZE then this will cause the while loop above to fail and the process to terminate.
      MPI_Recv(chunk, CHUNK_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      n_recv = status.MPI_TAG;
    }
}


int main (int argc, char* argv[])
{
  int proc_id;            // Process rank
  int n_proc;             // Number of processes

  //--------MPI BOILERPLATE CODE---------
  // Initializes the MPI execution enviornment and must  be called ONCE by every program that uses MPI. It must be called before any other MPI functions are called. In this case it passes the command line arguments to all the processes.
  MPI_Init(&argc, &argv);
    
  // Get the current process id. Initially every process has a designated unique integer rank between 0 and the number of task -1 within the communicator. The rank is usually refered to as the task ID or the process id. If a process becomes associated with other communicators then it will consequently have a unique rank within each.
  MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

  //Returns the total number of MPI processes in the communcator, below it is SMPI_COMM_WORLD in which case it represents the number of MPI tasks available to our application that is being run.
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    

  if (proc_id == MASTER)
    {
      master(n_proc);
    }
  else
    {
      slave(proc_id);
    }    
  //Terminates the MPI execution environment. This function needs to be called in every application using MPI and no other MPI routines can be called after calling MPI_Finalize
  MPI_Finalize();
}
