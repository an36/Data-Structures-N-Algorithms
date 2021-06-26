CC=gcc
FLAGS= -std=c99 -Wall -lm

.PHONY: all
all:
	make mqg.exe	
mqg.exe: main.o
	$(CC) -o mqg.exe main.o $(FLAGS)
main.o: main.c
	$(CC) -c main.c $(FLAGS)
# Clean targets
.PHONY: clean
clean:
	rm main.o mqg
