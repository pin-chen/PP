#include <stdio.h>
#include <stdlib.h>
#include "hostFE.h"
#include "helper.h"

#define ISCHECK 0
#define BLOCK_SIZE 8
#define RELAX(tmp) (tmp+BLOCK_SIZE-1)/BLOCK_SIZE*BLOCK_SIZE

void hostFE(int filterWidth, float *filter, int imageHeight, int imageWidth,
            float *inputImage, float *outputImage, cl_device_id *device,
            cl_context *context, cl_program *program)
{
    // Set up the OpenCL environment
    cl_int status;
    cl_command_queue commands;
    cl_mem inputImage_mem, filter_mem, outputImage_mem;
    int dataSize = imageWidth * imageHeight * sizeof(float);
    int filterSize = filterWidth * filterWidth * sizeof(float);
    // Declare context in helper
    // cl_context *context
    // Choose a device from context in helper
    // cl_device_id *device
    // Using device and context create a command queue
    commands = clCreateCommandQueue(*context, *device, 0, &status);
#if ISCHECK
    CHECK(status, "clCreateCommandQueue");
#endif
    // Create buffers on device
    inputImage_mem = clCreateBuffer(*context, CL_MEM_READ_ONLY, dataSize, NULL, &status);
#if ISCHECK
    CHECK(status, "clCreateBuffer (inputImage)");
#endif
    filter_mem = clCreateBuffer(*context, CL_MEM_READ_ONLY, filterSize, NULL, &status);
#if ISCHECK
    CHECK(status, "clCreateBuffer (filter)");
#endif
    outputImage_mem = clCreateBuffer(*context, CL_MEM_WRITE_ONLY, dataSize, NULL, &status);
#if ISCHECK
    CHECK(status, "clCreateBuffer (outputImage)");
#endif
    // Transfer input data to the device
    clEnqueueWriteBuffer(commands, inputImage_mem, CL_TRUE, 0, dataSize, inputImage, 0, NULL, NULL);
    clEnqueueWriteBuffer(commands, filter_mem, CL_TRUE, 0, filterSize, filter, 0, NULL, NULL);
    // Create the program & Build the program in helper
    // cl_program *program 
    // Use the "convolution" function as the kernel 
    cl_kernel kernel = clCreateKernel(*program, "convolution", &status);
#if ISCHECK
    CHECK(status, "clCreateKernel");
#endif
    // Set Arguments
    clSetKernelArg(kernel, 0, sizeof(cl_int), (void*)&filterWidth);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&filter_mem);
    clSetKernelArg(kernel, 2, sizeof(cl_int), (void*)&imageHeight);
    clSetKernelArg(kernel, 3, sizeof(cl_int), (void*)&imageWidth);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&inputImage_mem);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&outputImage_mem);
    // Set local and global workgroup sizes
    size_t localws[] = {BLOCK_SIZE, BLOCK_SIZE};
    size_t globalws[] = {RELAX(imageHeight), RELAX(imageWidth)};
    // Execute kernel
    clEnqueueNDRangeKernel(commands, kernel, 2, NULL, globalws, localws, 0, NULL, NULL);
    // Copy results from device back to host
    clEnqueueReadBuffer(commands, outputImage_mem, CL_TRUE, 0, dataSize, outputImage, 0, NULL, NULL);
    // Release
    clReleaseMemObject(inputImage_mem);
    clReleaseMemObject(filter_mem);
    clReleaseMemObject(outputImage_mem);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
}