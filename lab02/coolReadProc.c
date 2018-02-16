// Boom Johnson - Walter Rasmussen - Spring 2018
// readProc.c - Reads data from "/proc/loadavg" 1 seconds with  end signal handling.

#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>

FILE *read1fp, *read2fp, *writefp;
volatile char mfree[100], la1[100], la5[100], la15[100], tmpproc[100], *runproc, *numproc;
int count = 1; // Data index
int exitCheck = 0; // Used in EXIThandler

void ALRMhandler(int sig){
	read1fp = fopen("/proc/meminfo", "r");
	read2fp = fopen("/proc/loadavg", "r");
	writefp = fopen("./lab02coolData", "a");
	
	fscanf( read1fp, "%*s %*s %*s %*s %s %*s", mfree);
	fscanf( read2fp, "%s %s %s %s", la1, la5, la15, tmpproc);
	runproc = strtok(tmpproc, "/");
	numproc = strtok(NULL, "/");

	fprintf( writefp, "%d %s %s %s %s %s %s\n", count, mfree, la1, la5, la15, runproc, numproc);
	
	fclose(read1fp);
	fclose(read2fp);
	fclose(writefp);
	
	count++;
	alarm(1);
}

void EXIThandler(int sig){ // Checks if the user actually wants to exit.
	if (!exitCheck){
		printf("\nAre you sure you want to exit?\n");
		exitCheck++;
		return;
	}
	printf("\nProgram was safely closed.\n");
	exit(0);
}

int main(int argc, char *argz[]) {
	signal( SIGALRM, ALRMhandler);
	signal( SIGINT, EXIThandler);

	alarm(1);
	
	while (1);

	return 0;
}
