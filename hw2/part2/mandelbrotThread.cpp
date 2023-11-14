#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include "CycleTimer.h"

typedef struct
{
    float x0, y0;
    //float x1, y1;
    float dx, dy;
    uint width;
    uint height;
    int maxIterations;
    int *output;
    uint threadId;
    uint numThreads;
} WorkerArgs;

extern void mandelbrotSerial(
    float x0, float y0, float x1, float y1,
    int width, int height,
    int startRow, int numRows,
    int maxIterations,
    int output[]);


//
static inline uint mandel_thread(float c_re, float c_im, uint count)
{
    float z_re = c_re, z_im = c_im;
    uint i;
    for (i = 0; i < count; ++i)
    {
        if (z_re * z_re + z_im * z_im > 4.f)
            break;

        float new_re = z_re * z_re - z_im * z_im;
        float new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;
    }

    return i;
}


//
// workerThreadStart --
//
// Thread entrypoint.
void workerThreadStart(WorkerArgs *const args)
{
    double startTime = CycleTimer::currentSeconds();
    // TODO FOR PP STUDENTS: Implement the body of the worker
    // thread here. Each thread could make a call to mandelbrotSerial()
    // to compute a part of the output image. For example, in a
    // program that uses two threads, thread 0 could compute the top
    // half of the image and thread 1 could compute the bottom half.
    // Of course, you can copy mandelbrotSerial() to this file and 
    // modify it to pursue a better performance.

    //printf("Hello world from thread %d\n", args->threadId);

    uint totalRows_per_thread = args->height / args->numThreads;
    uint totalRows_leftover = args->height % args->numThreads;

    uint startRow, endRow;
    if (args->threadId < totalRows_leftover) {
        startRow = args->threadId * totalRows_per_thread + args->threadId;
        endRow = startRow + totalRows_per_thread + 1;
    } else {
        startRow = args->threadId * totalRows_per_thread + totalRows_leftover;
        endRow = startRow + totalRows_per_thread;
    }

    for (uint j = startRow; j < endRow; j++)
    {
        for (uint i = 0; i < args->width; ++i)
        {
            float x = args->x0 + i * args->dx;
            float y = args->y0 + j * args->dy;

            uint index = (j * args->width + i);
            args->output[index] = mandel_thread(x, y, args->maxIterations);
        }
    }
    double endTime = CycleTimer::currentSeconds();
    printf("ThreadId[%u]:\t\t[%.3f] ms\n", args->threadId, (endTime - startTime) * 1000);
}

//
// MandelbrotThread --
//
// Multi-threaded implementation of mandelbrot set image generation.
// Threads of execution are created by spawning std::threads.
void mandelbrotThread(
    int numThreads,
    float x0, float y0, float x1, float y1,
    int width, int height,
    int maxIterations, int output[])
{
    static constexpr int MAX_THREADS = 32;

    if (numThreads > MAX_THREADS)
    {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    // Creates thread objects that do not yet represent a thread.
    std::thread workers[MAX_THREADS];
    WorkerArgs args[MAX_THREADS];
    
    // 
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

    for (int i = 0; i < numThreads; i++)
    {
        // TODO FOR PP STUDENTS: You may or may not wish to modify
        // the per-thread arguments here.  The code below copies the
        // same arguments for each thread
        args[i].x0 = x0;
        args[i].y0 = y0;
        //args[i].x1 = x1;
        //args[i].y1 = y1;
        args[i].dx = dx;//
        args[i].dy = dy;//
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].numThreads = numThreads;
        args[i].output = output;

        args[i].threadId = i;
    }


    printf("--------------------------------------\n");
    // Spawn the worker threads.  Note that only numThreads-1 std::threads
    // are created and the main application thread is used as a worker
    // as well.
    for (int i = 1; i < numThreads; i++)
    {
        workers[i] = std::thread(workerThreadStart, &args[i]);
    }

    workerThreadStart(&args[0]);

    // join worker threads
    for (int i = 1; i < numThreads; i++)
    {
        workers[i].join();
    }
}
