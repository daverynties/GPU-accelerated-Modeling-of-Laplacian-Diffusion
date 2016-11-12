#
include "cuda_runtime.h"#
include "device_launch_parameters.h"#
include < stdio.h > #include < stdlib.h > #include < conio.h > #define num_t float# define N 1024# define THREADS_PER_BLOCK 1024

__global__ void kernel(float * u) {

  int i = blockIdx.x * blockDim.x + threadIdx.x;

  if (i > 0 && i < N - 1) {
    u[i] = ((u[i - 1] + u[i + 1]) / 2);
  }
}

int main() {
  num_t * dev_a, * dev_b;
  int size = N * sizeof(num_t);
  int time = 30000;

  cudaMalloc((void * * ) & dev_a, size);
  cudaMalloc((void * * ) & dev_b, size);
  dev_a = (num_t * ) malloc(size);

  //initial condition
  for (int i = 0; i < N; i++) {
    if (i == 0) {
      dev_a[i] = 100;
    } else {
      dev_a[i] = 23;
    }
  }

  int dimThreads = N / THREADS_PER_BLOCK;
  int dimBlock = N / dimThreads;
  for (int k = 0; k < time; k++) {
    cudaMemcpy(dev_b, dev_a, size, cudaMemcpyHostToDevice);
    kernel << < dimBlock, dimThreads >> > (dev_b);
    cudaMemcpy(dev_a, dev_b, size, cudaMemcpyDeviceToHost);
  }

  for (int j = 0; j < N; j++) {
    printf(" %g", dev_a[j]);
  }

  free(dev_a);
  cudaFree(dev_b);
  _getch();
  return 0;

}