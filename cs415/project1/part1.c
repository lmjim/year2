/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 1
 * This is my own work except a basic outline for launchPrograms was provided
 */

#include "part1.h"

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

void readPrograms(char **argv, PCB **prgms, int prgmCount){
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

void launchPrograms(PCB **prgms, int prgmCount){
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
			execvp(program->CMD, program->ARGS); // run program
			perror("Error: execvp failed"); // error occurred
			freePrograms(prgms, prgmCount); // free memory
			exit(5); // exit due to issue
		}
	}
	return;
}

void waitForPrograms(int prgmCount){
	// wait for all children to finish
	int i = 0;
	for(; i<prgmCount; i++){
		wait(NULL);
	}
	return;
}

void freePrograms(PCB **prgms, int prgmCount){
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
	int prgmCount = getProgramCount(argv); // number of programs found in file
	PCB **prgms = (PCB**)malloc(prgmCount * sizeof(PCB*)); // allocate memory for a list of PCBs, will need to free
	readPrograms(argv, prgms, prgmCount); // save the program information in list of PCBs
	launchPrograms(prgms, prgmCount); // launch all of the programs
	waitForPrograms(prgmCount); // wait for all children to finish
	freePrograms(prgms, prgmCount); // free everything in the list of PCBs
	return 0;
}
