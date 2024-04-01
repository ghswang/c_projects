/*
This program has the user create their own canvas
and allows them to manipulate the canvas through
various commands, which includes (but is not limited
to) being able to paint the canvas and saving the
current state of the canvas to a user-named text file
*/

#include <stdio.h>

#include "canvas.h"
#include "input_validation.h"
#include "commands.h"

int main(int argc, char** argv) {
	Canvas user = Create_And_Display_Empty_User_Canvas(argc, argv);

	while (true) {
		printf("Enter your command: ");
		List_Of_Commands(&user);
		Display_Current_State_Canvas(user);
	}

	return 0;
}
