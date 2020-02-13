#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1064
struct _Graph
{
    Node *nodes[MAX_NODES];                 /*!<Array with the graph nodes */
    Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
    int num_nodes;                          /*!<Total number of nodes in te graph */
    int num_edges;                          /*!<Total number of connection in the graph */
};


//funciones privadas

int find_node_index(const Graph * g, long nId1);

int* graph_getConnectionsIndex (const Graph * g, int index);


// It returns the index of the node with id nId1
int find_node_index(const Graph *g, long nId1){
    int i;
    if (!g) return -1;

    for (i = 0; i < g->num_nodes; i++){

        if (node_getId(g->nodes[i]) == nId1) return i;
    }
    // ID not found
    return -1;
}

// It returns an array with the indices of the nodes connected to the node
// whose index is index
// It also allocates memory for the array.
int *graph_getConnectionsIndex(const Graph *g, int index)
{
    int *array = NULL, i, j = 0, sizeNConnect;

    if (!g) return NULL;

    if (index < 0 || index > g->num_nodes) return NULL;

    // get memory for the array
    sizeNConnect = node_getConnect(g->nodes[index]);
    array = (int *)malloc(sizeNConnect * sizeof(int));
    if (!array){
        // print error message
        //fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    // assign values to the array with the indices of the connected nodes
    for (i = 0; i < g->num_nodes; i++){
        if (g->connections[index][i] == TRUE){
            array[j++] = i;
        }
    }
    return array;
}

//Interfaz publica

Graph *graph_init(){
    Graph *g = NULL;
    int i, j;

    g = (Graph *) malloc (sizeof(Graph));
    if (!g) return NULL;

    g->num_nodes = 0;
    g->num_edges = 0;
    for (i=0; i<MAX_NODES; i++){
        g->nodes[i] = NULL;
        for (j=0; j<MAX_NODES; j++){
            g->connections[i][j] = FALSE;
        }
    }

    return g;
}

void graph_free(Graph *g){
    int i;

    for (i=0; i<MAX_NODES; i++){
        free(g->nodes[i]);
    }

    free(g);
}


Status graph_insertNode(Graph *g, const Node *n){
    Node *aux = NULL;
    int index = -1;
    if (!g || !n) return ERROR;

    aux = node_copy(n);
    if (!aux) return ERROR;

    index = find_node_index(g, node_getId(aux));
    if ((index) != -1){
        if (node_cmp(g->nodes[index], aux) == 0){
            free(aux);
            return ERROR;
        }
        free (g->nodes[index]);
        g->nodes[index] = aux;
        return OK;
    }

    g->num_nodes++;
    g->nodes[g->num_nodes] = aux;
     
    return OK;
}

Status graph_insertEdge(Graph *g, const long nId1, const long nId2){
    int index = -1;
    int cont;
    if (!g) return ERROR;

    g->connections[nId1][nId2] = TRUE;
    g->num_edges++;
    index = find_node_index(g, nId1);
    cont = node_getConnect(g->nodes[index]);
    node_setNConnect(g->nodes[index], cont++);

    return OK;
}

Node *graph_getNode(const Graph *g, long nId){
    Node *aux = NULL;
    int index = -1;

    if (!g) return NULL;
    
    index = find_node_index(g, nId);
    aux = node_copy(g->nodes[index]);
    return aux;
}

Status graph_setNode(Graph *g, const Node *n){
    int index = -1;
    if (!g || !n) return ERROR;

    index = find_node_index(g, node_getId(n));
    node_setName(g->nodes[index], node_getName((Node *)n));
    node_setLabel(g->nodes[index], node_getLabel(n));
    node_setNConnect(g->nodes[index], node_getConnect(n));
    return OK;
}

long *graph_getNodesId(const Graph *g){
    long *aux = NULL;
    int i;
    
    if (!g) return NULL;

    aux = (long *) malloc(g->num_nodes * sizeof(long));
    if (!aux) return NULL;
    
    for (i=0; i<g->num_nodes; i++){
        aux[i] = node_getId(g->nodes[i]);
    }

    return aux;
}

int graph_getNumberOfNodes(const Graph *g){
    if (!g) return -1;

    return g->num_nodes;
}

int graph_getNumberOfEdges(const Graph *g){
    if (!g) return -1;

    return g->num_edges;
}

Bool graph_areConnected(const Graph *g, const long nId1, const long nId2){
    if (!g) return FALSE;

    return g->connections[nId1][nId2];
}

int graph_getNumberOfConnectionsFrom(const Graph *g, const long fromId){
    int index = -1;
    if (!g) return -1;
    
    index = find_node_index(g, fromId);
    return node_getConnect(g->nodes[index]);
}

long *graph_getConnectionsFrom(const Graph *g, const long fromId){
    long *cast = NULL;
    if (!g) return NULL;

    int aux = find_node_index(g, fromId);

    cast = (long *) graph_getConnectionsIndex(g, aux);
    return cast;
}

int graph_print(FILE *pf, const Graph *g){
    int cont=0, i, j;
    long *array = NULL;
    if (!pf || !g) return -1;
    
    for (i=0; i < g->num_nodes; i++){
        cont += node_print(pf, g->nodes[i]);
        printf("\n");

        /*da error en la funcion graph_getConnectionsIndex
        array = graph_getConnectionsFrom((Graph *)g, node_getId(g->nodes[i]));

        if (!array) return -1;

        for (j=0; (j < g->num_nodes) && (array[j]!= 0); j++){
            cont += fprintf(pf, " %ld", array[j]);
        }
        free(array);
        */
    }
    return cont;
}

