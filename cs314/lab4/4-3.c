//Author: Lily Jim
//Credits: original c code and x86-64 code provided in assignment
//UO CIS 314 Fall 2018

#include <stdio.h>
#define N 4
typedef long array_t[N][N];

// Function to print nested array:
void printarray(array_t a){
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

// Original c code (+print):
void transpose_original(array_t a){
	for (long i = 0; i < N; ++i) {
		for (long j = 0; j < i; ++j) {
			long t1 = a[i][j];
			long t2 = a[j][i];
			a[i][j] = t2;
			a[j][i] = t1;
		}
	}
	printarray(a);
}

/* x86-64 code to annotate:
***Note: Eric said to leave my annotations on the old version of the assignment***
rdi=a, rsi=i, rdx=col, rcx=j, r8=t2, r9=t1, rax=row

.L3:				// Label (start of loop)
	cmpq %rcx, %rsi		// Compare i and j
	jle .L7			// Jump to .L7 (exit loop) if i <= j (i.e. continue loop if j < i)
	movq (%rdx), %r9	// Move value col points at into t1
	movq (%rax), %r8	// Move value row points at into t2
	movq %r9, (%rax)	// Move t2 into the place row points at
	movq %r8, (%rdx)	// Move t1 into the place col points at
	addq $8, %rax		// Add 8 to row pointer (change index pointer is pointing at)
	addq $32, %rdx		// Add 32 to col pointer (change index pointer is pointing at)
	addq $1, %rcx		// Add 1 to j
	jmp .L3			// Jump to .L3 (start of loop)
*/

// Optimized c code:
void transpose(array_t a){
	for(long i = 0; i < N; ++i){
		long *row = &a[i][0]; // set row pointer to ith row and 0th column
                long *col = &a[0][i]; // set col pointer to 0th row and ith column
		for(long j = 0; j < i; ++j){
			long t1 = *col; // set value col is pointing at to t1
			long t2 = *row; // set value row is pointing at to t2
			*row = t1; // swap
			*col = t2; // swap 
			row += 1; // point at next element in row
			col += N; // point at next element in col
		}
	}
	printarray(a);
}


void main(){
	array_t array = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	printarray(array);
	transpose(array);
	//{{1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15}, {4, 8, 12, 16}}
}
