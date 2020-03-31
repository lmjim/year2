/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 1
 * This is my own work except for updateAndPrintProgram that is based off of 
 * 	code provided in lab and the rest is based off of a basic outline 
 *	that was given. I also chatted with Chase to determine what information
 *	to print out. 
 */

#include "part4.h"

// global variables:
PCB **prgms = NULL;
int prgmCount = 0;
int CurrentProgram = 0;
int allExited = 0;
int StartRun = 0;

void sig_usr1(int signal){
	if(signal == SIGUSR1){
		StartRun = 1; // signal program that it can start
	}
}

void sig_chld(int signal){
	if(signal == SIGCHLD){
		int i = 0;
		for(; i<prgmCount; i++){ // for each program
			int status;
			if(waitpid(prgms[i]->PID, &status, WNOHANG) > 0){
				if(WIFEXITED(status)){ // if program has exited
					if(prgms[i]->HasExited == 0){
						//printf("%d has exited\n", prgms[CurrentProgram]->PID);
						prgms[i]->HasExited = 1; // mark it as being done
					}
				}
			}
		}
	}
}

void sig_alrm(int signal){
	if(signal == SIGALRM){
		//printf("alarm\n");
		if(prgms[CurrentProgram]->HasExited == 1){
			prgms[CurrentProgram]->STATE = Exited; // if program has exited, set its state
			printf("Alarm signaled during:\n");
			updateAndPrintProgram(); // update information based off of proc stat then print info to user
		}
		else{
			printf("Alarm signaled during:\n");
			updateAndPrintProgram(); // update information based off of proc stat then print info to user
			kill(prgms[CurrentProgram]->PID, SIGSTOP); // otherwise pause the program
			prgms[CurrentProgram]->STATE = Paused;
		}
		if(checkPrograms()){
			allExited = 1;
			return; // if all programs are done, proceed to finish
		}
		int oldProgram = CurrentProgram;
		CurrentProgram = nextProgram(); // find the next program that has yet to finish
		if(oldProgram == CurrentProgram){
			printf("Continuing same program\n\n");
		}else{
			printf("Next program to run:\n");
			updateAndPrintProgram(); // update information based off of proc stat then print info to user
		}
		if(prgms[CurrentProgram]->STATE == NotStarted){ // if the program has not been started
			//printf("%d is starting\n", prgms[CurrentProgram]->PID);
			kill(prgms[CurrentProgram]->PID, SIGUSR1); // start the program
			prgms[CurrentProgram]->STATE = Running;
		}
		else{
			kill(prgms[CurrentProgram]->PID, SIGCONT);
			prgms[CurrentProgram]->STATE = Running; // otherwise resume it
		}
	}
}

int getProgramCount(char **argv){
	// count number of lines in file to get number of progrms
	FILE *in = fopen(argv[1], "r"); // will need to close file
	if(in == NULL){
		// issue opening file
		printf("Error: issue opening file\n");
		exit(2);
	}
	int count = 0;
	char *line = NULL; // getline will allocate memory, will need to be freed
	size_t len = 0;
	ssize_t chars;
	while((chars = getline(&line, &len, in)) != -1){
		count++; // for each line increment counter
	}
	free(line); // deallocate memory
	fclose(in); // close file
	return count;
}

void readPrograms(char **argv){
	// save program information from file in PCB
	FILE *in = fopen(argv[1], "r"); // will need to close file
	if(in == NULL){
		// issue opening file
		printf("Error: issue opening file a second time\n");
		exit(3);
	}
	char *line = NULL; // getline will allocate memory, will need to be freed
	size_t len = 0;
	ssize_t chars;
	int i = 0;
	for(; i<prgmCount; i++){
		chars = getline(&line, &len, in); // read in line
		if(line[chars - 1] == '\n'){
			line[chars - 1] = '\0'; // remove the new line character
		}
		char *lineCopy = strdup(line); // make a copy of the line so original is not altered, will need to free later
		int wordCount = 0; // initialize counter of words in the line
		char *token = strtok(lineCopy, " ");
		while(token != NULL){
			wordCount++; // count the number of words on the line
			token = strtok(NULL, " ");
		}
		PCB *newPCB = (PCB*)malloc(sizeof(PCB)); // create new PCB
		newPCB->ARGC = wordCount; // save argument count in PCB
		newPCB->STATE = NotStarted; // has not started
		newPCB->HasExited = 0; // has not exited
		newPCB->UserTime = -1; // initialize, real time won't be negative
		newPCB->SystemTime = -1; // initialize, real time won't be negative
		newPCB->StartTime = -1; // initialize, real time won't be negative
		newPCB->UpTime = -1; // initialize, real time won't be negative
		newPCB->VSIZE = -1; // initialize, real size won't be negative
		char *lineCopy2 = strdup(line); // make another copy of the original line, will need to free later
		char *arg = strtok(lineCopy2, " ");
		newPCB->CMD = strdup(arg); // save command in PCB
		newPCB->ARGS = (char **)malloc((wordCount+1) * sizeof(char*)); // allocate memory for all of the arguments plus a spot for the null pointer at the end
		int j = 0;
		for(; j<wordCount; j++){
			newPCB->ARGS[j] = strdup(arg); // save each argument in PCB
			arg = strtok(NULL, " ");
		}
		newPCB->ARGS[j] = NULL; // arguments need to end with a null value
		newPCB->PID = -1; // set default pid to negative
		prgms[i] = newPCB; // add this new PCB to the list of programs
		free(lineCopy); // free duplicated line
		free(lineCopy2); // free second duplication
	}
	free(line); // free original line
	fclose(in); // close file
	return;
}

