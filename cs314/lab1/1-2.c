//Author: Lily Jim
//Credits: Lab Instructor helped with steps needed
//UO CIS 314 Fall 2018

#include <stdio.h>

//x=12345678, y=0xABCDEF00
//z=1234EF00, bytes 3 and 2 from x and bytes 1 and 0 from y
//want x = 0x12340000 and y = 0x0000EF00
//x =    0001 0010 0011 0100 0101 0110 0111 1000
//mask = 1111 1111 1111 1111 0000 0000 0000 0000 = FFFF0000
//x&mask=0001 0010 0011 0100 0000 0000 0000 0000 = 12340000
//y =    
//mask = 0000 0000 0000 0000 1111 1111 1111 1111
//y&mask=0000 0000 0000 0000 1110 1111 0000 0000 = 0000EF00
//x|y  = 0001 0010 0110 0100 1110 1111 0000 0000 = 1234EF00

unsigned int combine(unsigned int x, unsigned int y){
	unsigned int x2 = x & 0xFFFF0000;
	unsigned int y2 = y & 0x0000FFFF;
	unsigned int xy = x2 | y2;
	printf("%X\n", xy);
	return xy;
}

void main(){
        combine(0x12345678, 0xABCDEF00);
        combine(0xABCDEF00, 0x12345678);
}

