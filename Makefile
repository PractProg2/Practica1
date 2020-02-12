

CC = gcc
CFLAG = -Wall -ansi -pedantic

all: p1_e2

p1_e2: p1_e2.o node.o graph.o


	$(CC) $(CFLAGS) p1_e2.o node.o graph.o -lm -o p1_e2



node.o: node.c node.h types.h

	$(CC) $(CFLAGS) -c node.c

p1_e2.o: p1_e2.c types.h

	$(CC) $(CFLAGS) -c p1_e2.c

graph.o: graph.c graph.h node.h types.h

	$(CC) $(CFLAGS) -c graph.c

clean: 
	rm -f *.o p1_e2
