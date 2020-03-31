#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
	char colon[8][4] ={
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

typedef struct{
	// TODO
} ClockType;

void initClock( ClockType *clock ){
	// TODO
	return;
}

void cleanClock( ClockType *clock){
        // TODO
	return;
}

void printClock(const time_t cur_time, const ClockType *clock){
        char *time = ctime(&cur_time);
        printf("The hour is %c%c\n", time[11], time[12]);

	//char *digitOne = &digits[time[11]][0][0];
	for(int i=0; i<8; i++){
		printf("%s%s%s%s%s%s%s%s%s%s%s\n", digits[time[11] - '0'][i], spacer[i], digits[time[12] - '0'][i],
				colon[i], digits[time[14] - '0'][i], spacer[i], digits[time[15] - '0'][i],
				colon[i], digits[time[17] - '0'][i], spacer[i], digits[time[18] - '0'][i]);
	}
        return;
}

void main(){
        time_t cur_time;
        time(&cur_time);
        ClockType *clock;
        initClock(clock);
        printClock(cur_time, clock);
        cleanClock(clock);
        return;
}

