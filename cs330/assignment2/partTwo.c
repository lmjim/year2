#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "clock.h"

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

void initTimer(ClockType *clock, int minutes, int seconds){
}

void runTimer(){
	printf("How long should the timer run (MM:SS)? ");
	int max = 10;
	char input[max];
	fgets(input, max, stdin); // Read input
	int min[2] = {input[0] - '0', input[1] - '0'};
	int sec[2] = {input[3] - '0', input[4] - '0'};
	
	while(1){
		// Print time:
		for(int i=0; i<8; i++){
	                printf("%s%s%s%s%s%s%s\n", digits[min[0]][i], spacer[i], digits[min[1]][i],
	                                colon[i], digits[sec[0]][i], spacer[i], digits[sec[1]][i]);
	        }
		
		// Count down one second:
		if(min[0] == 0 && min[1] == 0 && sec[0] == 0 && sec[1] == 0){
			goto end; // Break while loop
		}
		else if(min[0] != 0 && min[1] == 0 && sec[0] == 0 && sec[1] == 0){
			min[0]--;	// decrement min[0]
			min[1] = 9;	// set min[1] to 9
			sec[0] = 5;	// set sec[0] to 5
			sec[1] = 9;	// set sec[1] to 9
		}
		else if(min[1] != 0 && sec[0] == 0 && sec[1] == 0){
			min[1]--;	// decrement min[1]
			sec[0] = 5;	// set sec[0] to 5
			sec[1] = 9;	// set sec[1] to 9
                }
		else if(sec[0] != 0 && sec[1] == 0){
			sec[0]--;	// decrement sec[0]
			sec[1] = 9;	// set sec[1] to 9
                }
		else{
			sec[1]--;	// decrement sec[1]
		}

		sleep(1);
		printf("---------------------\n");
	}
end:
	return;
}

void cleanTimer(ClockType  *clock){
}

void main(){
	runTimer();
}
