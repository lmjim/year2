//Author: Lily Jim
//Credits: c code and assembly starter code provided
//	Week 4 slides and textbook used as references
//UO CIS 314 Fall 2018

#include <stdio.h>

/* Want assembly code that follows this c code:
int sum(int from, int to) {
	int result = 0;
	do {
		result += from;
		++from;
	} while (from <= to);
	return result;
}
*/

long sum(long from, long to) {
	long result = 0;
	// Ensure that argument *from* is in %rdi,
	// argument *to* is in %rsi, *result* is in %rax - do not modify.
	__asm__ ("movq %0, %%rdi # from in rdi;" :: "r" ( from ));
	__asm__ ("movq %0, %%rsi # to in rsi;" :: "r" ( to ));
	__asm__ ("movq %0, %%rax # result in rax;" :: "r" ( result ));

	// My x86-64 code with comments:
		__asm__(".L2: # Create label for start of loop;");
		__asm__("addq %rdi, %rax # Add 'from' to 'result';");
		__asm__("addq $1, %rdi # Add one to 'from' (increment);");
		__asm__("cmpq %rsi, %rdi # Compare 'from' and 'to';");
		__asm__("jle .L2 # The above compare results in a '<=' comparison, \
				and if true, the loop continues. \
				Jump to start of loop ('.L2') or \
				continue on based on condition codes.;");

	// Ensure that *result* is in %rax for return - do not modify.
	__asm__ ("movq %%rax, %0 #result in rax;" : "=r" ( result ));
	return result;
}

void main(){
	printf("%d\n", sum(1, 6)); //21
	printf("%d\n", sum(3, 5)); //12
}
