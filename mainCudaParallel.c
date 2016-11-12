#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//used for high precision data
#define num_t float
//N equaled to vector size
#define N 1024
#define THREADS_PER_BLOCK 1024

__global__ void kernel(float* u) {

	int i = blockIdx.x * blockDim.x + threadIdx.x;

	if (i > 0 && i < N - 1) {
		u[i] = ((u[i - 1] + u[i + 1]) / 2);
	}
}

int main() {
	num_t *dev_a, *dev_b;
	int size = N * sizeof(num_t);
	int time = 30000;
	
	//initialization of dev_a and dev_b
	cudaMalloc((void**)&dev_a, size);
	cudaMalloc((void**)&dev_b, size);
	dev_a = (num_t *)malloc(size);

	//initial condition
	//first element is subjected to boiling water where the heat is highest
	//all other elements set initially to room temp.
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			dev_a[i] = 100;
		}
		else {
			dev_a[i] = 23;
		}
	}

	int dimThreads = N / THREADS_PER_BLOCK;
	int dimBlock = N / dimThreads;

	//compute the heat equation by sending a copy of the vector to the kernal
	//   at each iteration < time
	for (int k = 0; k < time; k++) {
		cudaMemcpy(dev_b, dev_a, size, cudaMemcpyHostToDevice);
		kernel << <dimBlock, dimThreads >> > (dev_b);
		cudaMemcpy(dev_a, dev_b, size, cudaMemcpyDeviceToHost);
	}

	//print vector to console
	for (int j = 0; j<N; j++) {
		printf(" %g", dev_a[j]);
	}

	//release memory
	free(dev_a);
	cudaFree(dev_b);
	_getch();
	return 0;

	


}
