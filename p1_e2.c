/**
* @file p1_e2.c
* @author Gonzalo Arcas & Ciro Alonso
* @date 19 February 2020
* @brief segundo ejercicio practica 1
*
* @details Comprobacion de las funciones del TAD Node y del TAD Graph
*
* @see
*/
#include "node.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Node *n2 = NULL;
    Node *n1 = NULL;
    Graph *grafo = NULL;

    n1 = node_init();
    if (!n1) return -1;
    n2 = node_init();
    if (!n2){
        node_free(n1);
        return -1;
    }
    grafo = graph_init();
    if (!grafo){
        node_free(n1);
        node_free(n2);
        return -1;
    }

    node_setName(n1, "first");
    node_setName(n2, "second");

    node_setId(n1, 111);
    node_setId(n2, 222);

    node_setLabel(n1, WHITE);
    node_setLabel(n2, WHITE);

    printf("Insertando nodo 1...resultado...: %d\n", graph_insertNode(grafo, n1));
    printf("Insertando nodo 2...resultado...: %d\n", graph_insertNode(grafo, n2));

    
    graph_insertEdge(grafo, node_getId(n2), node_getId(n1));
    printf("Insertando edge: nodo 2 ---> nodo 1\n");
    

    if (graph_areConnected(grafo, node_getId(n1), node_getId(n2)) == FALSE ){
        printf("Conectados nodo 1 y nodo 2? No\n");
    } else { 
        printf("Conectados nodo 1 y nodo 2? Si\n");
    }

    if (graph_areConnected(grafo,node_getId(n2), node_getId(n1)) == FALSE ){
        printf("Conectados nodo 2 y nodo 1? No\n");
    } else { 
        printf("Conectados nodo 2 y nodo 1? Si\n");
    }

    printf("Insertando nodo 2...resultado...: %d\n", graph_insertNode(grafo, n2));
    
    printf("Grafo\n");
    graph_print(stdout, grafo);

    node_free(n1);
    node_free(n2);
    graph_free(grafo);
    return 0;
}
