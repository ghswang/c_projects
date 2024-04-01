/*
This program is responsible for determining
the validity of user inputs
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "input_validation.h"

/*
COPIED FROM "input_validation.c" IN CLASS GOOGLE DRIVE!

This function determines whether or not the user has entered a
certain number of desired arguments
@const int numArgsRead: the number of arguments read
@const int numArgsNeed: the desired amount of arguments
@return: bool value of true if the number of arguments read is
			equal to the desired amount of arguments; bool value of false otherwise
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
This function determines whether or not there
exists an integer from a command line argument
@char* argv: string that represents a command line argument
@return: bool value of true if there exists an integer from
			the command line argument; bool value of false otherwise
*/
bool Is_Int_From_Command_Line(char* argv) {
	int num_digits = 0;
	
	for (int i = 0; i < strlen(argv); ++i) {
		if (!isdigit(argv[i])) {
			if (argv[i] == '-' || isalpha(argv[i]) || isspace(argv[i]) || 
					(ispunct(argv[i]) && argv[i] != '.')) {
				
				continue;
			}

			return false;
		}
		else if (isdigit(argv[i])) {
			++num_digits;
		}
	}

	if (num_digits == 0) {
		return false;
	}

	return true;
}

/*
This function obtains an integer from a command line argument,
assuming that there exists an integer from the command line argument
in the first place
@char* argv: string that represents a command line argument
@return: string containing an integer that was extracted from the command line argument
*/
char* Get_Int_From_Command_Line(char* argv) {
	char* value = NULL;
	int num_chars = 0;
	
	for (int i = 0; i < strlen(argv); ++i) {
		if(isdigit(argv[i]) || argv[i] == '-') {
			++num_chars;
			
			value = (char*)realloc(value, (num_chars + 1) * sizeof(char));
			value[num_chars - 1] = argv[i];
		}
	}

	value[num_chars] = '\0';

	return value;
}

/*
This function determines whether or not an integer
is at least (i.e. greater than or equal to) some value
@int value: integer in question
@int min_value: minimum value that is compared with the integer in question
@return: bool value of true if the integer in question is greater than or
			equal to the minimum value; bool value of false otherwise
*/
bool Is_Int_At_Least(int value, int min_value) {
	return value >= min_value;
}

/*
This function determines whether or not an integer
is between two other values, inclusive
@int value: integer in question
@int min_value: minimum value that is compared with the integer in question
@int min_value: maximum value that is compared with the integer in question
@return: bool value of true if the integer in question is greater than or
			equal to the minimum value and less than or equal to the
			maximum value; bool value of false otherwise
*/
bool Is_Int_Between_Inclusive(int value, int min_value, int max_value) {
	return value >= min_value && value <= max_value;
}

/*
This function determines whether or not the user's input 
for a command is in the correct format (excluding the
quit and help commands)
@char** positions: address of a string that represents the user's input
					excluding the very first character the user entered
@int numArgsNeed: the exact number of arguments the command requires
@char commandType: a starting letter that corresponds to a certain command
@return: bool value of true if the user's input for a command is in the correct
			format; bool value of false otherwise
*/
bool Is_Valid_Command_Format(char** positions, int numArgsNeed, char commandType) {
	char curr_character;
	int i, num_chars = 0;

	do {
		scanf("%c", &curr_character);
		++num_chars;

		*positions = (char*)realloc(*positions, (num_chars + 1) * sizeof(char));
		(*positions)[num_chars - 1] = curr_character;
	} while (curr_character != '\n');

	(*positions)[num_chars] = '\0';

	int num_args_read = 0, num_digits_per_arg = 0;

	if (!isspace((*positions)[0])) {
		return false;
	}
	else if (commandType == 'a' || commandType == 'd') {
		int numCharactersPerArg = 0;
		
		for (i = 1; i < num_chars; ++i) {
			if (!Is_Valid_Add_Or_Delete_Command_Format(*positions, i,
														&num_digits_per_arg, &numCharactersPerArg, &num_args_read)) {
				
				return false;
			}
		}
	}
	else if (commandType == 's' || commandType == 'l') {
		int total_num_characters_per_arg = 0;

		for (i = 1; i < num_chars; ++i) {
			if (!Is_Valid_Save_Or_Load_Command_Format(*positions, i,
														&total_num_characters_per_arg, &num_args_read)) {
		
				return false;
			}
		}
	}
	else {
		for (i = 1; i < num_chars; ++i) {
			if (!isdigit((*positions)[i]) && !isspace((*positions)[i])) {
				return false;
			}
			else if (isdigit((*positions)[i])) {
				++num_digits_per_arg;
			}
			else if (isspace((*positions)[i]) && num_digits_per_arg > 0) {
				++num_args_read;
				num_digits_per_arg = 0;
			}
		}
	}

	if (num_args_read != numArgsNeed) {
		return false;
	}

	return true;
}

/*
This function determines whether or not the user's input 
for the add or delete command are in the correct format,
going character by character to do so
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@int index: index number corresponding to a particular character within
				positions
int* num_digits_per_arg: address of the value representing the number of
							digits within every argument that the user entered
int* numCharactersPerArg: address of the value representing the number of
							characters within every argument that the user entered
int* num_args_read: address of the value representing how many arguments the user entered
@return: bool value of true if the user's input is valid for either the add or delete command,
			going character by character; bool value of false otherwise						
*/
bool Is_Valid_Add_Or_Delete_Command_Format(char* positions, int index,
											int* num_digits_per_arg, int* numCharactersPerArg, int* num_args_read) {
	
	if (!isalnum(positions[index]) && !isspace(positions[index])) {
		return false;
	}
	else if (isalpha(positions[index])) {
		++*numCharactersPerArg;

		if (*num_args_read >= 1 || *numCharactersPerArg > 1 ||
			(positions[index] != 'r' && positions[index] != 'c')) {
		
			return false;
		}
	}		
	else if (isdigit(positions[index])) {
		++*num_digits_per_arg;
	}
	else if (isspace(positions[index]) && (*numCharactersPerArg > 0 || *num_digits_per_arg > 0)) {
		++*num_args_read;
		*numCharactersPerArg = 0;
		*num_digits_per_arg = 0;
	}

	return true;
}

/*
This function determines whether or not the user's input 
for the save or load command are in the correct format,
going character by character to do so
@char* positions: string that represents the user's input
					excluding the very first character the user entered
@int index: index number corresponding to a particular character within
				positions
@int* total_num_characters_per_arg: address of the value representing the
							total number of characters within every argument
							that the user entered
int* num_args_read: address of the value representing how many arguments the user entered
@return: bool value of true if the user's input is valid for either the save or load command,
			going character by character; bool value of false otherwise	
*/
bool Is_Valid_Save_Or_Load_Command_Format(char* positions, int index,
											int* total_num_characters_per_arg, int* num_args_read) {
	
	if (!isspace(positions[index])) {
		++*total_num_characters_per_arg;
	}
	else if (isspace(positions[index]) && *total_num_characters_per_arg > 0) {
		++*num_args_read;
		*total_num_characters_per_arg = 0;

		if (*num_args_read > 1) {
			return false;
		}
	}

	return true;
}