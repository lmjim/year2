//Author: Lily Jim
//Credit: Starter code from Assignment 1 Prompt
//UO CIS 314 Fall 2018

#include <stdio.h>

void printBytes(unsigned char *start, int len) {
	for (int i = 0; i < len; ++i) {
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void printInt(int x) {
	printBytes((unsigned char *) &x, sizeof(int));
}

void printFloat(float x) {
	printBytes((unsigned char *) &x, sizeof(float));
}


void printShort(short x){
	printBytes((unsigned char *) &x, sizeof(short));
}

void printLong(long x){
	printBytes((unsigned char *) &x, sizeof(long));
}

void printDouble(double x){
	printBytes((unsigned char *) &x, sizeof(double));
}

void main(){
        printInt(5); //prints 4 bytes (trailing 0s)
        printFloat(5.0); //prints 4 bytes (leading 0s)
        printShort(5); //only print 2 bytes (trailing 0s)
        printLong(5); //prints 8 bytes (trailing 0s)
        printDouble(5.0); //prints 8 bytes (leading 0s)
}

