# Makefile creado por: Gonzalo Arcas Castrosín y Ciro Alonso Aquino, G2111 Pareja 7


# Para compilar el ejercicio1 de la practica 1 (p1_e1) utilizas el comando "make e1" y lo borras con "make clean"
# Para ejecutar el ejercicio1 de la practica 1 (p1_e1) utilizas el comando "./ p1_e1"

# Para compilar el ejercicio2 de la practica 2 (p1_e2) utilizas el comando "make e2" y lo borras con "make clean"
# Para ejecutar el ejercicio2 de la practica 2 (p1_e2) utilizas el comando "./ p1_e2"

# Para compilar el ejercicio3 de la practica 3 (p1_e3) utilizas el comando "make e3" y lo borras con "make clean"
# Para ejecutar el ejercicio3 de la practica 3 (p1_e3) utilizas el comando "./ p1_e3 test.txt"

# <test.txt> es nuestro fichero de texto del ejercicio p1_e3



CC = gcc
CFLAG = -g -Wall -ansi -pedantic

e1: p1_e1

p1_e1: p1_e1.o node.o


	$(CC) $(CFLAGS) p1_e1.o node.o -lm -o p1_e1


e2: p1_e2

p1_e2: p1_e2.o node.o graph.o


	$(CC) $(CFLAGS) p1_e2.o node.o graph.o -lm -o p1_e2


e3: p1_e3

p1_e3: p1_e3.o node.o graph.o


	$(CC) $(CFLAGS) p1_e3.o node.o graph.o -lm -o p1_e3



node.o: node.c node.h types.h

	$(CC) $(CFLAGS) -c node.c

p1_e1.o: p1_e1.c types.h

	$(CC) $(CFLAGS) -c p1_e1.c

p1_e2.o: p1_e2.c types.h

	$(CC) $(CFLAGS) -c p1_e2.c

p1_e3.o: p1_e3.c types.h

	$(CC) $(CFLAGS) -c p1_e3.c

graph.o: graph.c graph.h node.h types.h

	$(CC) $(CFLAGS) -c graph.c

clean: 
	rm -f *.o p1_e1 p1_e2 p1_e3
