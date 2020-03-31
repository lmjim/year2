#include <stdio.h>
#include <time.h>

void main(){
	time_t cur_time;
	time(&cur_time);
	char *time = ctime(&cur_time);
	printf("The time is now %s", time);
	printf("The day is %c%c%c\n", time[0], time[1], time[2]);
	printf("The hour is %c%c\n", time[11], time[12]);
}
