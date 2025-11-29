#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_dinamica.h"

NODO* crearNodo(const char *text){
    NODO *nuevo = (NODO*)malloc(sizeof(NODO));
    if (nuevo == NULL){
        exit(1);
    }
    nuevo -> palabra = malloc(strlen(text) + 1);
    if (nuevo -> palabra == NULL){
        exit(1);
    }
    strcpy(nuevo -> palabra, text);
    nuevo -> siguiente = NULL;
    return (nuevo);
}

void insertarNodo(NODO **cabeza, const char *text){
    NODO *nuevo = crearNodo(text);
    if (*cabeza == NULL){
        *cabeza = nuevo;
    }
    else {
        NODO *aux = *cabeza;
        while(aux -> siguiente != NULL){
            aux = aux -> siguiente;
        }
        aux  -> siguiente = nuevo;
    }
}

void liberarListaDinamica(NODO *cabeza){
    NODO *aux;
    while(cabeza != NULL){
        aux = cabeza;
        cabeza = cabeza -> siguiente;
        free(aux -> palabra);
        free(aux);
    }
}