CC := gcc
CCFLAGS := -Wall -c

id3: main.o id3.o
	$(CC) main.o id3.o -o id3

main.o: main.c
	$(CC) $(CCFLAGS) main.c

id3.o: id3.c id3.h
	$(CC) $(CCFLAGS) id3.c

clean:
	rm *.o id3
