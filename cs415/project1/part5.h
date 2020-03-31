#ifndef PART5_H
#define PART5_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 1
 * This is my own work except a general outline was given during lab
 */

typedef enum{ NotStarted, Running, Paused, Exited } State;

typedef struct{
	char* CMD;
	char** ARGS;
	int ARGC;
	pid_t PID;
	State STATE;
	int HasExited;
	int UserTime;
	int SystemTime;
	int StartTime;
	int UpTime;
	int VSIZE;
} PCB;

void sig_usr1(int signal); // SIGUSR1 signal handler
void sig_chld(int signal); // SIGCHLD signal handler
void sig_alrm(int signal); // SIGALRM signal handler
int getProgramCount(char **argv); // count number of lines in file to get number of programs
void readPrograms(char **argv); // save program information from file in PCB
void launchPrograms(); // launch all the programs
char * getStateString(State state); // get user readable state
void updateAndPrintProgram(); // update information based off of proc stat then print info to user
int nextProgram(); // get next program that has not exited
int checkPrograms(); // check if all programs have exited
void freePrograms(); // free all allocated memory in association with PCBs

#endif
