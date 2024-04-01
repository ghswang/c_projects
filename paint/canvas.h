#ifndef CANVAS_H
	#define CANVAS_H

	typedef struct Canvas_struct {
		int num_rows, num_cols;
		char** canvas;
	} Canvas;

	Canvas Create_And_Display_Empty_User_Canvas(int argc, char** argv);
	void Create_Empty_Canvas(Canvas* user);
	void Display_Current_State_Canvas(Canvas user);
#endif