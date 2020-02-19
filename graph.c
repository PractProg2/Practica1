/**
* @file graph.c
* @author Gonzalo Arcas & Ciro Alonso
* @date 19 February 2020
* @brief ADT graph
*
* @details Definicion de las funciones de graph.h
*
* @see
*/

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

#define MAX_NODES 1064
#define NAME_L 64 /*!< Maximum node name length */

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
    int index = -1, i;
    if (!g || !n || g->num_nodes >= MAX_NODES) return ERROR;

    aux = node_copy(n);
    if (!aux) return ERROR;

    for (i=0; i<g->num_nodes; i++){
        if (node_getId(g->nodes[i]) == node_getId(aux)){
            if (node_cmp(g->nodes[i], aux) == 0){
                free(aux);
                return ERROR;
            }
            free (g->nodes[i]);
            g->nodes[i] = aux;
            return ERROR;
        }
    }

    
    g->nodes[i] = aux;
    node_setNConnect(g->nodes[i],0);
    g->num_nodes++;
    return OK;
}

Status graph_insertEdge(Graph *g, const long nId1, const long nId2){
    int index = -1;
    int cont=0;
    if (!g) return ERROR;

    if (g->connections[nId1][nId2]== TRUE){
        return ERROR;
    }
    g->connections[nId1][nId2] = TRUE;
    g->num_edges++;
    
    for (int i=0; i<g->num_nodes; i++){
        if (node_getId(g->nodes[i]) == nId1){
            cont = node_getConnect(g->nodes[i]);
            cont = cont +1;
            node_setNConnect(g->nodes[i], cont);
        }
    }
    

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
    int cont=0, i, j, index;

    if (!pf || !g){
        fprintf(stderr, "%s", strerror(errno)); 
        return -1;
    }
    
    for (i=0; i < g->num_nodes; i++){
        int suma = 0, cont1 = 0;
        suma = node_print(pf, g->nodes[i]);
        
        
        for (j=0; j <= g->num_nodes; j++){
            if (g->connections[node_getId(g->nodes[i])][node_getId(g->nodes[j])] == TRUE){
                cont1 = fprintf(pf, " %ld" ,node_getId(g->nodes[j]));
            }
        }
        cont = suma + cont;
        fprintf(pf, "\n");
    }
    
    return  cont;
}


Status graph_readFromFile(FILE *fin, Graph *g){
    int i, numNodes = 0;
    char name[NAME_L];
    long id, id1, id2;
    Label label;
    Node *n = NULL;

    if (!fin || !g) return ERROR;

    

    n = node_init();
    if (!n) return ERROR;

    fscanf(fin, "%d", &numNodes);

    for (i=0; i<numNodes; i++){
        fscanf(fin, "%ld %s %d", &id, name, (int *)&label);
        node_setId(n, id);
        node_setName(n, name);
        node_setLabel(n, label);

        graph_insertNode(g, n);
    }
    
    while (!feof(fin)){
        fscanf(fin, "%ld %ld", &id1, &id2);

        graph_insertEdge(g, id1, id2);
    }

    node_free(n);
    
    return OK;
}
