# author: Shelby Hendrickx

CC = gcc
CFLAGS = -g -Wall -I.

sifs: src/main.o src/sifs.o src/student.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: src/main.c src/sifs.h src/student.h
	$(CC) $(CFLAGS) -c src/main.c

sifs.o: src/sifs.c src/sifs.h
	$(CC) $(CFLAGS) -c src/sifs.c

student.o: src/student.c src/student.h
	$(CC) $(CFLAGS) -c src/student.c

clean:
	$(RM) src/main.o src/sifs.o src/student.o sifs
