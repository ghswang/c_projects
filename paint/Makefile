paint.out: main.o canvas.o input_validation.o commands.o
	gcc -g -Wall -Werror -o paint.out main.o canvas.o input_validation.o commands.o

main.o: main.c canvas.h input_validation.h commands.h
	gcc -g -Wall -Werror -c main.c

canvas.o: canvas.c canvas.h input_validation.h
	gcc -g -Wall -Werror -c canvas.c

input_validation.o: input_validation.c input_validation.h
	gcc -g -Wall -Werror -c input_validation.c

commands.o: commands.c commands.h canvas.h input_validation.h
	gcc -g -Wall -Werror -c commands.c

clean:
	rm -fr *.o *.out

run:
	./paint.out							