//Author: Lily Jim
//Credits: Lab Instructor helped with steps needed
//UO CIS 314 Fall 2018

#include <stdio.h>

//x =     1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF
//mask =  1010 1010 1010 1010 1010 1010 1010 1010 = 0xAAAAAAAA
//x&mask= 1010 1010 1010 1010 1010 1010 1010 1010
//x = (2) 		!!(0) -> !(0) = 1
//!!(2) = 1			 !(1) = 0
//!(2) = 0
//!(0) = 1

int oddBit(unsigned int x){
	unsigned int mask = 0xAAAAAAAA;
	unsigned int x2 = !!(x & mask);
	printf("%X\n", x2);
	return x2;
}

void main(){
	oddBit(0x1);
	oddBit(0x2);
	oddBit(0x3);
	oddBit(0x4);
	oddBit(0xFFFFFFFF);
	oddBit(0xAAAAAAAA);
	oddBit(0x55555555);
}

