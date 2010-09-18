
#include <cuda/cuda.h>
#include <cuda_runtime.h>

// Device kernel
__global__ void
helloWorld(char* str)
{
    // determine where in the thread grid we are
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    // unmangle output
    str[idx] += idx;
}
