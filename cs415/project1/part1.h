#ifndef PART1_H
#define PART1_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 1
 * This is my own work except a general outline was given during lab
 */

typedef struct{
	char* CMD;
	char** ARGS;
	int ARGC;
	pid_t PID;
} PCB;

int getProgramCount(char **argv); // count number of lines in file to get number of programs
void readPrograms(char **argv, PCB **prgms, int prgmCount); // save program information from file in PCB
void launchPrograms(PCB **prgms, int prgmCount); // launch all the programs
void waitForPrograms(int prgmCount); // wait for all children to finish
void freePrograms(PCB **prgms, int prgmCount); // free all allocated memory in association with PCBs

#endif
