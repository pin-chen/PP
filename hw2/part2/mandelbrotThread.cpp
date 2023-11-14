#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include "CycleTimer.h"


float x0_global, y0_global;
//float x1_global, y1_global;
float dx_global, dy_global;
uint width_global;
uint height_global;
int maxIterations_global;
int *output_global;
uint numThreads_global;

typedef struct
{
    //float x0, y0;
    //float x1, y1;
    //float dx, dy;
    //uint width;
    //uint height;
    //int maxIterations;
    //int *output;
    uint threadId;
    //uint numThreads;
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

    // TODO FOR PP STUDENTS: Implement the body of the worker
    // thread here. Each thread could make a call to mandelbrotSerial()
    // to compute a part of the output image. For example, in a
    // program that uses two threads, thread 0 could compute the top
    // half of the image and thread 1 could compute the bottom half.
    // Of course, you can copy mandelbrotSerial() to this file and 
    // modify it to pursue a better performance.

    //printf("Hello world from thread %d\n", args->threadId);

    for (uint j = args->threadId; j < height_global; j += numThreads_global)
    {
        for (uint i = 0; i < width_global; ++i)
        {
            float x = x0_global + i * dx_global;
            float y = y0_global + j * dy_global;

            uint index = (j * width_global + i);
            output_global[index] = mandel_thread(x, y, maxIterations_global);
        }
    }

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
    x0_global = x0;
    y0_global = y0;
    //float x1_global, y1_global;
    dx_global = (x1 - x0) / width;
    dy_global = (y1 - y0) / height;
    width_global = width;
    height_global = height;
    maxIterations_global = maxIterations;
    output_global = output;
    numThreads_global = numThreads;

    for (int i = 0; i < numThreads; i++)
    {
        // TODO FOR PP STUDENTS: You may or may not wish to modify
        // the per-thread arguments here.  The code below copies the
        // same arguments for each thread
        //args[i].x0 = x0;
        //args[i].y0 = y0;
        //args[i].x1 = x1;
        //args[i].y1 = y1;
        //args[i].dx = dx;//
        //args[i].dy = dy;//
        //args[i].width = width;
        //args[i].height = height;
        //args[i].maxIterations = maxIterations;
        //args[i].numThreads = numThreads;
        //args[i].output = output;

        args[i].threadId = i;
    }

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
