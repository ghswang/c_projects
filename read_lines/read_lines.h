#ifndef READ_LINES_H
	#define READ_LINES_H

	#include <stdio.h>

	void read_lines(FILE* fp, char*** lines, int* num_lines);
	void read_one_line(FILE* fp, char*** lines, int* num_lines);
#endif