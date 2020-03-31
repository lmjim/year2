//Author: Lily Jim
//Credits: Lab Instructor helped with steps needed
//UO CIS 314 Fall 2018

#include <stdio.h>

//x=0x12345678, i=2, b=0xAB
//0001 0010 0011 0100 0101 0110 0111 1000
//            ^    ^                       is what we want to replace
//Want to replace 34 in x
//Set up mask as 0xFF
//i << 3 when i = 2 -> 00010000 = 16
//Shift mask over 16 places (i.e. the new i)
//Mask =            0000 0000 1111 1111 0000 0000 0000 0000
//~mask =           1111 1111 0000 0000 1111 1111 1111 1111
//x & ~mask =       0001 0010 0000 0000 0101 0110 0111 1000 = 0x12005678
//Byte 2 is now removed
//b=0xAB << 16 (the new i)
//new b =           0000 0000 1010 1011 0000 0000 0000 0000
//new b | x&~mask = 0001 0010 1010 1011 0101 0110 0111 1000 = 0x12AB5678

unsigned int replace(unsigned int x, int i, unsigned char b){
	int i2 = i << 3;
	int mask = 0xFF << i2;
	int not_mask = ~mask;
	unsigned int x2 = x & not_mask;
	unsigned int b2 = b << i2;
	unsigned int xb = x2 | b2;
	printf("%X\n", xb);
	return xb;
}

void main(){
	replace(0x12345678, 2, 0xAB);
	replace(0x12345678, 0, 0xAB);
}
