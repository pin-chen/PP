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
    
    // TODO: binary tree redunction
    uint64_t recv_in_circle;
    for (int i = 1; i < world_size; i *= 2) {
        //for (int j = 0; j < world_size; j += 2 * i)
        if (world_rank % (2 * i) == 0) {
            MPI_Recv(&recv_in_circle, 1, MPI_UNSIGNED_LONG_LONG, world_rank + i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //printf("%d <-- %d\n", world_rank, world_rank + i);
            local_in_circle += recv_in_circle;
        } else {
            //printf("%d --> %d\n", world_rank, world_rank - i);
            MPI_Send(&local_in_circle, 1, MPI_UNSIGNED_LONG_LONG, world_rank - i, 0, MPI_COMM_WORLD);
            break;
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
