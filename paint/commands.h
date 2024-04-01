#ifndef COMMANDS_H
	#define COMMANDS_H

	#include <stdbool.h>

	#include "canvas.h"

	void List_Of_Commands(Canvas* user);
	void Quit_Command(Canvas* user);
	void Help_Command();
	void Write_Command(Canvas* user, char* positions);
	bool Is_Line_One_Cell_Big(int start_row, int start_col, int end_row, int end_col);
	bool Is_Horizontal_Line(int start_row, int end_row);
	void Draw_Horizontal_Line(Canvas* user, int start_col, int end_col, int row);
	bool Is_Intersection (Canvas user, int row, int col, char line_symbol);
	bool Is_Vertical_Line(int start_col, int end_col);
	void Draw_Vertical_Line(Canvas* user, int start_row, int end_row, int col);
	bool Is_Diagonal_Line(int start_row, int start_col, int end_row, int end_col);
	void Draw_Right_Diagonal_Line(Canvas* user, int start_row, int start_col, int end_row, int end_col);
	void Draw_Left_Diagonal_Line(Canvas* user, int start_row, int start_col, int end_row, int end_col);
	void Erase_Command(Canvas* user, char* positions);
	void Resize_Command(Canvas* user, char* positions);
	void Resize_Rows(Canvas* user, int num_rows);
	void Resize_Cols(Canvas* user, int num_cols);
	void Add_Command(Canvas* user, char* positions);
	void Add_Row(Canvas* user, int pos);
	void Shift_All_Rows_One_Up(Canvas* user, int pos);
	void Add_Col(Canvas* user, int pos);
	void Shift_All_Cols_One_Right(Canvas* user, int pos);
	void Delete_Command(Canvas* user, char* positions);
	void Delete_Row(Canvas* user, int pos);
	void Shift_All_Rows_One_Down(Canvas* user, int pos);
	void Delete_Col(Canvas* user, int pos);
	void Shift_All_Cols_One_Left(Canvas* user, int pos);
	void Save_Command(Canvas user, char* positions);
	void Write_User_Canvas_Into_File(FILE* fp, Canvas user);
	void Load_Command(Canvas* user, char* positions);
	void Read_User_Canvas_From_File(FILE* fp, Canvas* user);
#endif