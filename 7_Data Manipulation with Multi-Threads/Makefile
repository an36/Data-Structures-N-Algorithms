CC=gcc
FLAGS= -std=c99 -Wall -lm
.PHONY: all
all:
	make thread mthread
thread: thrd.o
	$(CC) -o thread thrd.o -lpthread $(FLAGS)
thrd.o: thrd.c
	$(CC) -c thrd.c -lpthread  $(FLAGS)
mthread: mthread.o
	$(CC) -o mthread mthread.o -lpthread $(FLAGS)
mthread.o: mthread.c
	$(CC) -c mthread.c -lpthread $(FLAGS)
.PHONY: clean
clean:
	rm thrd.o thread mthread.o mthread
