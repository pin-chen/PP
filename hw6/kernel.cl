__kernel void convolution(const int filterWidth, 
                          __constant float *filter, 
                          const int imageHeight, 
                          const int imageWidth, 
                          __global float *inputImage, 
                          __global float *outputImage)
{
    int halffilterSize = filterWidth / 2;
    float sum = 0.0;
    int i = get_global_id(0);
    int j = get_global_id(1);
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