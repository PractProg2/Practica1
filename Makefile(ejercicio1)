

CC = gcc
CFLAG = -Wall -ansi -pedantic

all: exe

exe: p1_e1.o node.o


	$(CC) $(CFLAGS) p1_e1.o node.o -lm -o exe



node.o: node.c node.h types.h

	$(CC) $(CFLAGS) -c node.c

p1_e1.o: p1_e1.c types.h

	 $(CC) $(CFLAGS) -c p1_e1.c


clean: 
	rm -f *.o exe
