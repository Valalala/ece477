// Boom Johnson - Walter Rasmussen - Spring 2018
// readProc.c - Reads data from "/proc/loadavg" 5 seconds

#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>

FILE *read1fp, *read2fp, *writefp;
volatile char mfree[100], la1[100], la5[100], la15[100], tmpproc[100], *runproc, *numproc;
int count = 1;

void ALRMhandler(int sig){
	read1fp = fopen("/proc/meminfo", "r");
	read2fp = fopen("/proc/loadavg", "r");
	writefp = fopen("./lab02lameData", "a");
	
	fscanf( read1fp, "%*s %*s %*s %*s %s %*s", mfree);
	fscanf( read2fp, "%s %s %s %s", la1, la5, la15, tmpproc);
	runproc = strtok(tmpproc, "/");
	numproc = strtok(NULL, "/");
	fprintf( writefp, "%d %s %s %s %s %s %s\n", count, mfree, la1, la5, la15, runproc, numproc);
	//fprintf( writefp, )
	//read1fp--;
	//rewind(read1fp);
	//fseek(read1fp, 2L, SEEK_SET);
	//fscanf(read1fp, "%*s %s", mfree);
	printf("%s\n", mfree);
	
	fclose(read1fp);
	fclose(read2fp);
	fclose(writefp);
	count++;
	alarm(1);

}

int main(int argc, char *argz[]) {
	signal( SIGALRM, ALRMhandler);
	
	//read1fp = fopen("/proc/meminfo", "r");
	//read2fp = fopen("/proc/loadavg", "r");
	//writefp = fopen("./lab02lameData", "a");

	alarm(1);
	
	while (1){
		//sleep(1);
		//alarm(1);
	}

	return 0;
}
