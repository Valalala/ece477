// Boom Johnson - Walter Rasmussen - Spring 2018
// helloWorld.c - Prints "Hello ____!" Planet decided by input arg. 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argz[]) {
	
	// Error checking.
	if (argc != 2) {
		printf("Please enter an integer 1-9\n");
		return 1;
	}
	
	// Converts argument to int for use in the Switch case.
	switch (atoi(argz[1])) {
		case 1: printf("Hello Mercury!\n"); break;
		case 2: printf("Hello Venus!\n"); break;
		case 3: printf("Hello Earth!\n"); break; 
		case 4: printf("Hello Mars!\n"); break;
		case 5: printf("Hello Jupiter!\n"); break;
		case 6: printf("Hello Saturn!\n"); break;
		case 7: printf("Hello Uranus!\n"); break;
		case 8: printf("Hello Neptune!\n"); break;
		case 9: printf("Goodbye Pluto!\n"); break;
		
		default: printf("Hello Universe! (Please enter a number 1-9)\n"); break;	
	}
	
	return 0;
}
