#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

uint tosses_leftover;
uint64_t tosses_per_thread;

uint64_t monteCarloPi(uint world_rank)
{
    uint64_t local_in_circle = 0;
    uint64_t N;
    if(world_rank < tosses_leftover) {
        N = tosses_per_thread + 1;
    } else {
        N = tosses_per_thread;
    }
    uint seed = time(NULL) * world_rank;
    for (uint64_t i = 0; i < N; i += 1) {
        double x = (double) rand_r(&seed) / (double)(RAND_MAX - 1.0);
        double y = (double) rand_r(&seed) / (double)(RAND_MAX - 1.0);
        if (x * x + y * y <= 1.0) {
            local_in_circle++;
        }
    }
    return local_in_circle;
}

int main(int argc, char **argv)
{
    // --- DON'T TOUCH ---
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();
    double pi_result;
    long long int tosses = atoi(argv[1]);
    int world_rank, world_size;
    // ---

    // TODO: MPI init
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    tosses_per_thread = tosses / world_size;
    tosses_leftover = tosses % world_size;
    
    uint64_t local_in_circle = monteCarloPi(world_rank);

    if (world_rank > 0)
    {
        // TODO: MPI workers
        MPI_Send(&local_in_circle, 1, MPI_UNSIGNED_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }
    else if (world_rank == 0)
    {
        // TODO: non-blocking MPI communication.
        // Use MPI_Irecv, MPI_Wait or MPI_Waitall.
        MPI_Request requests[world_size - 1];
        MPI_Status statuses[world_size - 1];
        uint64_t recv_in_circle[world_size - 1];
        for (int i = 1; i < world_size; i++) {
            MPI_Irecv(&recv_in_circle[i - 1], 1, MPI_UNSIGNED_LONG_LONG, i, 0, MPI_COMM_WORLD, &requests[i - 1]);
        }
        MPI_Waitall(world_size - 1, requests, statuses);
        for (int i = 1; i < world_size; i++) {
            local_in_circle += recv_in_circle[i - 1];
        }
    }

    if (world_rank == 0)
    {
        // TODO: PI result
        pi_result = 4.0 * local_in_circle / tosses;
        // --- DON'T TOUCH ---
        double end_time = MPI_Wtime();
        printf("%lf\n", pi_result);
        printf("MPI running time: %lf Seconds\n", end_time - start_time);
        // ---
    }

    MPI_Finalize();
    return 0;
}
