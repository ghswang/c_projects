/*
This program has each player make a move on the game
board until either a tie occurs or until one of the
players wins
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "play_game.h"
#include "board.h"

/*
COPIED FROM "input_validation.c" IN CLASS GOOGLE DRIVE!

This function determines whether or not the user has entered a
certain number of desired arguments
@const int numArgsRead: the number of arguments read
@const int numArgsNeed: the desired amount of arguments
@return: bool value of true if the number of arguments read is equal to the desired amount of arguments; bool value of false otherwise
*/
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  
  do {
	scanf("%c", &character); //45  bob  \n
		
		if (!isspace(character)) { //found a non whitespace character on the way to the end of the line
			formatIsGood = false;
		}
	
	} while (character != '\n'); //read characters until the end of the line
  
  return formatIsGood;
}

/*
ADAPTED FROM "input_validation.c" IN CLASS GOOGLE DRIVE!

This function gets a valid integer value from the user
@int num_columns: user-defined number of columns for the game board
@return: valid integer value
*/
int Get_Valid_Int(int num_columns) {
	int value;
	const int numArgsNeeded = 1;
	int numArgsRead;
  
	do {
		printf("Enter a column between 0 and %d to play in: ", (num_columns - 1));
		numArgsRead = scanf(" %d", &value);
		printf("\n");
	} while (!isValidFormat(numArgsRead, numArgsNeeded));

	return value;
}

/*
This function asks player 1 to make a valid move on the game board
and keeps asking until the valid move is made
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@return: N/A
*/
void Player_1_Move(char** board, int num_rows, int num_columns) {
	int player_1_move;
	char player_1_piece = 'X';
	
	do {
		player_1_move = Get_Valid_Int(num_columns);
	} while (player_1_move < 0 || player_1_move > (num_columns - 1) || !Is_Valid_Move_On_Board(board, num_rows, player_1_move));


	Update_Game_Board(&board, num_rows, num_columns, player_1_move, player_1_piece);
}

/*
This function asks player 2 to make a valid move on the game board
and keeps asking until the valid move is made
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@return: N/A
*/
void Player_2_Move(char** board, int num_rows, int num_columns) {
	int player_2_move;
	char player_2_piece = 'O';
	
	do {
		player_2_move = Get_Valid_Int(num_columns);
	} while (player_2_move < 0 || player_2_move > (num_columns - 1) || !Is_Valid_Move_On_Board(board, num_rows, player_2_move));


	Update_Game_Board(&board, num_rows, num_columns, player_2_move, player_2_piece);
}

/*
This function determines whether or not the current player's move is able to
be made considering the current state of the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int curr_player_move: the column in which the current player's piece will be placed
@return: bool value of true if the current player's move is able to be made on the game board; bool value of false otherwise
*/
bool Is_Valid_Move_On_Board(char** board, int num_rows, int curr_player_move) {
	for (int i = 0; i < num_rows; ++i) {
		if ((board[i][curr_player_move] == '*')) {
			return true;
		}
	}

	return false;
}

/*
This function updates and displays the game board after the current player makes a valid move/
places their piece in an open spot on the game board
@char** *board: address of game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int curr_player_move: the column in which the current player's piece will be placed
@char curr_player_piece: the current player's piece, represented as a character (i.e. either 'X' or 'O')
@return: N/A
*/
void Update_Game_Board(char** *board, int num_rows, int num_columns, int curr_player_move, char curr_player_piece) {
	for (int i = 0; i < num_rows; ++i) {
		if ((*board)[(i)][curr_player_move] == '*') {
			(*board)[(i)][curr_player_move] = curr_player_piece;
			break;
		}
	}
	
	Display_Game_Board(*board, num_rows, num_columns);
}

