#ifndef LISTA_H
#define LISTA_H

typedef struct NODO {
    char *palabra;
    struct NODO *siguiente;
} NODO;

NODO* crearNodo(const char *text);
void insertarNodo(NODO **cabeza, const char *text);
void liberarListaDinamica(NODO *cabeza);

#endif