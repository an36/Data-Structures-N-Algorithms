CC=gcc
FLAGS= -std=c99 -Wall -lm
.PHONY: all
all:
	make twist xor tx
twist: twist.o
	$(CC) -o twist twist.o $(FLAGS)
twist.o: twist.c
	$(CC) -c twist.c $(FLAGS)
xor: xor.o
	$(CC) -o xor xor.o $(FLAGS)
xor.o: xor.c
	$(CC) -c xor.c $(FLAGS)
tx: tx.o
	$(CC) -o tx tx.o $(FLAGS)
tx.o: tx.c
	$(CC) -c tx.c $(FLAGS)
.PHONY: clean
clean:
	rm twist.o twist xor.o xor tx.o tx

