/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

int main (int argc, char* argv[])
{
  int proc_id;            // Process rank
  int n_proc;             // Number of processes

  //--------MPI BOILERPLATE CODE---------
  // Initializes the MPI execution enviornment and must  be called ONCE by every program that uses MPI. It must be called before any other MPI functions are called. In this case it passes the command line arguments to all the processes.
  MPI_Init(&argc, &argv);
    
  // Get the current process id. Initially every process has a designated unique integer rank between 0 and the number of task -1 within the communicator. The rank is usually refered to as the task ID or the process id. If a process becomes associated with other communicators then it will consequently have a unique rank within each.
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
  //Returns the total number of MPI processes in the communcator, below it is SMPI_COMM_WORLD in which case it represents the number of MPI tasks available to our application that is being run.
  MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

  // Display a "Hello world" message from each child/parent
  if (proc_id == MASTER)
    {
      printf( "Hello world from MATER, process %d of %d\n", proc_id, n_proc);
    }
  else
    {
      printf( "Hello world from SLAVE, process %d of %d\n", proc_id, n_proc);
    }
  //Terminates the MPI execution environment. This function needs to be called in every application using MPI and no other MPI routines can be called after calling MPI_Finalize
  MPI_Finalize();
}
