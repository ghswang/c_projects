/*
This program is responsible for canvas-related
functions and/or operations
*/

#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "input_validation.h"

/*
This function creates and displays a canvas
with valid user-specified dimensions; otherwise, it
creates and displays a 10x10 canvas to the user
@int argc: number of command line arguments
@char** argv: array of strings, where each string represents a separate command line argument
@return: empty canvas with either valid user-specified dimensions or default (i.e. 10x10) dimensions
*/
Canvas Create_And_Display_Empty_User_Canvas(int argc, char** argv) {
	Canvas user = {10, 10, NULL};
	
	if (argc != 3) {
		if (argc == 1) {
			user.num_rows = 10, user.num_cols = 10;
		}
		else {
			printf("\nWrong number of command line arguments entered.\n");
			printf("Usage: ./paint.out [num_rows num_cols]\n");
			printf("Making default board of 10 X 10.\n");
		}
	}
	else if (Is_Int_From_Command_Line(argv[1]) && Is_Int_From_Command_Line(argv[2])) {
		char* argv1;
		char* argv2;

		argv1 = Get_Int_From_Command_Line(argv[1]);
		argv2 = Get_Int_From_Command_Line(argv[2]);

		sscanf(argv1, "%d", &user.num_rows);
		sscanf(argv2, "%d", &user.num_cols);

		free(argv1);
		free(argv2);

		if (!Is_Int_At_Least(user.num_rows, 1) && Is_Int_At_Least(user.num_cols, 1)) {
			printf("\nThe number of rows is less than 1.\n");
			printf("Making default board of 10 X 10.\n");
			user.num_rows = 10, user.num_cols = 10;
		}
		else if (Is_Int_At_Least(user.num_rows, 1) && !Is_Int_At_Least(user.num_cols, 1)) {
			printf("\nThe number of columns is less than 1.\n");
			printf("Making default board of 10 X 10.\n");
			user.num_rows = 10, user.num_cols = 10;
		}
		else if (!Is_Int_At_Least(user.num_rows, 1) && !Is_Int_At_Least(user.num_cols, 1)) {
			printf("\nThe number of rows is less than 1.\n");
			printf("The number of columns is less than 1.\n");
			printf("Making default board of 10 X 10.\n");
			user.num_rows = 10, user.num_cols = 10;
		}
	}
	else if (!Is_Int_From_Command_Line(argv[1]) && Is_Int_From_Command_Line(argv[2])) {
		printf("\nThe number of rows is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
	}
	else if (Is_Int_From_Command_Line(argv[1]) && !Is_Int_From_Command_Line(argv[2])) {
		printf("\nThe number of columns is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
	}
	else {
		printf("\nThe number of rows is not an integer.\n");
		printf("The number of columns is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
	}

	Create_Empty_Canvas(&user);
	Display_Current_State_Canvas(user);

	return user;
}

/*
This function creates an empty canvas with
either valid user-specified dimenions or 
with default (i.e. 10x10) dimensions
@Canvas* user: address of user's canvas, including the canvas itself and the values for its dimensions
@return: N/A
*/
void Create_Empty_Canvas(Canvas* user) {
	int i, j;
	
	user->canvas = (char**)malloc(user->num_rows * sizeof(char*));

	for (i = (user->num_rows - 1); i >= 0; --i) {
		user->canvas[i] = (char*)malloc(user->num_cols * sizeof(char));
		
		for (j = 0; j < user->num_cols; ++j) {
			user->canvas[i][j] = '*';
		}
	}
}


/*
This function displays the current state of the
canvas to the user, detailing the corresponding row
numbers and columns numbers on the very left side and
bottom side of the canvas, respectively
@Canvas user: user's canvas, including the canvas itself and the values for its dimensions
@return: N/A
*/
void Display_Current_State_Canvas(Canvas user) {
	int i, j;
	
	printf("\n");

	for (i = (user.num_rows - 1); i >= 0 ; --i) {
		printf("%d ", i);
		
		for (j = 0; j < user.num_cols; ++j) {
			printf("%c ", user.canvas[i][j]);
		}

		printf("\n");
	}	

	printf("  ");

	for (j = 0; j < user.num_cols; ++j) {
		printf("%d ", j);
	}

	printf("\n\n");
}