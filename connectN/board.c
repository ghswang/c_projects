/*
This program creates the game board for Connect N
and displays it to the user
*/

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

/*
This function creates an empty game board for ConnectN
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@return: empty gameboard with user-defined dimensions number of rows by number of columns
*/
char** Create_Empty_Game_Board(int num_rows, int num_columns) {
	int i, j;
	
	char** empty_board = (char**)malloc(num_rows * sizeof(char*));
	for (i = 0; i < num_rows; ++i) {
		empty_board[i] = (char*)malloc(num_columns * sizeof(char));
	}

	for (i = 0; i < num_rows; ++i) {
		for (j = 0; j < num_columns; ++j) {
			empty_board[i][j] = '*';
		}
	}

	return empty_board;
}

/*
This function displays the game board for ConnectN to the user
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@return: N/A
*/
void Display_Game_Board(char** board, int num_rows, int num_columns) {
	int i, j;
	
	printf("\n");

	for (i = (num_rows - 1); i >= 0; --i) {
		printf("%d ", i);
		for (j = 0; j < num_columns; ++j) {
			printf("%c ", board[i][j]);
		}
		
		printf("\n");
	}

	printf("  ");
	
	for (j = 0; j < num_columns; ++j) {
		printf ("%d ", j);
	}
	
	printf("\n\n");
}