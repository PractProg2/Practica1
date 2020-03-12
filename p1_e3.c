/**
* @file p1_e3.c
* @author Gonzalo Arcas & Ciro Alonso
* @date 19 February 2020
* @brief tercer ejercicio practica 1
*
* @details Comprobacion de la funcion graph_readFromFile
*
* @see
*/
#include "node.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    Graph *grafo = NULL;
    FILE *fin = NULL;
    if (argc < 1 || argv[1] == NULL){
        fprintf(stderr, "<Falta introducir el nombre del fichero que se quiere leer>\n");
        return -1;
    }
    grafo = graph_init();
    if (!grafo){
        return -1;
    }

    fin = fopen(argv[1], "r");
    if (!fin ) return ERROR;
    
    if (graph_readFromFile(fin, grafo) == ERROR) return -1;

    graph_print(stdout, grafo);


    fclose(fin);
    graph_free(grafo);
}
