/*
This program is responsible for command-related
functions and/or operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "input_validation.h"

/*
This function serves to execute a list of commands
depending on user input and informs the user whether
or not their input is a valid command
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@return: N/A
*/
void List_Of_Commands(Canvas* user) {
	char firstCharacter;
	char* positions = NULL;

	scanf(" %c", &firstCharacter);

	if (firstCharacter == 'q' && isValidFormat(1, 1)) {
		Quit_Command(user);
	}
	else if (firstCharacter == 'h' && isValidFormat(1, 1)) {
		Help_Command();
	}
	else if (firstCharacter == 'w' && Is_Valid_Command_Format(&positions, 4, firstCharacter)) {
		Write_Command(user, positions);
	}
	else if (firstCharacter == 'e' && Is_Valid_Command_Format(&positions, 2, firstCharacter)) {
		Erase_Command(user, positions);
	}
	else if (firstCharacter == 'r' && Is_Valid_Command_Format(&positions, 2, firstCharacter)) {
		Resize_Command(user, positions);
	}
	else if (firstCharacter == 'a' && Is_Valid_Command_Format(&positions, 2, firstCharacter)) {
		Add_Command(user, positions);
	}
	else if (firstCharacter == 'd' && Is_Valid_Command_Format(&positions, 2, firstCharacter)) {
		Delete_Command(user, positions);
	}
	else if (firstCharacter == 's' && Is_Valid_Command_Format(&positions, 1, firstCharacter)) {
		Save_Command(*user, positions);
	}
	else if (firstCharacter == 'l' && Is_Valid_Command_Format(&positions, 1, firstCharacter)) {
		Load_Command(user, positions);
	}
	else {
		if (firstCharacter == 'w') {
			free(positions);
			printf("\nImproper draw command.\n");
		}
		else if (firstCharacter == 'e') {
			free(positions);
			printf("\nImproper erase command.\n");
		}
		else if (firstCharacter == 'r') {
			free(positions);
			printf("\nImproper resize command.\n");
		}
		else if (firstCharacter == 'a') {
			free(positions);
			printf("\nImproper add command.\n");
		}
		else if (firstCharacter == 'd') {
			free(positions);
			printf("\nImproper delete command.\n");
		}
		else if (firstCharacter == 's') {
			free(positions);
			printf("\nImproper save command or file could not be created.\n");
		}
		else if (firstCharacter == 'l') {
			free(positions);
			printf("\nImproper load command or file could not be opened.\n");
		}
		else {
			printf("\nUnrecognized command. Type h for help.\n");
		
			while(firstCharacter != 'q' && firstCharacter != 'h') {
				scanf("%c", &firstCharacter);

				if (firstCharacter == '\n') {
					break;
				}
			}
		}
	}
}

/*
This function deletes the user's canvas
and quits/exits the program
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@return: N/A
*/
void Quit_Command(Canvas* user) {
	for (int i = 0; i < user->num_rows; ++i) {
		free(user->canvas[i]);
	}

	free(user->canvas);

	printf("\n");

	exit(0);
}

/*
This function displays the various commands
that can be executed, as well as the correct
formatting for the user's input in order to
access them, respectively
@return: N/A
*/
void Help_Command() {
	printf("\nCommands:\n\n");
	printf("Help: h\n");
	printf("Quit: q\n");
	printf("Draw line: w row_start col_start row_end col_end\n");
	printf("Resize: r num_rows num_cols\n");
	printf("Add row or column: a [r | c] pos\n");
	printf("Delete row or column: d [r | c] pos\n");
	printf("Erase: e row col\n");
	printf("Save: s file_name\n");
	printf("Load: l file_name\n");
}

