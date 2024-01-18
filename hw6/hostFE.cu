__global__ void convolution(int filterWidth, float *filter, int imageHeight, int imageWidth, float *inputImage, float *outputImage)
{
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    int halffilterSize = filterWidth / 2;
    float sum = 0.0f;
    int k, l;
    int outer_begin = i - halffilterSize >= 0 ? -halffilterSize : -i;
    int outer_end = i + halffilterSize < imageHeight ? halffilterSize : imageHeight - i - 1;
    int inner_begin = j - halffilterSize >= 0 ? -halffilterSize : -j;
    int inner_end = j + halffilterSize < imageWidth ? halffilterSize : imageWidth - j - 1;
    for (k = outer_begin; k <= outer_end; k++)
    {
        for (l = inner_begin; l <= inner_end; l++)
        {
            sum += inputImage[(i + k) * imageWidth + j + l] *
                    filter[(k + halffilterSize) * filterWidth +
                            l + halffilterSize];
        }
    }
    outputImage[i * imageWidth + j] = sum;
}


extern "C" void hostFE(int filterWidth, float *filter, int imageHeight, int imageWidth,
                       float *inputImage, float *outputImage)
{
    float *filter_mem, *inputImage_mem, *outputImage_mem;
    int filterSize = filterWidth * filterWidth * sizeof(float);
    int dataSize = imageHeight * imageWidth * sizeof(float);

    cudaMalloc(&filter_mem, filterSize);
    cudaMalloc(&inputImage_mem, dataSize);
    cudaMalloc(&outputImage_mem, dataSize);

    cudaMemcpy(filter_mem, filter, filterSize, cudaMemcpyHostToDevice);
    cudaMemcpy(inputImage_mem, inputImage, dataSize, cudaMemcpyHostToDevice);

    int block_size = 16;

    dim3 dimBlock(block_size, block_size);
    dim3 dimGrid(imageWidth / block_size, imageHeight / block_size);

    convolution<<<dimBlock, dimGrid>>>(filterWidth, filter_mem, imageHeight, imageWidth, inputImage_mem, outputImage_mem);
    
    cudaMemcpy(outputImage, outputImage_mem, dataSize, cudaMemcpyDeviceToHost);
    
    cudaFree(outputImage_mem);
    cudaFree(inputImage_mem);
    cudaFree(filter_mem);
}