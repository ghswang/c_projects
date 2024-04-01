#ifndef PLAY_GAME_H
	#define PLAY_GAME_H

	#include <stdbool.h>

	bool isValidFormat(const int numArgsRead, const int numArgsNeed);
	int Get_Valid_Int(int num_columns);
	void Player_1_Move(char** board, int num_rows, int num_columns);
	void Player_2_Move(char** board, int num_rows, int num_columns);
	bool Is_Valid_Move_On_Board(char** board, int num_rows, int curr_player_move);
	void Update_Game_Board(char** *board, int num_rows, int num_columns, int curr_player_move, char curr_player_piece);
	void Play_Connect_N(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_Won_Game (char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_All_Same_Vertically_X(char* column, int num_rows, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_All_Same_Vertically_O(char* column, int num_rows, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_All_Same_Horizontally_X(char* row, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_All_Same_Horizontally_O(char* row, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	char* Obtain_Column_From_Game_Board(char** board, int num_rows, int column_entry);
	char* Obtain_Row_From_Game_Board(char** board, int num_columns, int row_entry);
	bool Is_Won_Game_Vertically(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_Won_Game_Horizontally(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_Won_Game_Diagonally(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_Won_Game_Left_Diagonal(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	char* Obtain_Left_Diagonal_From_Game_Board(char** board, int num_rows, int starting_row, int starting_column);
	bool Is_All_Same_Left_Diagonal_X(char* left_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_All_Same_Left_Diagonal_O(char* left_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_Won_Game_Right_Diagonal(char** board, int num_rows, int num_columns, int number_of_pieces_in_a_row_needed_to_win);
	char* Obtain_Right_Diagonal_From_Game_Board(char** board, int num_rows, int num_columns, int starting_row, int starting_column);
	bool Is_All_Same_Right_Diagonal_X(char* right_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win);
	bool Is_All_Same_Right_Diagonal_O(char* right_diagonal, int num_rows, int number_of_pieces_in_a_row_needed_to_win);
	
#endif