/*
This function allows the user to draw various
types of lines on the canvas but will not draw
on the canvas if the user's input does not specify
to draw within the dimensions of the canvas or if
the user's input does not form a line
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Write_Command(Canvas* user, char* positions) {
	int start_row, start_col, end_row, end_col;

	sscanf(positions, "%d %d %d %d", &start_row, &start_col, &end_row, &end_col);
	free(positions);

	if (!Is_Int_Between_Inclusive(start_row, 0, user->num_rows - 1) ||
		!Is_Int_Between_Inclusive(end_row, 0, user->num_rows - 1) ||
		!Is_Int_Between_Inclusive(start_col, 0, user->num_cols - 1) ||
		!Is_Int_Between_Inclusive(end_col, 0, user->num_cols - 1)) {
		
		printf("\nImproper draw command.\n");

		return;
	}

	if (Is_Line_One_Cell_Big(start_row, start_col, end_row, end_col)) {
		if (Is_Intersection(*user, start_row, start_col, '-')) {
			user->canvas[start_row][start_col] = '+';
		}
		else {
			user->canvas[start_row][start_col] = '-';
		}
	}
	else if (Is_Horizontal_Line(start_row, end_row)) {
		Draw_Horizontal_Line(user, start_col, end_col, start_row);
	}
	else if (Is_Vertical_Line(start_col, end_col)) {
		Draw_Vertical_Line(user, start_row, end_row, start_col);
	}
	else if (Is_Diagonal_Line(start_row, start_col, end_row, end_col)) {
		Draw_Right_Diagonal_Line(user, start_row, start_col, end_row, end_col);
		Draw_Left_Diagonal_Line(user, start_row, start_col, end_row, end_col);
	}
	else {
		printf("\nImproper draw command.\n");
	}
}

/*
This function determines whether or not the user's
input specifies to draw a line that occupies a singular
row and column (entry) on the canvas
@int start_row: row number in the canvas where the line starts
@int start_col: column number in the canvas where the line starts
@int end_row: row number in the canvas where the line ends
@int end_col: column number in the canvas where the line ends
@return: bool value of true if the user's input
			specifies to draw a line that occupies a
			singular row and column (entry) on the canvas;
			bool value of false otherwise
*/
bool Is_Line_One_Cell_Big(int start_row, int start_col, int end_row, int end_col) {
	return start_row == end_row && start_col == end_col;
}

/*
This function determines whether or not the user's
input specifies to draw a horizontal line on the canvas
@int start_row: row number in the canvas where the line starts
@int end_row: row number in the canvas where the line ends
@return: bool value of true if the user's input
			specifies to draw a horizontal line on the
			canvas; bool value of false otherwise
*/
bool Is_Horizontal_Line(int start_row, int end_row) {
	return start_row == end_row;
}

/*
This function draws a horizontal line on the canvas
according to the user's input
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int start_col: column number in the canvas where the line starts
@int end_col: column number in the canvas where the line ends
@int row: row number in the canvas where the horizontal line will be drawn
@return: N/A
*/
void Draw_Horizontal_Line(Canvas* user, int start_col, int end_col, int row) {
	int j;
	
	if (start_col < end_col) {
		for (j = start_col; j <= end_col; ++j) {
			if (Is_Intersection(*user, row, j, '-')) {
				user->canvas[row][j] = '+';
			}
			else {
				user->canvas[row][j] = '-';
			}
		}	
	}
	else {
		for (j = end_col; j <= start_col; ++j) {
			if (Is_Intersection(*user, row, j, '-')) {
				user->canvas[row][j] = '+';
			}
			else {
				user->canvas[row][j] = '-';
			}
		}		
	}	
}

/*
This function determines whether or not a line intersects
another line in the canvas
@Canvas user: user's canvas, including the canvas itself
					and the values for its dimensions
@int row: specific row number in the canvas
@int col: specific column number in the canvas
@char line_symbol: the representation for a particular type of line
					(e.g. horizontal, vertical, etc.)
@return: bool value of true if a line intersects another line in the
			canvas; bool value of false otherwise
*/
bool Is_Intersection(Canvas user, int row, int col, char line_symbol) {
	return user.canvas[row][col] != line_symbol && user.canvas[row][col] != '*';
}

/*
This function determines whether or not the user's
input specifies to draw a vertical line on the canvas
int start_col: column number in the canvas where the line starts
@int end_col: column number in the canvas where the line ends
@return: bool value of true if the user's input
			specifies to draw a vertical line on the
			canvas; bool value of false otherwise
*/
bool Is_Vertical_Line(int start_col, int end_col) {
	return start_col == end_col;
}

/*
This function draws a vertical line on the canvas
according to the user's input
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int start_row: row number in the canvas where the line starts
@int end_row: row number in the canvas where the line ends
@int col: column number in the canvas where the vertical line will be drawn
@return: N/A
*/
void Draw_Vertical_Line(Canvas* user, int start_row, int end_row, int col) {
	int i;

	if (start_row < end_row) {
		for (i = start_row; i <= end_row; ++i) {
			if (Is_Intersection(*user, i, col, '|')) {
				user->canvas[i][col] = '+';
			}
			else {
				user->canvas[i][col] = '|';
			}
		}	
	}
	else {
		for (i = end_row; i <= start_row; ++i) {
			if (Is_Intersection(*user, i, col, '|')) {
				user->canvas[i][col] = '+';
			}
			else {
				user->canvas[i][col] = '|';
			}
		}		
	} 
}

