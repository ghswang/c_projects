#ifndef INPUT_VALIDATION_H
	#define INPUT_VALIDATION_H

	#include <stdbool.h>

	bool isValidFormat(const int numArgsRead, const int numArgsNeed);
	bool Is_Int_From_Command_Line(char* argv);
	char* Get_Int_From_Command_Line(char* argv);
	bool Is_Int_At_Least(int value, int min_value);
	bool Is_Int_Between_Inclusive(int value, int min_value, int max_value);
	bool Is_Valid_Command_Format(char** positions, int numArgsNeed, char commandType);
	bool Is_Valid_Add_Or_Delete_Command_Format(char* positions, int index,
												int* num_digits_per_arg, int* numCharactersPerArg, int* num_args_read);
	bool Is_Valid_Save_Or_Load_Command_Format(char* positions, int index,
												int* total_num_characters_per_arg, int* num_args_read);
#endif