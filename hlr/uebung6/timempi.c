#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define LEN 100
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char string_buffer[LEN];
    char* rbuf = NULL;
    if(world_rank == 0)
        rbuf = malloc(world_size * LEN * sizeof(char));

    // Get the name of the processor
    char processor_name[50];
    int name_len = 50;
    if(gethostname(processor_name, name_len) != 0) {
        printf("Error with hostname");
        exit(1);
    }

    // Get current time on host
    struct timeval time;
    if(gettimeofday(&time, NULL) != 0) {
        printf("Error with time");
        exit(1);
    }

    // Generate output
    time_t curtime = time.tv_sec;
    char time_buffer[30];
    strftime(time_buffer, 30, "%Y-%m-%d %T.", localtime(&curtime));
    sprintf(string_buffer, "%s: %s%li", processor_name, time_buffer, time.tv_usec);

    // Gather output
    int rc = MPI_Gather(string_buffer, LEN, MPI_CHAR, rbuf, LEN, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rc != MPI_SUCCESS) {
        printf("Error while gathering, rc is: %d", rc);
        exit(1);
    }

    // Print output
    if(world_rank == 0) {
        for(int i = 0; i < world_size; ++i)
            printf("%.*s\n", LEN, rbuf + LEN * i);
    }

    if(MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS){
        printf("Error with barrier");
        exit(1);
    }

    printf("Rang %d beendet jetzt!\n", world_rank);
	
    // Finalize the MPI environment.
    MPI_Finalize();

}
