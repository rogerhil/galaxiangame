CC = gcc
CFLAGS = -g -c -Wall -lglut -lGL -lboost_regex
LIB1 = -lm
main: game.o globalconsts.o mainlib.o events.o functions.o ship.o weapons.o enemies.o background.o scenes.o main.o
	$(CC) -g -Wall -lglut -lGL -Xlinker -zmuldefs -lboost_regex game.o globalconsts.o mainlib.o events.o functions.o ship.o weapons.o enemies.o background.o scenes.o main.o -o main $(LIB1)

main.o: main.cpp main.H
	$(CC) $(CFLAGS) -o main.o main.cpp

game.o: game.cpp game.H
	$(CC) $(CFLAGS) -o game.o game.cpp

globalconsts.o: globalconsts.cpp globalconsts.H
	$(CC) $(CFLAGS) -o globalconsts.o globalconsts.cpp

mainlib.o: mainlib.cpp mainlib.H
	$(CC) $(CFLAGS) -o mainlib.o mainlib.cpp

events.o: events.cpp events.H
	$(CC) $(CFLAGS) -o events.o events.cpp

functions.o: functions.cpp functions.H
	$(CC) $(CFLAGS) -o functions.o functions.cpp

enemies.o: enemies.cpp enemies.H
	$(CC) $(CFLAGS) -o enemies.o enemies.cpp

weapons.o: weapons.cpp weapons.H
	$(CC) $(CFLAGS) -o weapons.o weapons.cpp

ship.o: ship.cpp ship.H
	$(CC) $(CFLAGS) -o ship.o ship.cpp

background.o: background.cpp background.H
	$(CC) $(CFLAGS) -o background.o background.cpp

scenes.o: scenes.cpp scenes.H
	$(CC) $(CFLAGS) -o scenes.o scenes.cpp

run: main
	./main
clean:
	\rm -rf main *.o *.cpp~ *.H~ Makefile~ *gz |clear

pack:
	tar cvzf main.tar.gz *.cpp *.H Makefile

	