void launchPrograms(){
	// launch all the programs
	int i = 0;
	for(; i<prgmCount; i++){ // launch each program
		PCB *program = prgms[i];
		program->PID = fork(); // fork
		if(program->PID < 0){
			perror("Error: fork failed"); // error occurred
			freePrograms(prgms, prgmCount); // free memory
			exit(4); // exit due to failure
		}
		if(program->PID == 0){
			while(StartRun == 0){
				usleep(100);
			}
			execvp(program->CMD, program->ARGS); // run program
			perror("Error: execvp failed"); // error occurred
			freePrograms(prgms, prgmCount); // free memory
			exit(5); // exit due to issue
		}
	}
	return;
}

char * getStateString(State state){
	// get user readable state
	switch(state){
		case NotStarted: return "Not Started";
		case Running: return "Running";
		case Paused: return "Paused";
		case Exited: return "Exited";
		default: return "Issue occured reading state";
	}
}

void updateAndPrintProgram(){
	// update information based off of proc stat then print info to user
	// access /proc/PID/stat:
	char path[16];
	sprintf(path, "/proc/%d/stat", prgms[CurrentProgram]->PID);
	FILE *file = fopen(path, "r");
	if(file != NULL){
		char buffer[1024];
		char delimiters[] = " ";
		fgets(buffer, sizeof(buffer), file);
		int i = 1;
		char *ptr = strtok(buffer, delimiters);
		do{
			if(i == 14){
				prgms[CurrentProgram]->UserTime = atoi(ptr);
			}
			if(i == 15){
				prgms[CurrentProgram]->SystemTime = atoi(ptr);
			}
			if(i == 22){
				prgms[CurrentProgram]->StartTime = atoi(ptr);
			}
			if(i == 23){
				prgms[CurrentProgram]->VSIZE = atoi(ptr);
			}
			i++;
			ptr = strtok(NULL, delimiters);
		}while(ptr != NULL);
		fclose(file);
	}
	// access /proc/uptime:
	char path2[13] = "/proc/uptime";
	FILE *file2 = fopen(path2, "r");
	if(file2 != NULL){
		char buffer2[1024];
		char delimiters2[] = " ";
		fgets(buffer2, sizeof(buffer2), file2);
		char *ptr2 = strtok(buffer2, delimiters2);
		prgms[CurrentProgram]->UpTime = atoi(ptr2);
		fclose(file2);
	}
	// print info:
	printf("\tProcess %d:  %s ", prgms[CurrentProgram]->PID, prgms[CurrentProgram]->CMD); // print which process is being looked at
	int i = 1;
	for(; i<prgms[CurrentProgram]->ARGC; i++){
		printf("%s ", prgms[CurrentProgram]->ARGS[i]); // print the command/args used to launch process
	}
	int utime = prgms[CurrentProgram]->UserTime;
	int stime = prgms[CurrentProgram]->SystemTime;
	int etime = prgms[CurrentProgram]->UpTime - (prgms[CurrentProgram]->StartTime / sysconf(_SC_CLK_TCK));
	int vSize = prgms[CurrentProgram]->VSIZE;
	printf("\n\tState: %s\tTime Since Starting: %d\tMemory: %d\n\t\tUser Time: %d\tSystem Time: %d\n", getStateString(prgms[CurrentProgram]->STATE), etime, vSize, utime, stime); // print proc information
	printf("\n"); // skip a line after printing info
}

int nextProgram(){
	// get next program that has not exited
	int i = 0;
	int j = CurrentProgram;
	for(; i<prgmCount - 1; i++){
		if(j == prgmCount - 1){
			j = 0;
		}
		else{
			j++;
		}
		if(prgms[j]->STATE != Exited){
			return j; // next program in list
		}
	}
	return CurrentProgram; // only the one program left
}

int checkPrograms(){
	// check if all programs have exited
	int i = 0;
	for(; i<prgmCount; i++){
		if(prgms[i]->STATE != Exited){
			return 0; // not all programs have exited
		}
	}
	return 1; // all programs have exited
}

void freePrograms(){
	// free all allocated memory in association with PCBs
	int i = 0;
	for(; i<prgmCount; i++){ // for each PCB
		free(prgms[i]->CMD); // free command
		int num = (prgms[i]->ARGC) + 1;
		int j = 0;
		for(; j<num;j++){
			free((prgms[i]->ARGS)[j]); // free each arg in args (including the additional null)
		}
		free(prgms[i]->ARGS); // free args
		free(prgms[i]); // free the PCB
	}
	free(prgms); // free the list of PCBs
}

int main(int argc, char **argv){
	if(argc != 2){
		// no file to read from
		printf("Error: no file to read from or too many args given\n");
		exit(1);
	}
	prgmCount = getProgramCount(argv); // number of programs found in file
	prgms = (PCB**)malloc(prgmCount * sizeof(PCB*)); // allocate memory for a list of PCBs, will need to free
	signal(SIGUSR1, sig_usr1); // subscribe to signal handler
	signal(SIGCHLD, sig_chld); // subscribe to signal handler
	signal(SIGALRM, sig_alrm); // subscribe to signal handler
	readPrograms(argv); // save the program information in list of PCBs
	launchPrograms(); // launch all of the programs

	struct itimerval timer;
        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 100000; // 100 milliseconds
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 100000; // 100 milliseconds

	printf("Starting program:\n");
	updateAndPrintProgram();
	kill(prgms[0]->PID, SIGUSR1); // start first program
	prgms[0]->STATE = Running; // set state, note: current program already initialized to 0
	setitimer(ITIMER_REAL, &timer, 0);
	while(!allExited){
		kill(prgms[CurrentProgram]->PID, SIGCHLD);
	}
	printf("All programs finished\n");
	freePrograms(); // free everything in the list of PCBs
	return 0;
}