/*
This function determines whether or not the user's
input specifies to draw a diagonal line on the canvas
@int start_row: row number in the canvas where the line starts
@int start_col: column number in the canvas where the line starts
@int end_row: row number in the canvas where the line ends
@int end_col: column number in the canvas where the line ends
@return: bool value of true if the user's input
			specifies to draw a diagonal line on the
			canvas; bool value of false otherwise
*/
bool Is_Diagonal_Line(int start_row, int start_col, int end_row, int end_col) {
	return abs(end_row - start_row) == abs(end_col - start_col);
}

/*
This function draws a right diagonal line on the canvas
according to the user's input
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int start_row: row number in the canvas where the line starts
@int start_col: column number in the canvas where the line starts
@int end_row: row number in the canvas where the line ends
@int end_col: column number in the canvas where the line ends
@return: N/A
*/
void Draw_Right_Diagonal_Line(Canvas* user, int start_row, int start_col, int end_row, int end_col) {
	int i, j;

	if (start_row < end_row && start_col < end_col) {
		for (i = start_row, j = start_col; i <= end_row && j <= end_col; ++i, ++j) {
			if (Is_Intersection(*user, i, j, '/')) {
				user->canvas[i][j] = '+';
			}
			else {
				user->canvas[i][j] = '/';
			}
		}
	}
	else if (start_row > end_row && start_col > end_col) {
		for (i = end_row, j = end_col; i <= start_row && j <= start_col; ++i, ++j) {
			if (Is_Intersection(*user, i, j, '/')) {
				user->canvas[i][j] = '+';
			}
			else {
				user->canvas[i][j] = '/';
			}
		}
	}
}

/*
This function draws a left diagonal line on the canvas
according to the user's input
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int start_row: row number in the canvas where the line starts
@int start_col: column number in the canvas where the line starts
@int end_row: row number in the canvas where the line ends
@int end_col: column number in the canvas where the line ends
@return: N/A
*/
void Draw_Left_Diagonal_Line(Canvas* user, int start_row, int start_col, int end_row, int end_col) {
	int i, j;

	if (start_row > end_row && start_col < end_col) {
		for (i = start_row, j = start_col; i >= end_row && j <= end_col; --i, ++j) {
			if (Is_Intersection(*user, i, j, '\\')) {
				user->canvas[i][j] = '+';
			}
			else {
				user->canvas[i][j] = '\\';
			}
		}
	}
	else if (start_row < end_row && start_col > end_col) {
		for (i = start_row, j = start_col; i <= end_row && j >= end_col; ++i, --j) {
			if (Is_Intersection(*user, i, j, '\\')) {
				user->canvas[i][j] = '+';
			}
			else {
				user->canvas[i][j] = '\\';
			}
		}
	}
}

/*
This function erases or deletes a user-given
row-column entry on the canvas, effectively
returning it to a blank space or blank entry
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Erase_Command(Canvas* user, char* positions) {
	int row, col;

	sscanf(positions, "%d %d", &row, &col);
	free(positions);

	if (!Is_Int_Between_Inclusive(row, 0, user->num_rows - 1) ||
		!Is_Int_Between_Inclusive(col, 0, user->num_cols - 1)) {
		
		printf("\nImproper erase command.\n");

		return;
	}

	user->canvas[row][col] = '*';	
}

/*
This function resizes the canvas to be some user-specified
number of rows by number of columns
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Resize_Command(Canvas* user, char* positions) {
	int num_rows, num_cols;

	sscanf(positions, "%d %d", &num_rows, &num_cols);
	free(positions);

	if (user->num_rows == num_rows && user->num_cols == num_cols) {
		return;
	}
	else if (!Is_Int_At_Least(num_rows, 1) || !Is_Int_At_Least(num_cols, 1)) {
		printf("\nImproper resize command.\n");

		return;
	}
	
	if (user->num_cols == num_cols) {
		Resize_Rows(user, num_rows);
	}
	else if (user->num_rows == num_rows) {
		Resize_Cols(user, num_cols);
	}
	else {
		Resize_Rows(user, num_rows);
		Resize_Cols(user, num_cols);
	}
}

/*
This function resizes the canvas to be the new user-specified
number of rows by the same number of columns of the current canvas
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int num_rows: the new user-specified number of rows
@return: N/A
*/
void Resize_Rows(Canvas* user, int num_rows) {
	int i, j;

	if (num_rows > user->num_rows) {
		user->canvas = (char**)realloc(user->canvas, num_rows * sizeof(char*));

		for (i = user->num_rows; i < num_rows; ++i) {
			user->canvas[i] = (char*)malloc(user->num_cols * sizeof(char));
			
			for (j = 0; j < user->num_cols; ++j) {
				user->canvas[i][j] = '*';
			}
		}

		user->num_rows = num_rows;
	}
	else if (num_rows < user->num_rows) {
		user->canvas = (char**)realloc(user->canvas, num_rows * sizeof(char*));

		user->num_rows = num_rows;
	}
}

