/*
This program reads a user-given binary file
containing or encoded with a specific 2D convex
shape and determines the perimeter of it
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Coordinate_struct {
	int x_coord;
	int y_coord;
} Coordinate;

void Get_All_Vertex_Coords(FILE* fp, Coordinate** vertex, int num_vertices);
double Calc_Perimeter(Coordinate* vertex, int num_vertices);
double Calc_Distance_Btwn_Two_Vertices(Coordinate first_vertex, Coordinate second_vertex);

/*
This function obtains the x and y coordinates for each individual
vertex/point of the 2D convex shape encoded within the user's binary file
@FILE* fp: file pointer to user's binary file opened in read mode
@Coordinate** vertex: address of pointer to all individual vertices/points of the 2D convex shape
@int num_vertices: number of vertices/points of the 2D convex shape
@return: N/A
*/
void Get_All_Vertex_Coords(FILE* fp, Coordinate** vertex, int num_vertices) {
	for (int i = 0; i < num_vertices; ++i) {
		fread(&((*vertex + i)->x_coord), sizeof(int), 1, fp);
		fread(&((*vertex + i)->y_coord), sizeof(int), 1, fp);

		/*
		OR 

		fread(&((*vertex)[i].x_coord), sizeof(int), 1, fp); 
		fread(&((*vertex)[i].y_coord), sizeof(int), 1, fp);
		*/
	}	
}

/*
This function calculates the perimeter of the 2D convex shape
encoded within the user's binary file
@Coordinate* vertex: pointer to all individual vertices/points of the 2D convex shape
@int num_vertices: number of vertices/points of the 2D convex shape
@return: perimeter of the 2D convex shape
*/
double Calc_Perimeter(Coordinate* vertex, int num_vertices) {
	double perimeter = 0;

	for (int i = 0; i < (num_vertices - 1); ++i) {
		perimeter += Calc_Distance_Btwn_Two_Vertices(vertex[i], vertex[i + 1]);
	}

	perimeter += Calc_Distance_Btwn_Two_Vertices(vertex[num_vertices - 1], vertex[0]);

	return perimeter;
}

/*
This function calculates the distance between two vertices/points
(i.e. length of a edge/side) from the 2D convex shape
@Coordinate first_vertex: first vertex/point from the 2D convex shape
@Coordinate second_vertex: second vertex/point from the 2D convex shape
@return: distance between two vertices/points (i.e. length of a edge/side)
*/
double Calc_Distance_Btwn_Two_Vertices(Coordinate first_vertex, Coordinate second_vertex){
	double dist;
	
	dist = sqrt(pow(second_vertex.x_coord - first_vertex.x_coord, 2) + pow(second_vertex.y_coord - first_vertex.y_coord, 2));

	return dist;
}

int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "rb");

	int num_vertices;
	fread(&num_vertices, sizeof(int), 1, fp);

	Coordinate* vertex = (Coordinate*)malloc(num_vertices * sizeof(Coordinate));
	Get_All_Vertex_Coords(fp, &vertex, num_vertices);

	double perimeter = Calc_Perimeter(vertex, num_vertices);
	printf("The perimeter is %.2lf\n\n", perimeter);

	free(vertex);

	return 0;
}