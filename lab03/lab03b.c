// Boom Johnson - Walter Rasmussen - Spring 2018
// lab03b.c - A game of connect against the computer which writes to an .html file. 

#include<stdio.h>
#include<unistd.h>
#include<strings.h>
#include<stdlib.h>
#include<time.h>

// Dimensions of the game board. 
#define WIDTH 6
#define HEIGHT 6
#define TILES 36

// Updates the array storing the html code based on player and computer moves.
int board( int choice, char player, int moveCount); 
// Places 'O' in opposition to the player. 
int enemyAI(int moveCount);
// Checks the board for winners of a draw. 
int checkWin();
// Rewrites the .html everytime it changes.
void writeToHTML();
// Initilzes the array the .html doc is stored in. 
void startup();

// Represents where the player or comp placed their piece.
struct token{
	int x;
	int y;
}

FILE *writefp; // For file IO
char *doc[256]; // The array that stores the .html file
char gameBoard[TILES] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int writeGrid[TILES]; // The line numbers of the lines in the .html that we want to change.
struct token playerT[TILES]; // Player's tokens.
struct token compT[TILES]; // Computer's tokens. 

int main(int argc, char *argz[]) 
{
	srand(time(NULL));
	int moveCount = 0;
	
	startup();
	writeToHTML();	

	system("chromium-browser ./cooldisplay.html &\n");


	//while (1);

	return 0;
}

int board( int choice, char player, int moveCount)
{
	int i, j; // For loop counters. 
	int pos; // Used to find the x y coordinates based on a single number.
	int x,y; // Coordinates made from choice.
	// 
	if (gameBoard[choice-1] == ' '){
		gameBoard[choice-1] = player;
		doc[writeGrid[choice-1]] = "<td> " + player + " </td>\n";
		writeToHTML();
		
		// Converts single number to coordinate. 
		for (i=0;i<WIDTH;i++) {
			for (j=0;j<HEIGHT;j++) {
				if (pos == (choice-1)) {
					x = i;
					y = j;
				}
				pos++;
			}
		}
		
		// Sets the tokens to have the correct coordinates
		if (player == 'X'){
			playerT[movecount].x = x;
			playerT[movecount].y = y;
		} else {
			compT[movecount].x = x;
			compT[movecount].y = y;
		}
	} else {
		printf("That space is already taken.\n");
		return 1;
	}	

	return 0;
}

int enemyAI(int moveCount)
{
	// Only places pieces randomly. 
	while(board(rand()%9, 'O', moveCount));

	return 0;
}

int checkWin(){
	int i,j; // For loop counters. 
	int prow, pcol, crow, ccol; // Number of symbols that are the same in each row and column.
	int full=0; // Used to check if the board is full. 
	
	// Checks the diagonals
	if ((gameBoard[0]=='X' && gameBoard[4]=='X' && gameBoard[8]=='X') || (gameBoard[2]=='X' && gameBoard[4]=='X' && gameBoard[6]=='X')) {
		printf("Player wins! Play again?\n");
		return 1; 
	} else if ((gameBoard[0]=='O' && gameBoard[4]=='O' && gameBoard[8]=='O') || (gameBoard[2]=='O' && gameBoard[4]=='O' && gameBoard[6]=='O')) {
		printf("Computer wins! Play again?\n");
		return 2; 
	}

	// Checks the rows and columns
	for (i=0;i<TILES-1;i++){
		prow=pcol=crow=ccol=0; // sets all counts to zero.
		for (j=i+1;j<TILES;j++) {
			if (playerT[i].y==playerT[j].y && playerT[j].y != NULL) row++;
			if (playerT[i].x==playerT[j].x && playerT[j].x != NULL) col++;
			
		}
		if (prow == 3 || pcol == 3) { // Does the player have 3 in a row or column. 
			printf("Player wins! Play again?\n");
			return 1; 
		} else if (crow == 3 || ccol == 3) { // Does the computer have 3 in a row or column.
			printf("Computer wins! Play again?\n");
			return 2; 
		}
	}
	
	// Checks for draw
	for (i=0;i<TILES; i++) {
		if (gameBoard[i]!=' ') full++;
	}
	if (full == TILES) {
		printf("It is a draw. Play again?\n");
		return 3;
	}
	
	// No one meets the win condition.
	return 0;

}

void writeToHTML()
{
	int i; // For loop counter. 
	writefp = fopen("./cooldisplay.html", "w");
	//Writes line by line. 
	for (i=0;i<256;i++){
		if (doc[i] != NULL) fprintf( writefp, "%s", doc[i]);
	}
	fclose(writefp);
}

void startup()
{
	int lp = 0; // Line pointer - makes adding and removing lines easier. 
	int boardp = 0; // Makes lines in the html corispond to board positions. 

	// The raw of the .html
	// writeGrid[boardp++]=lp++; This lets us write to specific places in the file more easily.
	doc[lp]="<!DOCTYPE html>\n"; lp++;
	doc[lp]="<html>\n"; lp++;
	doc[lp]="<meta http-equiv="Refresh"content="10">\n"; lp++;
	doc[lp]="<body>\n"; lp++;
	doc[lp]="<h1>Connect 4 Game</h1>\n"; lp++;
	doc[lp]="<p>Good luck and have fun.</p>\n"; lp++;
	doc[lp]="<table border="1">\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="<tr>\n"; lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="<td> _ </td>\n"; writeGrid[boardp++]=lp++;
	doc[lp]="</tr>\n"; lp++;
	doc[lp]="</table>\n"; lp++;
	doc[lp]="<p>Output: </p>\n"; lp++;
	doc[lp]="</body>\n"; lp++;
	doc[lp]="</html>\n"; lp++;
}

