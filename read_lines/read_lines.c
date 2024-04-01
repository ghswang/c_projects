#include <stdlib.h>
#include <stdio.h>

#include "read_lines.h"

/*
This function reads a file one line at a time and copies
the line into an array organized by line number
@FILE* fp: a file pointer opened in read mode
@char*** lines: a pointer indicating where the lines should be placed; if there are no lines in a file, lines will be set to NULL 
@int* num_lines: pointer to the number of lines; determines the line number for lines and where each corresponding line will be placed within lines
@return: N/A
*/
void read_one_line(FILE* fp, char*** lines, int* num_lines) {
	int total_num_characters = 0;
	char curr_character;
	
	if (fread(&curr_character, sizeof(char), 1, fp) != 1) { // OR fscanf(fp, "%c", &curr_character) != 1
		if (feof(fp) && *num_lines > 0) {
			return;
		}

		*lines = NULL;
		return;
	}
	else if (curr_character == '\n') {
		++total_num_characters;
		++(*num_lines);

		if (*num_lines == 1) {
			*lines = (char**)malloc(*num_lines * sizeof(char*));
			(*lines)[*num_lines - 1] = (char*)malloc((total_num_characters + 1) * sizeof(char));
			fseek(fp, -total_num_characters, SEEK_CUR);
			fread((*lines)[*num_lines - 1], sizeof(char), total_num_characters, fp);
			(*lines)[*num_lines - 1][total_num_characters] = '\0';
		}
		else {
			*lines = (char**)realloc(*lines, *num_lines * sizeof(char*));
			(*lines)[*num_lines - 1] = (char*)malloc((total_num_characters + 1) * sizeof(char));
			fseek(fp, -total_num_characters, SEEK_CUR);	
			fread((*lines)[*num_lines - 1], sizeof(char), total_num_characters, fp);
			(*lines)[*num_lines - 1][total_num_characters] = '\0';
		}

		return;
	}

	++total_num_characters;

	while (!feof(fp) && curr_character != '\n') {
		if (fread(&curr_character, sizeof(char), 1, fp) == 1) { //OR fscanf(fp, "%c", &curr_character) == 1
			++total_num_characters;
		}
		else {
			break;
		}
	}

	++(*num_lines);

	if (*num_lines == 1) {
		*lines = (char**)malloc(*num_lines * sizeof(char*));
		(*lines)[*num_lines - 1] = (char*)malloc((total_num_characters + 1) * sizeof(char));
		fseek(fp, -total_num_characters, SEEK_CUR);
		fread((*lines)[*num_lines - 1], sizeof(char), total_num_characters, fp);
		(*lines)[*num_lines - 1][total_num_characters] = '\0';
	}
	else {
		*lines = (char**)realloc(*lines, *num_lines * sizeof(char*));
		(*lines)[*num_lines - 1] = (char*)malloc((total_num_characters + 1) * sizeof(char));
		fseek(fp, -total_num_characters, SEEK_CUR);
		fread((*lines)[*num_lines - 1], sizeof(char), total_num_characters, fp);
		(*lines)[*num_lines - 1][total_num_characters] = '\0';
	}
}

void read_lines(FILE* fp, char*** lines, int* num_lines) {
	/*
			read all of the lines in fp into lines and set num_lines to be the total number of lines in the file.
			@fp: a file pointer opened in read mode
			@lines: a pointer indicating where the lines should be placed. If there are no lines in a file, lines
							will be set to NULL
			@num_lines: a pointer to the number of lines. set to the number of lines contained within lines
			@modifies: lines, num_lines
	*/
	
	*num_lines = 0;

	while (!feof(fp)) {
		read_one_line(fp, lines, num_lines);
	}
}