#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	char **array;
} ClockType;

void initClock( ClockType *clock ){
        clock->array = (char **)malloc(8 * sizeof(char*));
	for(int i=0; i<8; i++){
		(clock->array)[i] = (char *)malloc(4 * sizeof(char));
	}
}

void cleanClock( ClockType *clock){
        for(int i=0; i<8; i++){
		free((clock->array)[i]);
	}
	free(clock->array);
}

/*char * getDigit(char num){
	char zero[8][4] = {{"****"},
                {"*  *"},
                {"*  *"},
                {"*  *"},
                {"*  *"},
                {"*  *"},
                {"*  *"},
                {"****"}};
}*/

void printClock(const time_t cur_time, const ClockType *clock){
	char colon[8][4] = {{"   "},
                {"   "},
                {" * "},
                {"   "},
                {" * "},
                {"   "},
                {"   "},
                {"   "}};

        char *time = ctime(&cur_time);
        printf("The hour is %c%c\n", time[11], time[12]);


	for(int i=0; i<8; i++){
		printf("%s\n", colon[i]);
	}


	//clock->array[0] = "****";
	//printf("%s\n", clock->array[0]);

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
