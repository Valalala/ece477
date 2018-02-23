// Boom Johnson - Walter Rasmussen - Spring 2018
// lamelab03.c - A game of tic tac toe against the computer which writes to an .html file. 

#include<stdio.h>
#include<unistd.h>
#include<strings.h>
#include<stdlib.h>

int board( int choice, char player); 
int enemyAI();
void writeToHTML();
// Initilzes the array the .html doc is stored in. 
void startup();

FILE *writefp;
char *doc[256];
char gameBoard[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

int main(int argc, char *argz[]) 
{
	
	
	startup();
	writeToHTML();
	

	//system("chromium-browser ./lamedisplay.html &\n");

	//while (1);

	return 0;
}

int board( int choice, char player)
{
	
	gameBoard[choice-1] = player;
	
	return 0;
}

int enemyAI()
{


	return 0;
}

void writeToHTML()
{
	int i;
	writefp = fopen("./lamedisplay.html", "w");
	for (i=0;i<256;i++){
		if (doc[i] != NULL) fprintf( writefp, "%s", doc[i]);
	}
	fclose(writefp);
}

void startup()
{
	int lp = 0; // Line pointer - makes adding and removing lines easier. 

	// The raw of the .html
	doc[lp]="<!DOCTYPE html>\n"; lp++;
	doc[lp]="<html>\n"; lp++;
	doc[lp]="<meta http-equiv=\"Refresh\"content=\"10\">\n"; lp++;
	doc[lp]="<body>\n"; lp++;
	doc[lp]="<h1>Tic-Tac-Toe Game</h1>\n"; lp++;
	doc[lp]="<p>PlEAsE plAy MeEE3!</p>\n"; lp++;
	doc[lp]="<table border=\"1\">\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="</table>\n"; lp++;
	doc[lp]="<p>Output:  </p>\n"; lp++;
	doc[lp]="</body>\n"; lp++;
	doc[lp]="</html>\n"; lp++;
}

