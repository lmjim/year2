//Author: Lily Jim
//Credits: 'struct IntArray' code provided
//	fgets reference: https://www.geeksforgeeks.org/fgets-gets-c-language/
//	strtol reference: https://www.geeksforgeeks.org/strtol-function-in-c-stl/
//		and https://stackoverflow.com/questions/14794079/basics-of-strtol
//	Reference for using pointers: http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Pointers.html
//	Reference for selection sort: https://i.stack.imgur.com/1SKb2.jpg
//UO CIS 314 Fall 2018

#include <stdio.h>
#include <stdlib.h>

struct IntArray {
	int length;
	int *dataPtr;
};

struct IntArray* mallocIntArray(int length){
	//lab hints used for this function
	struct IntArray *ptr = malloc(sizeof(struct IntArray));
	ptr->length = length; //Set IntArray length to length passed into function
	ptr->dataPtr = malloc(length * sizeof(int)); //Set IntArray dataPtr to an int array of size length
	return ptr; //return the ptr to the created IntArray
}

void freeIntArray(struct IntArray *arrayPtr){
	free(arrayPtr->dataPtr); //free IntArray's dataPtr
	free(arrayPtr); //free IntArray pointer
}

void readIntArray(struct IntArray *array){
	for(int i = 0; i < (array->length); i++){ //for each spot in the array
		int entry;
		int valid = 0;
		while(valid != 1){
	                printf("Enter int: "); //ask for input
	                int max = 15;
	                char input[max];
	                fgets(input, max, stdin); //read input
	                char *end;
	                entry = strtol(input, &end, 10); //convert input
	                if(input == end){ //check validity
	                        printf("Invalid input\n");
	                }
	                else{
	                        valid = 1;
	                }
		}
		array->dataPtr[i] = entry; //add the entry into the array
	}
}

void swap(int *xp, int *yp){
	int min = *yp; //store value that yp points at
	*yp = *xp; //change value yp points at to the value xp points at
	*xp = min; //change value xp points at to the value stored in min
}

void sortIntArray(struct IntArray *array){
	for(int i=0; i < array->length; i++){ //for each entry in the array
		int min = array->dataPtr[i]; //set original min value as the current entry
		int min_location = i; //record the location in the array of the min value
		for(int j = i+1; j < array->length; j++){ //for each entry in the array following the entry you're looking at
			if(array->dataPtr[j] < min){ //compare entry to min
				min = array->dataPtr[j]; //set the new min value
				min_location = j; //set the new min location
			}
		}
		if(min_location != i){ //if the min is different from the current entry, swap them
			swap(&(array->dataPtr[i]), &(array->dataPtr[min_location])); //use & (address-of) to set pointers and pass pointers into swap()
		}
	}
}

void printIntArray(struct IntArray *array){
	printf("[ "); //print the notation for the start of an array
	for(int i=0; i < array->length; i++){
		printf("%d", array->dataPtr[i]); //print the next entry
		if(i < (array->length) - 1){
			printf(", "); //add a comma and space if there are more entries to go
		}
	}
	printf(" ]\n"); //print the notation for the end of an array
}

int main(){
	int valid = 0;
	long length;
	while(valid != 1){
		printf("Enter length: "); //ask for input
	        int max = 15;
	        char input[max];
	        fgets(input, max, stdin); //read input
		char *end;
		length = strtol(input, &end, 10); //convert input from string to long
		if(input == end){
			printf("Invalid input\n"); //there wasn't a number at the beginning of the input
		}
		else{
			valid = 1;
		}
	}
	struct IntArray *array = mallocIntArray(length);
	readIntArray(array);
	sortIntArray(array);
	printIntArray(array);
	freeIntArray(array);
	return 0;
}