/*
This function resizes the canvas to be the same number of rows
of the current canvas by the new user-specified number of columns
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int num_cols: the new user-specified number of columns
@return: N/A
*/
void Resize_Cols(Canvas* user, int num_cols) {
	int i, j;

	if (num_cols > user->num_cols) {
		for (i = 0; i < user->num_rows; ++i) {
			user->canvas[i] = (char*)realloc(user->canvas[i], num_cols * sizeof(char));

			for (j = user->num_cols; j < num_cols; ++j) {
				user->canvas[i][j] = '*';
			}
		}

		user->num_cols = num_cols;
	}
	else if (num_cols < user->num_cols) {
		for (i = 0; i < user->num_rows; ++i) {
			user->canvas[i] = (char*)realloc(user->canvas[i], num_cols * sizeof(char));
		}

		user->num_cols = num_cols;		
	}
}

/*
This function adds either a new row or new column somewhere in the canvas,
depending on the user's input
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Add_Command(Canvas* user, char* positions) {
	char identifier;
	int pos;

	sscanf(positions, " %c %d", &identifier, &pos);
	free(positions);

	if (identifier == 'r') {
		Add_Row(user, pos);
	}
	else {
		Add_Col(user, pos);
	}
}

/*
This function adds a new row at some user-specified row number
in the canvas
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified row number
@return: N/A
*/
void Add_Row(Canvas* user, int pos) {
	if (!Is_Int_Between_Inclusive(pos, 0, user->num_rows)) {
		printf("\nImproper add command.\n");

		return;
	}

	++user->num_rows;
		
	user->canvas = (char**)realloc(user->canvas, user->num_rows * sizeof(char*));
	user->canvas[user->num_rows - 1] = (char*)malloc(user->num_cols * sizeof(char));

	for (int j = 0; j < user->num_cols; ++j) {
		user->canvas[user->num_rows - 1][j] = '*';
	}

	Shift_All_Rows_One_Up(user, pos);
}

/*
This function shifts the row at some user-specified row number
in the canvas and all rows above it up by one row
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified row number
@return: N/A
*/
void Shift_All_Rows_One_Up(Canvas* user, int pos) {
	char placeholder;
	
	for (int i = user->num_rows - 1; i > pos; --i) {
		for (int j = 0; j < user->num_cols; ++j) {
			placeholder = user->canvas[i][j];
			user->canvas[i][j] = user->canvas[i - 1][j];
			user->canvas[i - 1][j] = placeholder;
		}
	}
}

/*
This function adds a new column at some user-specified column
number in the canvas
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified column number
@return: N/A
*/
void Add_Col(Canvas* user, int pos) {
	if (!Is_Int_Between_Inclusive(pos, 0, user->num_cols)) {
		printf("\nImproper add command.\n");

		return;
	}

	++user->num_cols;

	for (int i = 0; i < user->num_rows; ++i) {
		user->canvas[i] = (char*)realloc(user->canvas[i], user->num_cols * sizeof(char));
		
		user->canvas[i][user->num_cols - 1] = '*';
	}

	Shift_All_Cols_One_Right(user, pos);
}

/*
This function shifts the column at some user-specified column
number in the canvas and all columns to the right of it one to
the right
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified column number
@return: N/A
*/
void Shift_All_Cols_One_Right(Canvas* user, int pos) {
	char placeholder;

	for (int i = 0; i < user->num_rows; ++i) {
		for (int j = user->num_cols - 1; j > pos; --j) {
			placeholder = user->canvas[i][j];
			user->canvas[i][j] = user->canvas[i][j - 1];
			user->canvas[i][j - 1] = placeholder;
		}
	}
}

/*
This function deletes either a row or column somewhere in the canvas,
depending on the user's input
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Delete_Command(Canvas* user, char* positions) {
	char identifier;
	int pos;

	sscanf(positions, " %c %d", &identifier, &pos);
	free(positions);

	if (identifier == 'r') {
		Delete_Row(user, pos);
	}
	else {
		Delete_Col(user, pos);
	}
}

/*
This function deletes some user-specified row in the canvas
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified row number
@return: N/A
*/
void Delete_Row(Canvas* user, int pos) {
	if (!Is_Int_Between_Inclusive(pos, 0, user->num_rows - 1)) {
		printf("\nImproper delete command.\n");

		return;
	}

	Shift_All_Rows_One_Down(user, pos);

	--user->num_rows;

	user->canvas = (char**)realloc(user->canvas, user->num_rows * sizeof(char*));
}

