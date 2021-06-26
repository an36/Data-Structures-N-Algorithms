CC = gcc
CFLAGS = -g -std=c99
LDFLAGS = -lm

main: main.o teamInfo.o linkedList_teamInfo.o
	$(CC) $(LDFLAGS) -o main main.o teamInfo.o linkedList_teamInfo.o
main.o: main.c
	$(CC) $(CFLAGS)  -c main.c
teamInfo.o: starter_code/teamInfo.c starter_code/teamInfo.h
	$(CC) $(CFLAGS)  -c starter_code/teamInfo.c
linkedList_teamInfo.o: linkedList_teamInfo.c starter_code/teamInfo_LinkedList.h
	$(CC) $(CFLAGS)  -c linkedList_teamInfo.c
