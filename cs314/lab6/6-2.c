//Author: Lily Jim
//Credits: code for inner function provided, example code for main provided and used
//UO CIS 314 Fall 2018

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inner(float *u, float *v, int length, float *dest){
	int i;
	float sum = 0.0f;
	for(i = 0; i < length; ++i){
		sum += u[i] * v[i];
	}
	*dest = sum;
}

void inner2(float *u, float *v, int length, float *dest){
	int i;
	// Four accumulators: sum, sum1, sum2, sum3
	float sum = 0.0f;
	float sum1 = 0.0f;
	float sum2 = 0.0f;
	float sum3 = 0.0f;
	int limit = length - 3;
	for(i = 0; i < limit; i += 4){ // i+=4 so 4-way loop unrolling
		// Parallel accumulators:
		sum += u[i] * v[i];
		sum1 += u[i+1] * v[i+1];
		sum2 += u[i+2] * v[i+2];
		sum3 += u[i+3] * v[i+3];
	}
	for(; i < length; i++){ // Catch remaining values (up to 3 could be skipped by prior loop)
		sum += u[i] * v[i];
	}
	*dest = sum + sum1 + sum2 + sum3;
}

void main(){
	clock_t start;
	clock_t end;
	double total_time;
	float dest;
	int len = 100;

	float *u = malloc(sizeof(float) * len); // Initialize array u
	float *v = malloc(sizeof(float) * len); // Initialize array v
	for(int i = 0; i < len; i++){
		u[i] = (float) i; // Put values into u
		v[i] = (float) i; // Put values into v
	}

	start = clock();
	inner(u, v, len, &dest); // Run inner
	end = clock();
	total_time = ((double) (end - start)) / CLOCKS_PER_SEC; // Time it takes for inner to complete
	printf("Inner Time: %f\n", total_time); // Print unoptimized time

	start = clock();
	inner2(u, v, len, &dest); // Run inner2
	end = clock();
	total_time = ((double) (end - start)) / CLOCKS_PER_SEC; // Time it takes for inner2 to complete
	printf("Inner2 Time: %f\n", total_time); // Print optimized time

	free(u); // Free array
	free(v); // Free array
}

