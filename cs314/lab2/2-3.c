//Author: Lily Jim
//UO CIS 314 Fall 2018

#include <stdio.h>

int ge(float x, float y) {
	unsigned int ux = *((unsigned int*) &x); // convert x raw bits
	unsigned int uy = *((unsigned int*) &y); // convert y raw bits
	unsigned int sx = ux >> 31; // extract sign bit of ux
	unsigned int sy = uy >> 31; // extract sign bit of uy
	ux <<= 1; // drop sign bit of ux
	uy <<= 1; // drop sign bit of uy

	//or together every condition that should return 1:
	//when x is positive and y is negative
	//when both are positive and x is still greater or equal
	//when both are negative and x is still greater or equal
	//when both are zero
	int condition = ((sx==0 && sy==1) || (sx==0 && sy==0 && ux>=uy) || (sx==1 && sy==1 && ux>=uy) || (ux==0 && uy==0));
	printf("%d\n", condition);
	return condition;
}

void main(){
	ge(0.0f, 0.0f);  //1
	ge(-0.0f, 0.0f); //1
	ge(-1.0f, 0.0f); //0
	ge(0.0f, 1.0f);  //0
	ge(1.0f, 0.0f);  //1
	ge(0.0f, -1.0f); //1
}

