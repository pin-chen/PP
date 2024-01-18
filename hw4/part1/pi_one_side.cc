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

    MPI_Win win;

    // TODO: MPI init
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    tosses_per_thread = tosses / world_size;
    tosses_leftover = tosses % world_size;
    
    uint64_t local_in_circle = monteCarloPi(world_rank);
    
    if (world_rank == 0)
    {
        // Master
        MPI_Win_create(&local_in_circle, sizeof(uint64_t), sizeof(uint64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
        MPI_Win_fence(0, win);
        MPI_Win_fence(0, win);
        MPI_Win_free(&win);
    }
    else
    {
        // Workers
        MPI_Win_create(NULL, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
        MPI_Win_fence(0, win);
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, win);
        MPI_Accumulate(&local_in_circle, 1, MPI_UNSIGNED_LONG_LONG, 0, 0, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, win);
        MPI_Win_unlock(0, win);
        MPI_Win_fence(0, win);
        MPI_Win_free(&win);
    }

    if (world_rank == 0)
    {
        // TODO: handle PI result
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