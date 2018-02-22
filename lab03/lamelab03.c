// Boom Johnson - Walter Rasmussen - Spring 2018
// lamelab03.c - A game of tic tac toe against the computer which writes to an .html file. 

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

FILE *writefp;
char gameBoard[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

int main(int argc, char *argz[]) {
	
	// Checks if file exists, if it doesn't create and fill it.
	if (access("./lamedisplay.html", F_OK) == -1) startup();

	system("chromium-browser ./lamedisplay.html &\n");

	//while (1);

	return 0;
}

int board( int choice, char player){

	

	if (square[choice-1] ==) square[choice-1] = player;

	writefp = fopen("./lamedisplay.html", "r+");

	fclose(writefp);
}

int enemyAI(){

}

void startup(){

	writefp = fopen("./lamedisplay.html", "a");

	fprintf( writefp, "<!DOCTYPE html>\n");
	fprintf( writefp, "<html>\n");
	fprintf( writefp, "<meta http-equiv="Refresh"content="10">\n");
	fprintf( writefp, "<body>\n");
	fprintf( writefp, "<h1>Tic-Tac-Toe Game</h1>\n");
	fprintf( writefp, "<p>PlEAsE plAy MeEE3!</p>\n");
	fprintf( writefp, "<table border="1">\n");
	fprintf( writefp, "<tr>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "</tr>\n");
	fprintf( writefp, "<tr>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "</tr>\n");
	fprintf( writefp, "<tr>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "<td>_</td>\n");
	fprintf( writefp, "</tr>\n");
	fprintf( writefp, "</table>\n");
	fprintf( writefp, "<p>Output:  </p>\n");
	fprintf( writefp, "</body>\n");
	fprintf( writefp, "</html>\n");

	fclose(writefp);

}

