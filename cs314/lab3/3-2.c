//Author: Lily Jim
//Credit: Assembly code provided to reverse engineer
//UO CIS 314 Fall 2018

#include <stdio.h>

/*
a is in %rdi
b is in %rsi
c is in %rdx
Reverse engineer: (using slide 27 from week 3)
subq %rdx, %rsi         dest = dest - src       =>      b = b - c
imulq %rsi, %rdi        dest = dest * src       =>      a = a * b
salq $63, %rsi          dest = dest << src      =>      b = b << 63
sarq $63, %rsi          dest = dest >> src      =>      b = b >> 63
movq %rdi, %rax         dest = src              =>      new_var1 = a
xorq %rsi, %rax         dest = dest ^ src       =>      new_var1 = new_var1 ^ b
*/

long decode(long a, long b, long c){
	b = b - c; //subtract
	a = a * b; //multiply
	b = b << 63; //shift left
	b = b >> 63; //shift right
	long d = a; //move a into new variable d
	d = d ^ b; //exponential multiplication
	return d; //return new variable
}

void main(){
	printf("%d\n", decode(1, 2, 4)); //-2
	printf("%d\n", decode(3, 5, 7)); //-6
	printf("%d\n", decode(10, 20, 30)); //-100
}

