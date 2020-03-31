//Author: Lily Jim
//Credits: Original c code provided by assignment
//UO CIS 314 Fall 2018

/* Original c code:
#define N 4
typedef int array_t[N][N];

int dim() {
	return N;
}

void f(array_t a, int x, int y) {
	for (int i = 0; i < dim(); ++i) {
		for (int j = 0; j < dim(); ++j) {
			a[i][j] = i * x * y + j;
		}
	}
}
*/

#include <stdio.h>

#define N 4
typedef int array_t[N][N];

int dim(){
	return N;
}

void f(array_t a, int x, int y){
	int d = dim(); // Make call to dim() once, since it will always return N
	int xy = x * y; // Multiply x and y once since x and y do not change
	for(int i=0; i < d; i++){
		int z = i * xy; // Multiply xy by i once for each i instead of j times
		for(int j=0; j < d; j++){
			a[i][j] = z + j;
		}
	}
}

void printarray(array_t a){
	// Function to print array
        printf("{{");
        for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                        printf("%d", a[i][j]);
                        if (j == (N - 1)){
                                printf("}");
                        }else{
                                printf(", ");
                        }
                }
                if (i == (N - 1)){
                        printf("}\n");
                }else{
                        printf(", {");
                }
        }
}

void main(){
	array_t array = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
        printarray(array); // Print original array
        f(array, 2, 10);
	printarray(array);
	// Print array after call to f, should be: {{0, 1, 2, 3}, {20, 21, 22, 23}, {40, 41, 42, 43}, {60, 61, 62, 63}}
}

