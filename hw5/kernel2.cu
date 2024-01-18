#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

__global__ void mandelKernel(int* img, float lowerX, float lowerY, float stepX, float stepY, int resX, int resY, int count, size_t pitch) {
    int thisX = blockIdx.x * blockDim.x + threadIdx.x;
    int thisY = blockIdx.y * blockDim.y + threadIdx.y;
    if (thisX >= resX || thisY >= resY) return;
    // To avoid error caused by the floating number, use the following pseudo code
    //
    float c_re = lowerX + thisX * stepX;
    float c_im = lowerY + thisY * stepY;

    float z_re = c_re, z_im = c_im;
    int i;
    for (i = 0; i < count; ++i)
    {
        if (z_re * z_re + z_im * z_im > 4.f)
            break;

        float new_re = z_re * z_re - z_im * z_im;
        float new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;
    }

    ((int*)((int8_t*) img + thisY * pitch))[thisX] = i;
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;

    int size_h = resX * resY * sizeof(int);
    int size_d = resX * sizeof(int);
    int* img_h;
    int* img_d;
    size_t pitch;

    cudaHostAlloc(&img_h, size_h, cudaHostAllocDefault);
    cudaMallocPitch(&img_d, &pitch, size_d, resY);

    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid((int)((float) resX / dimBlock.x + 0.5), (int)((float) resY / dimBlock.y + 0.5));

    mandelKernel<<<dimGrid, dimBlock>>>(img_d, lowerX, lowerY, stepX, stepY, resX, resY, maxIterations, pitch);

    cudaDeviceSynchronize();

    cudaMemcpy2D(img_h, size_d, img_d, pitch, size_d, resY, cudaMemcpyDeviceToHost);
    cudaMemcpy(img, img_h, size_h, cudaMemcpyHostToHost);

    cudaFreeHost(img_h);
    cudaFree(img_d);
}
