// lapDiff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <time.h>
#define SIZEOFARRAY 10

// The function fillArray is in the file simple.cu
extern void fillArray(int *a, int size);

int main()
{
 clock_t start, diff;
  // Declare the array and initialize to 0
   float initialTemperature[SIZEOFARRAY];
	float temperatureAfterTimeX[SIZEOFARRAY];
	int i;
	for (i = 0; i <= SIZEOFARRAY + 1; i++) {
		if (i == 0) {
			initialTemperature[i] = 100;
			temperatureAfterTimeX[i] = 100;
		}
		else {
			initialTemperature[i] = 23;
			temperatureAfterTimeX[i] = 23;
		}
	}

	int time = 0;

	start = clock();
	//Perform algorithm with timing
	//for (int i = 0; i <= time; i++) {
	while (temperatureAfterTimeX[2] < 95) {
		for (int j = 1; j < SIZEOFARRAY; j++) {
			temperatureAfterTimeX[j] = (((temperatureAfterTimeX[j - 1]) + temperatureAfterTimeX[j + 1]) / 2);
		}
		time++;
	}
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;

	// Print the initial array
	printf("Current state of array after time:\n");
	for (i = 0; i <= SIZEOFARRAY; i++) {
		printf("%.2f ", temperatureAfterTimeX[i]);
	}
	printf("\n");
	printf("Time Value: %d", time);
	printf("Time taken %d seconds %d milliseconds", msec / 1000, msec % 1000);

	// Call the function that will call the GPU function
	//fillArray(a, SIZEOFARRAY);

	//hold for windows console output
	getchar();


    return 0;
}

