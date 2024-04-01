/*
This program has two players play the game Connect N
with user-defined dimensions and user-specified number
of pieces in a row needed to win
*/

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "play_game.h"
#include "clean_up.h"

int main(int argc, char** argv) {
	int num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win, num_args_read;
	char** game_board;
	
	if (argc > 4) {
		printf("Too many arguments entered\n");
		printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit(0);
	}
	else if (argc < 4) {
		printf("Not enough arguments entered\n");
		printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit(0);
	}
	else {
		num_args_read = sscanf(argv[1], "%d", &num_rows);
		if (num_args_read != 1) {
			exit(0);
		}
		
		num_args_read = sscanf(argv[2], "%d", &num_columns);
		if (num_args_read != 1) {
			exit(0);
		}

		num_args_read = sscanf(argv[3], "%d", &number_of_pieces_in_a_row_needed_to_win);
		if (num_args_read != 1) {
			exit(0);
		}
	}

	game_board = Create_Empty_Game_Board(num_rows, num_columns);
	Display_Game_Board(game_board, num_rows, num_columns);
	Play_Connect_N(game_board, num_rows, num_columns, number_of_pieces_in_a_row_needed_to_win);
	Delete_Game_Board(&game_board, num_rows);

	return (0);
}
