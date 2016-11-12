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

__global__ void kernel(float* u, float* v) {

	int i = blockIdx.x * blockDim.x + threadIdx.x;

	for (int k = 0; k < kend; k++) {
		if (i > 0 && i < N - 1) {
			u[i] = ((u[i - 1] + u[i + 1]) / 2);
		}
		v[N*k + i] = u[i];
	}
}

int main() {
	num_t *u, *uDev, *v, *vDev;
	int size1 = N * sizeof(num_t);
	int size2 = 30000;
	
	//initialization of dev_a and dev_b
	cudaMalloc((void**)&uDev, size1);
	cudaMalloc((void**)&vDev, size2);
	a = (num_t *)malloc(size1);
	v = (num_t *)malloc(size2);

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

	cudaMemcpy(dev_b, dev_a, size, cudaMemcpyHostToDevice);
	int dimThreads = N / THREADS_PER_BLOCK;
	int dimBlock = N / dimThreads;
	kernel << <dimBlock, dimThreads >> > (uDev, vDev);
	cudaMemcpy(v, vDev, size2, cudaMemcpyDeviceToHost);


	//print vector to console
	for (int j = 0; j<N; j++) {
		printf(" %g", dev_a[j]);
	}

	//release memory
	free(u);
	free(v);
	cudaFree(uDev);
	cudaFree(vDev);
	_getch();
	return 0;

	


}
