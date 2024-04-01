/*
This program cleans/tidies up the remains of Connect N
once the game is over (i.e. either a player has won or
a tie has been reached)
*/

#include <stdio.h>
#include <stdlib.h>

#include "clean_up.h"

/*
This function deletes the ConnectN game board and sets it
to NULL once the game is over (i.e. either a player has won
or a tie has been reached)
@char** *board: address of game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@return: N/A
*/
void Delete_Game_Board(char** *board, int num_rows) {
	for (int i = 0; i < num_rows; ++i) {
		free((*board)[i]);
	}

	free(*board);

	*board = NULL;
}