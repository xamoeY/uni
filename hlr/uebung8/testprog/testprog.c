#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank == 0)
        printf("world_size: %d\n", world_size);

    printf("hello from %d\n", my_rank);

    int send_buff[1] = { 1 };
    int recv_buff[1] = { 2 };

    MPI_Request request;
    MPI_Status status;
    MPI_Isend(send_buff, 1, MPI_INT, (my_rank + 1) % 2, 1, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
    MPI_Recv(recv_buff, 1, MPI_INT, (my_rank + 1) % 2, 1, MPI_COMM_WORLD, NULL);
    /*
    int right = (my_rank + 1) % world_size;
    int left = my_rank - 1;
    if (left < 0)
        left = world_size - 1;

    printf("I'm %d, left is %d, right is %d\n", my_rank, left, right);
    MPI_Sendrecv(send_buff, 1, MPI_INT, left, 1,
                 recv_buff, 1, MPI_INT, right, 1,
                 MPI_COMM_WORLD, NULL);
    */

    printf("%d | recv_buff: %d\n", my_rank, recv_buff[0]);

    MPI_Finalize();

    return 0;
}
