connectn.out: main.o board.o play_game.o clean_up.o
	gcc -g -Wall -Werror -o connectn.out main.o board.o play_game.o clean_up.o

main.o: main.c board.h
	gcc -g -Wall -Werror -c main.c

board.o: board.c board.h
	gcc -g -Wall -Werror -c board.c

play_game.o: play_game.c play_game.h board.h
	gcc -g -Wall -Werror -c play_game.c

clean_up.o: clean_up.c clean_up.h
	gcc -g -Wall -Werror -c clean_up.c

clean:
	rm -fr *.o *.out

run:
	./connectn.out 3 3 3