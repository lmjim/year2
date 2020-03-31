#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "timer.h"

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

void initTimer(ClockType *clock, int minutes, int seconds){
	// This function is not used
	return;
}

void runTimer(){
        printf("How long should the timer run (MM:SS)? "); // Ask for input
        int max = 10;
        char input[max];
        fgets(input, max, stdin); // Read input
	// Note: there is no checking if the input is what is expected (format wise)
        int min[2] = {input[0] - '0', input[1] - '0'}; // Convert minute input
        int sec[2] = {input[3] - '0', input[4] - '0'}; // Convert second input

        while(1){
                // Print time/clock:
                for(int i=0; i<8; i++){
                        printf("%s%s%s%s%s%s%s\n", digits[min[0]][i], spacer[i], digits[min[1]][i],
                                        colon[i], digits[sec[0]][i], spacer[i], digits[sec[1]][i]);
                }

                // Count down one second:
                if(min[0] == 0 && min[1] == 0 && sec[0] == 0 && sec[1] == 0){
                        goto end; // Break while loop
                }
                else if(min[0] != 0 && min[1] == 0 && sec[0] == 0 && sec[1] == 0){
                        min[0]--;       // decrement min[0]
                        min[1] = 9;     // set min[1] to 9
                        sec[0] = 5;     // set sec[0] to 5
                        sec[1] = 9;     // set sec[1] to 9
                }
                else if(min[1] != 0 && sec[0] == 0 && sec[1] == 0){
                        min[1]--;       // decrement min[1]
                        sec[0] = 5;     // set sec[0] to 5
                        sec[1] = 9;     // set sec[1] to 9
                }
                else if(sec[0] != 0 && sec[1] == 0){
                        sec[0]--;       // decrement sec[0]
                        sec[1] = 9;     // set sec[1] to 9
                }
                else{
                        sec[1]--;       // decrement sec[1]
                }

                sleep(1); // Wait one second
                printf("---------------------\n"); // Print separater between clocks
        }
end:
        return;
}

void cleanTimer(ClockType  *clock){
	// This function is not used
	return;
}

