determinant.out: main.o matrix.o determinant.o
	gcc -g -Wall -Werror -o determinant.out main.o matrix.o determinant.o

main.o: main.c matrix.h determinant.h
	gcc -g -Wall -Werror -c main.c

matrix.o: matrix.c matrix.h
	gcc -g -Wall -Werror -c matrix.c

determinant.o: determinant.c determinant.h matrix.h
	gcc -g -Wall -Werror -c determinant.c

clean:
	rm -fr *.o *.out

run:
	./determinant.out simple_3x3_matrix.txt