/*
This function plays out Connect N until either player has
won or until a tie has been reached
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: N/A
*/
void Play_Connect_N(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	int i;
	
	if ((num_rows * num_columns) % 2 == 1) {
		Player_1_Move(board, num_rows, num_columns);
		if (Is_Won_Game(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
			return;
		}

		for (i = 0; i < num_rows * num_columns - 1; i += 2) {
			Player_2_Move(board, num_rows, num_columns);
			if (Is_Won_Game(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
				return;
			}
			Player_1_Move(board, num_rows, num_columns);
			if (Is_Won_Game(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
				return;
			}
		}
	}
	else {
		for (i = 0; i < num_rows * num_columns; i += 2) {
			Player_1_Move(board, num_rows, num_columns);
			if (Is_Won_Game(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
				return;
			}
			Player_2_Move(board, num_rows, num_columns);
			if (Is_Won_Game(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
				return;
			}
		}
	}

	printf("Tie game!\n\n");
}

/*
This function determines whether or not a player has won the game
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if a player has won the game; bool value of false otherwise
*/
bool Is_Won_Game(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	return Is_Won_Game_Vertically(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win) ||
			Is_Won_Game_Horizontally(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win) ||
			Is_Won_Game_Diagonally(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win);
}


/*
This function determines whether or not the number of player 1's pieces in a row equals
the number of pieces needed to win for any of the columns on the game board
@char* column: a certain column on the game board
@int num_rows: user-defined number of rows for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 1's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Vertically_X(char* column, int num_rows, int number_of_pieces_in_a_row_needed_to_win) {
	if (number_of_pieces_in_a_row_needed_to_win == 1) {
		return true;
	}

	int player_1_pieces_in_a_row = 1;

	for (int i = 1; i < num_rows; ++i) {
		if (column[i] == column[i - 1] && column[i - 1] == 'X') {
			++player_1_pieces_in_a_row;
			
			if (player_1_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}
		else {
			player_1_pieces_in_a_row = 1;
		}
	}
	
	return false;
}

/*
This function determines whether or not the number of player 2's pieces in a row equals
the number of pieces needed to win for any of the columns on the game board
@char* column: a certain column on the game board
@int num_rows: user-defined number of rows for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 2's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Vertically_O(char* column, int num_rows, int number_of_pieces_in_a_row_needed_to_win) {
	int player_2_pieces_in_a_row = 1;

	for (int i = 1; i < num_rows; ++i) {
		if (column[i] == column[i - 1] && column[i - 1] == 'O') {
			++player_2_pieces_in_a_row;
			
			if (player_2_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}
		else {
			player_2_pieces_in_a_row = 1;
		}
	}
	
	return false;
}

/*
This function determines whether or not the number of player 1's pieces in a row equals
the number of pieces needed to win for any of the rows on the game board
@char* row: a certain row on the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 1's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Horizontally_X(char* row, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	int player_1_pieces_in_a_row = 1;

	for (int i = 1; i < num_columns; ++i) {
		if (row[i] == row[i - 1] && row[i - 1] == 'X') {
			++player_1_pieces_in_a_row;
			
			if (player_1_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}
		else {
			player_1_pieces_in_a_row = 1;
		}
	}

	return false;
}

/*
This function determines whether or not the number of player 2's pieces in a row equals
the number of pieces needed to win for any of the rows on the game board
@char* row: a certain row on the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 2's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Horizontally_O(char* row, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	int player_2_pieces_in_a_row = 1;

	for (int i = 1; i < num_columns; ++i) {
		if (row[i] == row[i - 1] && row[i - 1] == 'O') {
			++player_2_pieces_in_a_row;
			
			if (player_2_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}
		else {
			player_2_pieces_in_a_row = 1;
		}
	}

	return false;
}

/*
This function acquires a specified column from the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int column_entry: the specified column number
@return: a specified column on the game board
*/
char* Obtain_Column_From_Game_Board(char** board, int num_rows, int column_entry) {
	char* column = (char*)malloc(num_rows * sizeof(char));

	for (int i = 0; i < num_rows; ++i) {
		column[i] = board[i][column_entry];
	}

	return column;
}

/*
This function acquires a specified row from the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_columns: user-defined number of columns for the game board
@int row_entry: the specified row number
@return: a specified row on the game board
*/
char* Obtain_Row_From_Game_Board(char** board, int num_columns, int row_entry) {
	char* row = (char*)malloc(num_columns * sizeof(char));

	for (int j = 0; j < num_columns; ++j) {
		row[j] = board[row_entry][j];
	}

	return row;
}

/*
This function determines whether or not a player has won the game vertically
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if a player has won the game vertically; bool value of false otherwise
*/
bool Is_Won_Game_Vertically(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	for (int i = 0; i < num_columns; ++i) {
		char* column = Obtain_Column_From_Game_Board(board, num_rows, i);
		
		if (Is_All_Same_Vertically_X(column, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(column);
			printf("Player 1 Won!\n\n");
			return true;
		}
		else if (Is_All_Same_Vertically_O(column, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(column);
			printf("Player 2 Won!\n\n");
			return true;
		}

		free(column);
	}

	return false;
}


/*
This function determines whether or not a player has won the game horizontally
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if a player has won the game horizontally; bool value of false otherwise
*/
bool Is_Won_Game_Horizontally(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	for (int i = 0; i < num_rows; ++i) {
		char* row = Obtain_Row_From_Game_Board(board, num_columns, i);
		
		if (Is_All_Same_Horizontally_X(row, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
			free(row);
			printf("Player 1 Won!\n\n");
			return true;
		}
		else if (Is_All_Same_Horizontally_O(row, num_columns, number_of_pieces_in_a_row_needed_to_win)) {
			free(row);
			printf("Player 2 Won!\n\n");
			return true;
		}

		free(row);
	}

	return false;
}

/*
This function determines whether or not a player has won the game diagonally
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if a player has won the game diagonally; bool value of false otherwise
*/
bool Is_Won_Game_Diagonally(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	return Is_Won_Game_Left_Diagonal(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win) ||
			Is_Won_Game_Right_Diagonal(board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win);
}

/*
This function acquires a specified left diagonal from the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int starting_row: the row number for the beginning of the specified left diagonal
@int starting_column: the column number for the beginning of the specified left diagonal
@return: a specified left diagonal on the game board
*/
char* Obtain_Left_Diagonal_From_Game_Board(char** board, int num_rows, int starting_row, int starting_column) {
	char* left_diagonal = (char*)malloc(num_rows * sizeof(char));

	left_diagonal[0] = board[starting_row][starting_column];

	for (int i = 1; i < num_rows; ++i) {
		if ((starting_row + 1) > (num_rows - 1) || (starting_column - 1) < 0) {
			break;
		}
		
		left_diagonal[i] = board[starting_row + 1][starting_column - 1];
		++starting_row;
		--starting_column;
	}

	return left_diagonal;
}

/*
This function acquires a specified right diagonal from the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int starting_row: the row number for the beginning of the specified right diagonal
@int starting_column: the column number for the beginning of the specified right diagonal
@return: a specified right diagonal on the game board
*/
char* Obtain_Right_Diagonal_From_Game_Board(char** board, int num_rows, int num_columns, int starting_row, int starting_column) {
	char* right_diagonal = (char*)malloc(num_rows * sizeof(char));

	right_diagonal[0] = board[starting_row][starting_column];

	for (int i = 1; i < num_rows; ++i) {
		if ((starting_row + 1) > (num_rows - 1) || (starting_column + 1) > (num_columns - 1)) {
			break;
		}
		
		right_diagonal[i] = board[starting_row + 1][starting_column + 1];
		++starting_row;
		++starting_column;
	}

	return right_diagonal;
}

/*
This function determines whether or not the number of player 1's pieces in a row equals
the number of pieces needed to win for any of the left diagonals on the game board
@char* left_diagonal: a certain left diagonal on the game board
@int num_rows: user-defined number of rows for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 1's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Left_Diagonal_X(char* left_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win) {
	int player_1_pieces_in_a_row = 1;
	
	for (int i = 1; i < num_rows; ++i) {
		if (left_diagonal[i] == left_diagonal[i - 1] && left_diagonal[i] == 'X') {
			++player_1_pieces_in_a_row;

			if (player_1_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}

		else {
			player_1_pieces_in_a_row = 1;
		}
	}

    return false;
}

/*
This function determines whether or not the number of player 2's pieces in a row equals
the number of pieces needed to win for any of the left diagonals on the game board
@char* left_diagonal: a certain left diagonal on the game board
@int num_rows: user-defined number of rows for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 2's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Left_Diagonal_O(char* left_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win) {
	int player_2_pieces_in_a_row = 1;
	
	for (int i = 1; i < num_rows; ++i) {
		if (left_diagonal[i] == left_diagonal[i - 1] && left_diagonal[i] == 'O') {
			++player_2_pieces_in_a_row;

			if (player_2_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}

		else {
			player_2_pieces_in_a_row = 1;
		}
	}

    return false;
}

/*
This function determines whether or not the number of player 1's pieces in a row equals
the number of pieces needed to win for any of the right diagonals on the game board
@char* right_diagonal: a certain right diagonal on the game board
@int num_rows: user-defined number of rows for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 1's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Right_Diagonal_X(char* right_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win) {
	int player_1_pieces_in_a_row = 1;
	
	for (int i = 1; i < num_rows; ++i) {
		if (right_diagonal[i] == right_diagonal[i - 1] && right_diagonal[i] == 'X') {
			++player_1_pieces_in_a_row;

			if (player_1_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}

		else {
			player_1_pieces_in_a_row = 1;
		}
	}

    return false;
}

/*
This function determines whether or not the number of player 2's pieces in a row equals
the number of pieces needed to win for any of the right diagonals on the game board
@char* right_diagonal: a certain right diagonal on the game board
@int num_rows: user-defined number of rows for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if the number of player 2's pieces in a row equals the number of pieces needed to win; bool value of false otherwise
*/
bool Is_All_Same_Right_Diagonal_O(char* right_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win) {
	int player_2_pieces_in_a_row = 1;
	
	for (int i = 1; i < num_rows; ++i) {
		if (right_diagonal[i] == right_diagonal[i - 1] && right_diagonal[i] == 'O') {
			++player_2_pieces_in_a_row;

			if (player_2_pieces_in_a_row == number_of_pieces_in_a_row_needed_to_win) {
				return true;
			}
		}

		else {
			player_2_pieces_in_a_row = 1;
		}
	}

    return false;
}

/*
This function determines whether or not a player has won the game on any of the left diagonals
on the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if a player has won the game on any of the left diagonals on the game board; bool value of false otherwise
*/
bool Is_Won_Game_Left_Diagonal(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	for (int j = 1; j < num_columns; ++j) {
		char* left_diagonal = Obtain_Left_Diagonal_From_Game_Board(board, num_rows, 0, j);

		if (Is_All_Same_Left_Diagonal_X(left_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(left_diagonal);
			printf("Player 1 Won!\n\n");
			return true;				
		}
		else if (Is_All_Same_Left_Diagonal_O(left_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(left_diagonal);
			printf("Player 2 Won!\n\n");
			return true;
		}

		free(left_diagonal);
	}

	for (int i = 1; i < (num_rows - 1); ++i) {
		char* left_diagonal = Obtain_Left_Diagonal_From_Game_Board(board, num_rows, i, (num_columns - 1));

		if (Is_All_Same_Left_Diagonal_X(left_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(left_diagonal);
			printf("Player 1 Won!\n\n");
			return true;				
		}
		else if (Is_All_Same_Left_Diagonal_O(left_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(left_diagonal);
			printf("Player 2 Won!\n\n");
			return true;
		}

		free(left_diagonal);
	}
	
	return false;
}

/*
This function determines whether or not a player has won the game on any of the right diagonals
on the game board
@char** board: game board with user-defined dimensions number of rows by number of columns
@int num_rows: user-defined number of rows for the game board
@int num_columns: user-defined number of columns for the game board
@int number_of_pieces_in_a_row_needed_to_win: user-specified number of pieces in a row needed to win the game
@return: bool value of true if a player has won the game on any of the right diagonals on the game board; bool value of false otherwise
*/
bool Is_Won_Game_Right_Diagonal(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win) {
	for (int j = 0; j < (num_columns - 1); ++j) {
		char* right_diagonal = Obtain_Right_Diagonal_From_Game_Board(board, num_rows, num_columns, 0, j);

		if (Is_All_Same_Right_Diagonal_X(right_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(right_diagonal);
			printf("Player 1 Won!\n\n");
			return true;
		}
		else if (Is_All_Same_Right_Diagonal_O(right_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(right_diagonal);
			printf("Player 2 Won!\n\n");
			return true;
		}

		free(right_diagonal);
	}

	for (int i = 1; i < (num_rows - 1); ++i) {
		char* right_diagonal = Obtain_Right_Diagonal_From_Game_Board(board, num_rows, num_columns, i, 0);

		if (Is_All_Same_Right_Diagonal_X(right_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(right_diagonal);
			printf("Player 1 Won!\n\n");
			return true;				
		}
		else if (Is_All_Same_Right_Diagonal_O(right_diagonal, num_rows, number_of_pieces_in_a_row_needed_to_win)) {
			free(right_diagonal);
			printf("Player 2 Won!\n\n");
			return true;
		}

		free(right_diagonal);
	}

	return false;	
}