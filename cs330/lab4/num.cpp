#include <iostream>

int main(int argc, char **argv) {
	int **num = nullptr;;
	int size = 5, i, j;

	// Allocate memory for 2-D int array
	num = new int * [5];
	for (i = 0; i < size; i++){
		num[i] = new int[5];
		// Set values
		for (j = 0; j < size; j++)
			num[i][j] = i * size + j;
	}

	// Print values
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			std::cout << num[i][j];
		}
		std::cout << std::endl;
	}

	// Deallocate memory
	for (i = 0; i < size; i++){
		delete [] num[i];
	}
	delete [] num;
}
