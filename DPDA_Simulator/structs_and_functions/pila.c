#include <stdio.h>
#include <stdbool.h>

#include "pila.h"

void inicioPila(PILA *p){
    p -> cima = -1;
}

bool isEmptyPila(PILA *p){
    return (p -> cima == -1);
}

void imprimirPila(PILA *p){
    int i;
    for (i=p -> cima; i>=0; i--){
        printf("%c", p -> x[i]);
    }
}

bool pushPila(PILA *p, X n){
    if (p -> cima < MAX){
        p -> x[++p -> cima] = n;
        return (true);
    }
    else {
        return (false);
    }
}

X popPila(PILA *p) {
    if (!isEmptyPila(p)) { // Solo si NO está vacía
        return p -> x[p->cima--];
    } 
    else {
        printf("Error: la pila está vacía, no se puede hacer pop.\n");
        return '\0'; // o bien devuelve un valor sentinela
    }
}
