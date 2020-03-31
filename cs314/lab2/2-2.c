//Author: Lily Jim
//UO CIS 314 Fall 2018

#include <stdio.h>

unsigned int extract(unsigned int x, int i){
	int shift = 3 - i; //this is the number of bytes you want to shift x by
			//to get the most significant byte to be what you are trying to preserve
	shift = shift << 3; //this is the number in bits to shift x by
	x = x << shift;

	signed int z = (signed) x; //this needs to be signed so when you shift it
				//to the right it will fill in with either 1s or 0s
				//this correlates with the "signed" bit 1 or 0
	z = z >> 24; //this shifts the byte we want to keep to the least significant place
	x = (unsigned) z; //this returns the int to unsigned

	printf("%#010x\n", x);
	
	return x;
}

void main(){
	extract(0x12345678, 0); //0x00000078
	extract(0xABCDEF00, 2); //0xFFFFFFCD
}

