C = gcc
CFLAGS = -g -std=c99
LDFLAGS = -lm

main: main.o teamInfo.o hash_table.o
	$(CC) $(LDFLAGS) -o main main.o teamInfo.o hash_table.o
main.o: main.c
	$(CC) $(CFLAGS)  -c main.c
teamInfo.o: starter_code/teamInfo.c starter_code/teamInfo.h
	$(CC) $(CFLAGS)  -c starter_code/teamInfo.c
hash_table.o: starter_code/hash_table.c starter_code/hash_table.h
	$(CC) $(CFLAGS)  -c starter_code/hash_table.c
