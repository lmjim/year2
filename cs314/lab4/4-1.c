//Author: Lily Jim
//Credits: Starter code and x86-64 code provided by assignment
//	Week 4 slides and textbook used as references
//UO CIS 314 Fall 2018

#include <stdio.h>

/* x86-64 code annotated:
loop:				// Label 'loop' (name of function)
	movq %rsi, %rcx		// Move 'b' into a new variable
	movl $1, %edx		// Initialize 'mask' equal to 1
	movl $0, %eax		// Initialize 'result' equal to 0
.L2:				// Label '.L2' (start of for loop)
	testq %rdx, %rdx	// Condition for the for loop
	je .L4			// Jump to .L4 (exit loop) if ZF is set (mask == 0)
	movq %rdx, %r8		// Move 'mask' into a new variable
	andq %rdi, %r8		// The new variable becomes itself & 'a'
	orq %r8, %rax		// 'result' becomes itself | new_variable
	salq %cl, %rdx		// For loop update expression: 'mask' shifts left by the variable containing 'b'
	jmp .L2			// Jump back to label '.L2' (beginning of for loop)
.L4:				// Label '.L4' (end of for loop)
	ret			// Return 'result'
*/

// The following c code creates the above x86-64 code
// It is broken down into multiple lines to exemplify 
// which lines of the x86-64 code match up with the c code
long loop(long a, long b) {
	long shift = b;		// Move b into a new variable (shift)
	long mask = 1;		// Initialize mask to 1
	long result = 0;	// Initialize result to 0
	for (mask; mask != 0; mask <<= shift) { // Update expression (shift mask left), and compare mask to 0 (continue or end loop)
		long temp = mask; // Move mask into a new variable (temp)
		temp = temp & a; // & temp and a
		result = result | temp; // | result and temp
	}
	return result; // return result
}


/* The above c code can be condensed into the following and maintain the same x86-64 code:

long loop(long a, long b){
	long result = 0;
	for (long mask = 1; mask != 0; mask <<= b){
		result |= (mask & a);
	}
	return result;
}

*/

void main(){
	printf("%d\n", loop(1, 5)); //1
	printf("%d\n", loop(2, 4)); //0
	printf("%d\n", loop(3, 3)); //1
	printf("%d\n", loop(4, 2)); //4
	printf("%d\n", loop(5, 1)); //5
}
