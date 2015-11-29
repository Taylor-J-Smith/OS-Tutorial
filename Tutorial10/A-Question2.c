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
#define PING_LIMIT 1000
#define DATA_SIZE 10000000


int main (int argc, char* argv[])
{
	// double data[DATA_SIZE] = { 0 };    // The data to send
	double *data = malloc(DATA_SIZE*(sizeof(double)));
	double starttime;
	double endtime;
    int ping_pong_num = 0;  // number of times we've pinged or ponged
    int proc_id;            // Process rank
    int n_proc;             // Number of processes
    MPI_Status status;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    
    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    starttime = MPI_Wtime();
    while(ping_pong_num < PING_LIMIT){
        ping_pong_num++;
        if (proc_id == MASTER){
        	MPI_Send(data, DATA_SIZE, MPI_DOUBLE,1,0,MPI_COMM_WORLD);
	    }else{
	    	MPI_Recv(data, DATA_SIZE, MPI_DOUBLE,MASTER,MPI_ANY_TAG,MPI_COMM_WORLD,&status); 
	    }

	    if (proc_id != MASTER){
        	MPI_Send(data, DATA_SIZE, MPI_DOUBLE,MASTER,0,MPI_COMM_WORLD);
	    }else{
	    	MPI_Recv(data, DATA_SIZE, MPI_DOUBLE,1,MPI_ANY_TAG,MPI_COMM_WORLD,&status); 
	    }
    }

    // Display a "Hello world" message from each child/parent
    if (proc_id == MASTER)
    {
		endtime = MPI_Wtime();
	    printf("%f\n",endtime - starttime );    
	}

    // Required to terminate all MPI processes
    
    MPI_Finalize();
    
}
