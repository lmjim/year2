//Author: Lily Jim
//Credits:
// references for ctime: https://www.tutorialspoint.com/c_standard_library/c_function_ctime.htm
// 			 https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rtref/ctime.htm
//UO CIS330 Winter 2019

#include <stdio.h>
#include <time.h>
#include "clock.h"

// Global variables: digits, colon, spacer
char digits[10][8][5] = {
	{{"****"},
        {"*  *"},
        {"*  *"},
        {"*  *"},
        {"*  *"},
        {"*  *"},
        {"*  *"},
        {"****"}},

	{{"  * "},
        {" ** "},
        {"* * "},
        {"  * "},
        {"  * "},
        {"  * "},
        {"  * "},
        {"****"}},

	{{" ** "},
        {"*  *"},
        {"   *"},
        {"   *"},
        {"  * "},
        {" *  "},
        {"*   "},
        {"****"}},

	{{" ** "},
        {"*  *"},
        {"   *"},
        {" ** "},
        {"  **"},
        {"   *"},
        {"*  *"},
        {" ** "}},

	{{"*  *"},
        {"*  *"},
        {"*  *"},
        {"****"},
        {"   *"},
        {"   *"},
        {"   *"},
        {"   *"}},

	{{"****"},
        {"*   "},
        {"*   "},
        {"****"},
        {"   *"},
        {"   *"},
        {"   *"},
        {"****"}},

	{{"****"},
        {"*   "},
        {"*   "},
        {"****"},
        {"*  *"},
        {"*  *"},
        {"*  *"},
        {"****"}},

	{{"*** "},
        {"  * "},
        {"  * "},
        {" ***"},
        {"  * "},
        {"  * "},
        {"  * "},
        {"  * "}},

	{{"****"},
        {"*  *"},
        {"*  *"},
        {"****"},
        {"*  *"},
        {"*  *"},
        {"*  *"},
        {"****"}},

	{{"****"},
        {"*  *"},
        {"*  *"},
        {"****"},
        {"   *"},
        {"   *"},
        {"   *"},
        {"****"}}
};

char colon[8][4] = {
	{"   "},
        {"   "},
        {" * "},
        {"   "},
        {" * "},
        {"   "},
        {"   "},
        {"   "}
};

char spacer[8][2] = {
	{" "},
	{" "},
	{" "},
	{" "},
	{" "},
	{" "},
	{" "},
	{" "},
};

void initClock( ClockType *clock ){
	// This function is not used
	return;
}

void printClock( const time_t cur_time, const ClockType *clock ){
	char *time = ctime(&cur_time);

	for(int i=0; i<8; i++){
		// Prints the first line of each digit on the same line
		// and goes until the last line, creating the full digits next to each other (horizontally)
		printf("%s%s%s%s%s%s%s%s%s%s%s\n", digits[time[11] - '0'][i], spacer[i], digits[time[12] - '0'][i],
				colon[i], digits[time[14] - '0'][i], spacer[i], digits[time[15] - '0'][i],
				colon[i], digits[time[17] - '0'][i], spacer[i], digits[time[18] - '0'][i]);
	}

        return;
}

void cleanClock( ClockType *clock){
	// This function is not used
	return;
}
