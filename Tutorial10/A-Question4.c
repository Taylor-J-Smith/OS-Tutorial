#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

void master(int n_slave, int range){
    int portion = range/n_slave;
    int excess = range-(portion*n_slave);
    int *num = (int *) malloc(sizeof(int)*range);
    int n_sent = 0;
    int *results = (int *) calloc(portion, sizeof(int));
    int prime_nums[n_slave][(int) ceil(((double) range/2+2)/n_slave)];
    int prime_count = 0;

    for(int i=0; i<(range/2+2); i++){
        prime_nums[i%n_slave][i/n_slave] = 0;
    }

    MPI_Status status;

    for(int i=1; i<=range; i++){
        num[i-1] = i;
    }

    for (int i = 1; i <= n_slave; ++i){
        // Send portion of num to each process initially
        // Sends num, of type int to process 'i'
        MPI_Send(&num[n_sent*portion], portion, MPI_INT, i, 
                 n_sent, MPI_COMM_WORLD);
        n_sent++;
    }

    for(int i=0; i<n_slave; ++i){
        // Receive the computed results back from the slave
        MPI_Recv(results, portion, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 MPI_COMM_WORLD, &status);

        for(int j=0; j<portion; j++){
            if(results[j]!=0){
                prime_nums[prime_count%n_slave][prime_count/n_slave] = results[j];
                prime_count++;
            }
        }
    }

    if(excess>0){
        MPI_Send(&num[n_sent*excess], excess, MPI_INT, 1, 
                 n_sent, MPI_COMM_WORLD);
        n_sent++;

        // Receive the computed results back from the slave
        MPI_Recv(results, excess, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 MPI_COMM_WORLD, &status);

        for(int j=0; j<portion; j++){
            if(results[j]!=0){
                prime_nums[prime_count%n_slave][prime_count/n_slave] = results[j];
                prime_count++;
            }
        }
    }

    // Send all the slave processes STOP signal, (TAG of portion)
    for (int i = 1; i <= n_slave; ++i)
    {
        MPI_Send(num, portion, MPI_INT, i, 
                 portion, MPI_COMM_WORLD);
    }

    for(int i=0; i<(range/2+2); i++){
        if(prime_nums[i%n_slave][i/n_slave]!=0){
            printf("%d ", prime_nums[i%n_slave][i/n_slave]);
        } else {
            break;
        }
    }
    printf("\n");

    free(num);
    free(results);
}

bool is_prime(int num){
    if(num==2){
        return 1;
    } else if(num<=0){
        return 0;
    }
    for(int i=2; i<=ceil(sqrt(num)); i++){
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}

void slave(int n_slave, int range){
    int portion = range/n_slave;
    int *num = (int *) malloc(sizeof(int)*portion);
    int *primes = (int *) calloc(portion, sizeof(int));
    int count = 0;
    int n_recv = 0;

    MPI_Status status;

    // Receive the chunk to calculate from MASTER
    MPI_Recv(num, portion, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    n_recv = status.MPI_TAG;

    while(n_recv<portion){
        for(int i=0; i<portion; i++){
            if(is_prime(num[i])){
                primes[count++] = num[i];
            }

        }
        for(int i=count; i<portion; i++){
            primes[i] = 0;
        }
        count = 0;

        // Send the results back to MASTER, include in TAG the chunk that was calculated
        MPI_Send(primes, portion, MPI_INT, MASTER, n_recv, MPI_COMM_WORLD);

        // Receive the chunk to calculate from MASTER
        MPI_Recv(num, portion, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        n_recv = status.MPI_TAG;
    }

    free(num);
    free(primes);
}

int main (int argc, char* argv[]){
	int range = 1000;
	
    int proc_id; // Process rank
    int n_proc; // Number of processes
    int n_slave; // number of slaves

    // Initialize MPI
    MPI_Init(&argc, &argv);
    
    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    n_slave = n_proc-1;

    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    if (proc_id == 0) {
        master(n_slave, range);
    } else {
        slave(n_slave, range);
    }

    // Required to terminate all MPI processes
    MPI_Finalize();
}