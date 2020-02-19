/**
* @file p1_e1.c
* @author Gonzalo Arcas & Ciro Alonso
* @date 19 February 2020
* @brief primer ejercicio practica 1
*
* @details Comprobacion de las funciones del TAD Node
*
* @see
*/
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Node *nodazo;
    Node *nodito;

    nodito = node_init();
    if (!nodito) return -1;
    nodazo = node_init();
    if (!nodazo){
        node_free(nodito);
        return -1;
    }

    node_setName(nodito, "first");
    node_setName(nodazo, "second");

    node_setId(nodito, 111);
    node_setId(nodazo, 222);

    node_setLabel(nodito, WHITE);
    node_setLabel(nodazo, WHITE);

    node_print(stdout, nodito);
    node_print(stdout, nodazo);

    printf("\n");

    if (node_cmp(nodito, nodazo) == 0){
        printf("Son iguales?: Si\n");
    }else {
        printf("Son iguales?: No\n");
    }

    printf("Id del primer nodo: %ld\n", node_getId(nodito));

    printf("Nombre del segundo nodo es: %s\n", node_getName(nodazo));

    node_free(nodazo);

    nodazo = node_copy(nodito);

    node_print(stdout, nodito);
    node_print(stdout, nodazo);

    printf("\n");

    if (node_cmp(nodito, nodazo) == 0){
        printf("Son iguales?: Si\n");
    }else {
        printf("Son iguales?: No\n");
    }

    node_free(nodito);
    node_free(nodazo);

    return 0;
}
