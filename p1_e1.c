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
    Node *n2;
    Node *n1;

    n1 = node_init();
    if (!n1) return -1;
    n2 = node_init();
    if (!n2){
        node_free(n1);
        return -1;
    }

    node_setName(n1, "first");
    node_setName(n2, "second");

    node_setId(n1, 111);
    node_setId(n2, 222);

    node_setLabel(n1, WHITE);
    node_setLabel(n2, WHITE);

    node_print(stdout, n1);
    node_print(stdout, n2);

    printf("\n");

    if (node_cmp(n1, n2) == 0){
        printf("Son iguales?: Si\n");
    }else {
        printf("Son iguales?: No\n");
    }

    printf("Id del primer nodo: %ld\n", node_getId(n1));

    printf("Nombre del segundo nodo es: %s\n", node_getName(n2));

    node_free(n2);

    n2 = node_copy(n1);

    node_print(stdout, n1);
    node_print(stdout, n2);

    printf("\n");

    if (node_cmp(n1, n2) == 0){
        printf("Son iguales?: Si\n");
    }else {
        printf("Son iguales?: No\n");
    }

    node_free(n1);
    node_free(n2);

    return 0;
}
