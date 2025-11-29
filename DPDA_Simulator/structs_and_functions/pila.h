#ifndef PILA_H
#define PILA_H

#include <stdbool.h>

#define MAX 4

typedef char X;

typedef struct {
    X x[MAX];
    int cima;
} PILA;


void inicioPila(PILA *p);
bool isEmptyPila(PILA *p);
bool pushPila(PILA *p, X n);
X popPila(PILA *p);

#endif
