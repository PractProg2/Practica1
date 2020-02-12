#include "node.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Node *nodazo = NULL;
    Node *nodito = NULL;
    Graph *grafo = NULL;

    nodito = node_init();
    if (!nodito) return -1;
    nodazo = node_init();
    if (!nodazo){
        node_free(nodito);
        return -1;
    }
    grafo = graph_init();
    if (!grafo){
        node_free(nodito);
        node_free(nodazo);
        return -1;
    }

    node_setName(nodito, "first");
    node_setName(nodazo, "second");

    node_setId(nodito, 111);
    node_setId(nodazo, 222);

    node_setLabel(nodito, WHITE);
    node_setLabel(nodazo, WHITE);

    printf("Insertando nodo 1...resultado...: %d\n", graph_insertNode(grafo, nodito));
    printf("Insertando nodo 2...resultado...: %d\n", graph_insertNode(grafo, nodazo));

    printf("Insertando edge: nodo 2 ---> nodo 1\n");
    graph_insertEdge(grafo, node_getId(nodazo), node_getId(nodito));

    if (graph_areConnected(grafo, node_getId(nodito), node_getId(nodazo)) == FALSE ){
        printf("Conectados nodo 1 y nodo 2? No\n");
    } else { 
        printf("Conectados nodo 1 y nodo 2? Si\n");
    }

    if (graph_areConnected(grafo, node_getId(nodazo), node_getId(nodito)) == FALSE ){
        printf("Conectados nodo 2 y nodo 1? No\n");
    } else { 
        printf("Conectados nodo 2 y nodo 1? Si\n");
    }

    printf("Insertando nodo 2...resultado...: %d\n", graph_insertNode(grafo, nodazo));

    printf("Grafo \n");
    graph_print(grafo);

    node_free(nodito);
    node_free(nodazo);
    graph_free(grafo);
    return 0;
}