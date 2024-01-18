#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

__global__ void mandelKernel(int* img, float lowerX, float lowerY, float stepX, float stepY, int resX, int resY, int count) {
    int thisX = blockIdx.x * blockDim.x + threadIdx.x;
    int thisY = blockIdx.y * blockDim.y + threadIdx.y;
    if (thisX >= resX || thisY >= resY) return;
    
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

    img[thisX + thisY * resX] = i;
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;

    int size = resX * resY * sizeof(int);
    int* img_d;
    cudaMalloc((void**)&img_d, size);

    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid((int)((float) resX / dimBlock.x + 0.5), (int)((float) resY / dimBlock.y + 0.5));

    mandelKernel<<<dimGrid, dimBlock>>>(img_d, lowerX, lowerY, stepX, stepY, resX, resY, maxIterations);

    cudaDeviceSynchronize();

    cudaMemcpy(img, img_d, size, cudaMemcpyDeviceToHost);

    cudaFree(img_d);
}