/*
This function shifts the row at some user-specified row number
in the canvas and all rows above it down by one row
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified row number
@return: N/A
*/
void Shift_All_Rows_One_Down(Canvas* user, int pos) {
	char placeholder;

	for (int i = pos; i < user->num_rows - 1; ++i) {
		for (int j = 0; j < user->num_cols; ++j) {
			placeholder = user->canvas[i][j];
			user->canvas[i][j] = user->canvas[i + 1][j];
			user->canvas[i + 1][j] = placeholder;
		}
	}
}

/*
This function deletes some user-specified column in the canvas
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified column number
@return: N/A
*/
void Delete_Col(Canvas* user, int pos) {
	if (!Is_Int_Between_Inclusive(pos, 0, user->num_cols - 1)) {
		printf("\nImproper delete command.\n");

		return;
	}

	Shift_All_Cols_One_Left(user, pos);

	--user->num_cols;

	for (int i = 0; i < user->num_rows; ++i) {
		user->canvas[i] = (char*)realloc(user->canvas[i], user->num_cols * sizeof(char));
	}
}

/*
This function shifts the column at some user-specified column
number in the canvas and all columns to the right of it one to
the left
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@int pos: the user-specified column number
@return: N/A
*/
void Shift_All_Cols_One_Left(Canvas* user, int pos) {
	char placeholder;

	for (int i = 0; i < user->num_rows; ++i) {
		for (int j = pos; j < user->num_cols - 1; ++j) {
			placeholder = user->canvas[i][j];
			user->canvas[i][j] = user->canvas[i][j + 1];
			user->canvas[i][j + 1] = placeholder;
		}
	}
}

/*
This function saves the current state of the canvas to a user-specified text file
@Canvas user: user's canvas, including the canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Save_Command(Canvas user, char* positions) {
	char* file_name = (char*)malloc((strlen(positions) + 1) * sizeof(char));

	sscanf(positions, " %s", file_name);
	free(positions);

	file_name = (char*)realloc(file_name, (strlen(file_name) + 1) * sizeof(char));

	FILE* fp = fopen(file_name, "w");
	free(file_name);
	
	if (fp == NULL) {
		printf("\nImproper save command or file could not be created.\n");
		
		return;
	}

	Write_User_Canvas_Into_File(fp, user);
}

/*
This function copies the current state of the canvas into a user-specified text file
@FILE* fp: file pointer to a user-specified text file opened in write mode
@Canvas user: user's canvas, including the canvas itself and the values for its dimensions
@return: N/A
*/
void Write_User_Canvas_Into_File(FILE* fp, Canvas user) {
	int i, j;

	fprintf(fp, "%d %d", user.num_rows, user.num_cols);

	for (i = (user.num_rows - 1); i >= 0 ; --i) {
		for (j = 0; j < user.num_cols; ++j) {
			fprintf(fp, "%c", user.canvas[i][j]);
		}
	}

	fclose(fp);
}

/*
This function loads the canvas that was previously saved in a user-specified text file
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@return: N/A
*/
void Load_Command(Canvas* user, char* positions) {
	char* file_name = (char*)malloc((strlen(positions) + 1) * sizeof(char));

	sscanf(positions, " %s", file_name);
	free(positions);

	file_name = (char*)realloc(file_name, (strlen(file_name) + 1) * sizeof(char));

	FILE* fp = fopen(file_name, "r");
	free(file_name);

	if (fp == NULL) {
		printf("\nImproper load command or file could not be opened.\n");

		return;
	}

	Read_User_Canvas_From_File(fp, user);
}

/*
This function retrieves the canvas from a user-specified text file
@FILE* fp: file pointer to a user-specified text file opened in read mode
@Canvas* user: address of user's canvas, including the
				canvas itself and the values for its dimensions
@return: N/A
*/
void Read_User_Canvas_From_File(FILE* fp, Canvas* user) {
	int i, j;

	fscanf(fp, "%d %d", &user->num_rows, &user->num_cols);

	user->canvas = (char**)realloc(user->canvas, user->num_rows * sizeof(char*));
	for (i = 0; i < user->num_rows; ++i) {
		user->canvas[i] = (char*)realloc(user->canvas[i], user->num_cols * sizeof(char));
	}
	
	for (i = (user->num_rows - 1); i >= 0; --i) {
		for (j = 0; j < user->num_cols; ++j) {
			fscanf(fp, " %c", &(user->canvas[i][j]));
		}
	}

	fclose(fp);
}