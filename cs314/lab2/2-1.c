//Author: Lily Jim
//UO CIS 314 Fall 2018

#include <stdio.h>

int mask(int n){
	int mask = 1; //This would be 0000 ... 0001 in binary
	mask = mask << n; //This would shift the 1 in binary to the n+1 spot 
			//where you want all the spots behind it to be 1s 
			//(but not this spot itself)
			//ex: 1 << 3 -> 1000 = 8
	mask = mask - 1; //This would change the spot in the binary mask that
			//was a 1 to a 0 and every single spot after that
			//from 0 to 1, ex: 8 - 1 = 7 -> 0111 which is what we want
	printf("0x%X\n", mask);	
	return mask;
}

void main(){
	mask(0);  //0x0
	mask(1);  //0x1
	mask(2);  //0x3
	mask(3);  //0x7
	mask(5);  //0x1F
	mask(8);  //0xFF
	mask(16); //0xFFFF
	mask(31); //0xFFFFFFF
}
