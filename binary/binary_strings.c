/*
This program takes in a user's binary
string containing possibly any number
of x's and/or X's and displays all the
possible configurations of their string
in binary
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Get_All_Configurations_Bin_Str(char* bin_str, int len);
void R_Get_All_Configurations_Bin_Str(char* bin_str, int len, int starting_index);

/*
This function initializes the call to the recursive function
that will display all the possible configurations of the user's
binary string
@char* bin_str: user's binary string
@int len: number of characters in user's binary string
@return: N/A
*/
void Get_All_Configurations_Bin_Str(char* bin_str, int len) {
	return R_Get_All_Configurations_Bin_Str(bin_str, len, 0);
}

/*
This recursive function displays all the possible configurations
of the user's binary string by replacing every occurrence of x or
X with either 0 or 1
@char* bin_str: user's binary string
@int len: number of characters in user's binary string
@int starting_index: starting point for checking every character in the user's binary string
@return: N/A
*/
void R_Get_All_Configurations_Bin_Str(char* bin_str, int len, int starting_index) {
	if (starting_index == len) {
		printf("%s\n\n", bin_str);
		return;
	}

	if (bin_str[starting_index] == 'x' || bin_str[starting_index] == 'X') {
		bin_str[starting_index] = '0';
		R_Get_All_Configurations_Bin_Str(bin_str, len, starting_index + 1);

		bin_str[starting_index] = '1';
		R_Get_All_Configurations_Bin_Str(bin_str, len, starting_index + 1);

		bin_str[starting_index] = 'X';
	}
	else {
		R_Get_All_Configurations_Bin_Str(bin_str, len, starting_index + 1);
	}
}

int main(int argc, char** argv) {
	int len = strlen(argv[1]);
	char* bin_str = (char*)malloc((len + 1) * sizeof(char));
	strcpy(bin_str, argv[1]);

	Get_All_Configurations_Bin_Str(bin_str, len);
	free(bin_str);

	return 0;
}
