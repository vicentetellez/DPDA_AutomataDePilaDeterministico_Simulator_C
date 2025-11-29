#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "structs_and_functions/pila.c"
#include "structs_and_functions/lista_dinamica.c"

char* leerPalabraManual();
void ingresarLineas(NODO **lista);
bool validarAlfaNumerico(char text[]);
bool validarCaracteresProhibidos(char text[]);
bool validarRepeticionEnLista(NODO *lista);
bool validarExisteEnLista(NODO *lista, const char *palabra);
void liberarMemoriaValidacionLinea7(char *estado1, char *simbolo_alfabeto, char *simbolo_pila, char *estado2, char *palabra_pila, NODO *lista_linea1, NODO *lista_linea2, NODO *lista_linea3, NODO *lista_transiciones);
NODO* dividirEnLista(const char *linea);
bool validarLinea1(NODO *linea1);
bool validarLinea2(NODO *linea2);
bool validarLinea3(NODO *linea3);
bool validarLinea4(NODO *linea4, NODO *linea1);
bool validarLinea5(NODO *linea5, NODO *linea1);
bool validarLinea6(NODO *linea6, NODO *linea3);
bool validarLinea7(NODO *linea7, NODO *linea1, NODO *linea2, NODO *linea3);
char* validarLineasIngresadas1to7(NODO *lista);
// Lectura Automata
void imprimirLecturaAutomata(int posicion_linea8_actual, const char* linea8, const char* estado_actual, PILA *p);;
bool lecturaAutomata(NODO *lista_lineas);

int main(){
    system("cls");
    bool salir = false;
    do{
        NODO *lista = NULL;
        // Linea 1
        ingresarLineas(&lista);
        if (strcmp(lista -> palabra, "_FIN") != 0){
            // Linea 2
            ingresarLineas(&lista);
            // Linea 3
            ingresarLineas(&lista);
            // Linea 4
            ingresarLineas(&lista);
            // Linea 5
            ingresarLineas(&lista);
            // Linea 6
            ingresarLineas(&lista);
            // Linea 7
            ingresarLineas(&lista);
            // Linea 8
            ingresarLineas(&lista);
            printf("\n");
            // Validar las lineas
            char p[23];
            strcpy(p, validarLineasIngresadas1to7(lista));
            if (strcmp(p, "NADA") == 0){
                // Lineas validas, se mete la linea 8 a lectura por el automata
                lecturaAutomata(lista);
            }
            else {
                // Alguna o algunas lineas son invalidas
                printf("%s", p);
            }
            printf("\n");
        }
        else {
            salir = true;
        }

        liberarListaDinamica(lista);
        
    } while(!salir);

    return 0;
}


char* leerPalabraManual() {
    char *palabra = NULL;
    int c;
    size_t len = 0;

    while ((c = getchar()) != '\n' && c != EOF) {
        palabra = realloc(palabra, len + 2);
        if (palabra == NULL) {
            printf("Error de memoria.\n");
            exit(1);
        }
        palabra[len++] = (char)c;
    }
    if (palabra == NULL) return (NULL);

    palabra[len] = '\0';
    return (palabra);
}
void ingresarLineas(NODO **lista){
    char* p = leerPalabraManual();
    insertarNodo(lista, p);
    free(p);
}

bool validarAlfaNumerico(char text[]){
    int i, l = strlen(text);
    for (i=0; i<l; i++){
        if ((text[i] < 48 || text[i] > 57) && (text[i] < 65 || text[i] > 90) && (text[i] < 97 || text[i] > 122)){
            return (false);
        }
    }
    return (true);    
}
bool validarCaracteresProhibidos(char text[]){
    int i, l = strlen(text);
    for (i=0; i<l; i++){
        if (text[i] == 34 || text[i] == 35 || text[i] == 39 || text[i] == 44 || text[i] == 46){
            return (false);
        }
    }
    return (true);
}
bool validarRepeticionEnLista(NODO *lista){
    NODO *a = lista;
    while (a != NULL) {
        NODO *b = a->siguiente;
        while (b != NULL) {
            if (strcmp(a->palabra, b->palabra) == 0) {
                return false; // repetido
            }
            b = b->siguiente;
        }
        a = a->siguiente;
    }
    return (true);
}
bool validarExisteEnLista(NODO *lista, const char *palabra) {
    while (lista != NULL) {
        if (strcmp(lista -> palabra, palabra) == 0){
            return (true);
        }
        lista = lista -> siguiente;
    }
    return (false);
}

void liberarMemoriaValidacionLinea7(char *estado1, char *simbolo_alfabeto, char *simbolo_pila, char *estado2, char *palabra_pila, NODO *lista_linea1, NODO *lista_linea2, NODO *lista_linea3, NODO *lista_transiciones) {
    // Libera punteros simples
    if (estado1 != NULL) free(estado1);
    if (simbolo_alfabeto != NULL) free(simbolo_alfabeto);
    if (simbolo_pila != NULL) free(simbolo_pila);
    if (estado2 != NULL) free(estado2);
    if (palabra_pila != NULL) free(palabra_pila);

    // Libera listas dinámicas (si existen)
    if (lista_linea1 != NULL) liberarListaDinamica(lista_linea1);
    if (lista_linea2 != NULL) liberarListaDinamica(lista_linea2);
    if (lista_linea3 != NULL) liberarListaDinamica(lista_linea3);
    if (lista_transiciones != NULL) liberarListaDinamica(lista_transiciones);
}
NODO* dividirEnLista(const char *linea) {
    int i, j, inicio = 0, fin = 0, n = 0;
    int l = strlen(linea);
    bool inicioN = true;
    NODO *lista = NULL;
    for (i=0; i<l; i++) {
        if (linea[i] != 32 && inicioN == true) {
            inicio = i;
            inicioN = false;
        }
        if ((linea[i+1] == 32 || linea[i+1] == '\0') && inicioN == false) {
            fin = i;
            int tam = fin - inicio + 2;
            char *p = (char*) malloc(tam);
            n = 0;
            for (j=inicio; j<=fin; j++) {
                p[n++] = linea[j];
            }
            p[n] = '\0';
            insertarNodo(&lista, p);
            free(p);
            inicioN = true;
        }
    }

    return (lista);
}

bool validarLinea1(NODO *linea1){
    // Primer caracter tiene que ser alfanumerico + no debe contener de los caracteres prohibidos + se permite espacios

    if (linea1 == NULL){
        return (false);
    }

    if (linea1 -> palabra[0] == 32 || linea1 -> palabra[strlen(linea1 -> palabra) - 1] == 32){
        return (false);
    }

    NODO *lista_linea1 = dividirEnLista(linea1 -> palabra);
    NODO *aux = NULL;

    // Que comience siendo alfanumerico
    aux = lista_linea1;
    while (aux != NULL){
        char a[2];
        a[0] = aux -> palabra[0];
        a[1] = '\0';
        if (!validarAlfaNumerico(a)){
            liberarListaDinamica(lista_linea1);
            return (false);
        }
        aux = aux -> siguiente;
    }

    // Que ninguno contenga los caracteres prohibidos
    aux = lista_linea1;
    while (aux != NULL){
        if (!validarCaracteresProhibidos(aux -> palabra)){
            liberarListaDinamica(lista_linea1);
            return (false);
        }
        aux = aux -> siguiente;
    }

    // Que no hayan repeticiones de estados
    aux = lista_linea1;
    if (!validarRepeticionEnLista(aux)){
        liberarListaDinamica(lista_linea1);
        return (false);
    }

    liberarListaDinamica(lista_linea1);
    return (true);   
}
bool validarLinea2(NODO *linea2){
    // Debe ser simbolos separados por espacio + no debe contener de los caracteres prohibidos + se permite espacios

    if (linea2 == NULL){
        return (false);
    }

    if (linea2 -> palabra[0] == 32 || linea2 -> palabra[strlen(linea2 -> palabra) - 1] == 32){
        return (false);
    }

    NODO *lista_linea2 = dividirEnLista(linea2 -> palabra);
    NODO *aux = NULL;

    // Que sean simbolos (1) separados por espacios
    aux = lista_linea2;
    while (aux != NULL){
        if (strlen(aux -> palabra) != 1){
            liberarListaDinamica(lista_linea2);
            return (false);
        }
        aux = aux -> siguiente;
    }

    // Que ninguno contenga los caracteres prohibidos
    aux = lista_linea2;
    while (aux != NULL){
        if (!validarAlfaNumerico(aux -> palabra)){
            liberarListaDinamica(lista_linea2);
            return (false);
        }
        aux = aux -> siguiente;
    }

    // Que no haya repeticiones de simbolos
    aux = lista_linea2;
    if (!validarRepeticionEnLista(aux)){
        liberarListaDinamica(lista_linea2);
        return (false);
    }

    liberarListaDinamica(lista_linea2);
    return (true); 
}
bool validarLinea3(NODO *linea3){
    // Debe ser 1 solo simbolo separado por espacio + no debe contener caracteres prohibidos + sin repeticiones

    if (linea3 == NULL){
        return (false);
    }

    if (linea3 -> palabra[0] == 32 || linea3 -> palabra[strlen(linea3 -> palabra) - 1] == 32){
        return (false);
    }

    NODO *lista_linea3 = dividirEnLista(linea3 -> palabra);
    NODO *aux = NULL;

    // Que sean simbolos (1) separados por espacios
    aux = lista_linea3;
    while (aux != NULL){
        if (strlen(aux -> palabra) != 1){
            liberarListaDinamica(lista_linea3);
            return (false);
        }
        aux = aux -> siguiente;
    }

    // Que ninguno contenga los caracteres prohibidos
    aux = lista_linea3;
    while (aux != NULL){
        if (!validarCaracteresProhibidos(aux -> palabra)){
            liberarListaDinamica(lista_linea3);
            return (false);
        }
        aux = aux -> siguiente;
    }

    // Que no haya repeticiones de simbolos
    aux = lista_linea3;
    if (!validarRepeticionEnLista(aux)){
        liberarListaDinamica(lista_linea3);
        return (false);
    }

    liberarListaDinamica(lista_linea3);
    return (true);     
}
bool validarLinea4(NODO *linea4, NODO *linea1){
    // Debe ser una sola palabra + debe estar en la linea 1 + no espacios

    if (linea4 == NULL || linea1 == NULL){
        return (false);
    }

    int i, l = strlen(linea4 -> palabra);

    // Que no tenga espacios
    for (i=0; i<l; i++){
        if (linea4 -> palabra[i] == 32){
            return (false);
        }
    }

    NODO *lista_linea1 = dividirEnLista(linea1 -> palabra);
    NODO *inicio = lista_linea1;

    // Que el estado de la Linea 4 se encuentre en la Linea 1
    while (lista_linea1 != NULL){
        if (strcmp(lista_linea1 -> palabra, linea4 -> palabra) == 0){
            liberarListaDinamica(inicio);
            return (true);
        }
        lista_linea1 = lista_linea1 -> siguiente;
    }
    liberarListaDinamica(inicio);
    return (false);
}
bool validarLinea5(NODO *linea5, NODO *linea1){
    // Pueden ser varias palabras separadas por espacio + tienen que encontrarse en la linea 1, eso nos quita la validacion de: no pueden haber simbolos prohibidos

    if (linea5 == NULL || linea1 == NULL){
        return (false);
    }

    if (linea5 -> palabra[0] == 32 || linea5 -> palabra[strlen(linea5 -> palabra) - 1] == 32){
        return (false);
    }

    NODO *lista_linea5 = dividirEnLista(linea5 -> palabra);
    NODO *aux5 = NULL;
    NODO *lista_linea1 = dividirEnLista(linea1 -> palabra);
    NODO *aux1 = NULL;

    // Que no hayan repeticiones de estados
    aux5 = lista_linea5;
    if (!validarRepeticionEnLista(aux5)){
        liberarListaDinamica(lista_linea5);
        liberarListaDinamica(lista_linea1);
        return (false);
    }

    // Que los estados de la Linea 5 se encuentre en la Linea 1
    int validar1 = 0, validar2 = 0;
    aux5 = lista_linea5;
    while (aux5 != NULL){
        aux1 = lista_linea1;
        while (aux1 != NULL){
            if (strcmp(aux5 -> palabra, aux1 -> palabra) == 0){
                validar1++;
                break;
            }
            aux1 = aux1 -> siguiente;
        }
        validar2++;
        aux5 = aux5 -> siguiente;
    }
    if (validar1 == validar2){
        liberarListaDinamica(lista_linea5);
        liberarListaDinamica(lista_linea1);
        return (true);
    }
    else {
        liberarListaDinamica(lista_linea5);
        liberarListaDinamica(lista_linea1);
        return (false);
    }
}
bool validarLinea6(NODO *linea6, NODO *linea3){
    // Debe ser una sola palabra + debe estar en la linea 3 + no espacios

    if (linea6 == NULL || linea3 == NULL){
        return (false);
    }

    int l = strlen(linea6 -> palabra);

    // Que sea 1 solo simbolo y que no tenga espacios
    if (l != 1 || linea6 -> palabra[0] == 32) {
        return false;
    }

    NODO *lista_linea3 = dividirEnLista(linea3 -> palabra);
    NODO *inicio = lista_linea3;

    // Que el simbolo de la Linea 6 se encuentre en la Linea 3
    while (lista_linea3 != NULL){
        if (strcmp(lista_linea3 -> palabra, linea6 -> palabra) == 0){
            liberarListaDinamica(inicio);
            return (true);
        }
        lista_linea3 = lista_linea3 -> siguiente;
    }
    liberarListaDinamica(inicio);
    return (false);
}
bool validarLinea7(NODO *linea7, NODO *linea1, NODO *linea2, NODO *linea3){
    // Que tenga el formato ([Estado],[Simbolo_Alfabeto],[Simbolo_Pila]=[Estado],[Palabra_Pila])
    // Que no tenga espacios + cada simbolo o palabra debe estar en la linea que le toca + se permite #

    if (linea7 == NULL || linea1 == NULL || linea2 == NULL || linea3 == NULL){
        return (false);
    }

    // Separamos la Linea 7
    NODO *lista_transiciones = dividirEnLista(linea7 -> palabra);
    NODO *aux_transiciones = NULL;

    // Validamos que no tengan espacios
    aux_transiciones = lista_transiciones;
    while (aux_transiciones != NULL){
        int i, l = strlen(aux_transiciones -> palabra);
        for (i=0; i<l; i++){
            if (aux_transiciones -> palabra[i] == 32){
                liberarListaDinamica(lista_transiciones);
                return (false);
            }
        } 
        aux_transiciones = aux_transiciones -> siguiente;
    }

    // Validamos que tengan formato [Abrir parentesis] ... [2 Comas] ... [Un =] ... [1 Coma] ... [Cerrar parentesis]
    aux_transiciones = lista_transiciones;
    while (aux_transiciones != NULL){
        int i, l = strlen(aux_transiciones -> palabra);
        int count_parA = 0, count_parB = 0, count_igual = 0, count_comas = 0;
        if (aux_transiciones -> palabra[0] != '(' || aux_transiciones -> palabra[l-1] != ')') {
            liberarListaDinamica(lista_transiciones);
            return (false);
        }
        for (i=0; i<l; i++) {
            if (aux_transiciones -> palabra[i] == '('){
                count_parA++;
            }
            else {
                if (aux_transiciones -> palabra[i] == ')'){
                    count_parB++;
                }
                else {
                    if (aux_transiciones -> palabra[i] == '='){
                        count_igual++;
                    }
                    else {
                        if (aux_transiciones -> palabra[i] == ','){
                            count_comas++;
                        }
                    }
                }
            }
        }
        if (count_parA != 1 || count_parB != 1 || count_igual != 1 || count_comas != 3) {
            liberarListaDinamica(lista_transiciones);
            return (false);
        }
        aux_transiciones = aux_transiciones -> siguiente;
    }

    // Validar que sea deterministica (Estado,Simbolo_Alfa,Simbolo_Pila) no se debe repetir
    NODO *lista_tripletes = NULL;   
    aux_transiciones = lista_transiciones;
    while (aux_transiciones != NULL){
        int i = 0, n = 0, l = strlen(aux_transiciones -> palabra);
        bool inicio = false;
        char *p = (char*) malloc(l+1);
        for (i=0; i<l; i++) {
            if (aux_transiciones -> palabra[i] == 40) { 
                inicio = true; 
                continue;
            }
            if (aux_transiciones -> palabra[i] == 61) { 
                break;
            }
            if (inicio) {
                p[n++] = aux_transiciones -> palabra[i];
            }
        }
        p[n] = '\0';
        insertarNodo(&lista_tripletes, p);
        free(p);
        aux_transiciones = aux_transiciones -> siguiente;
    }
    if (!validarRepeticionEnLista(lista_tripletes)) {
        liberarListaDinamica(lista_tripletes);
        return (false);
    }
    liberarListaDinamica(lista_tripletes);

    // Validamos que cada Estado, Simbolo del Alfabeto, Simbolo de la Pila, etc... este en las lineas correspondientes

    aux_transiciones = lista_transiciones;
    NODO *lista_linea1 = dividirEnLista(linea1 -> palabra);
    NODO *lista_linea2 = dividirEnLista(linea2 -> palabra);
    NODO *lista_linea3 = dividirEnLista(linea3 -> palabra);

    while (aux_transiciones != NULL) {
        char *estado1 = malloc(strlen(aux_transiciones -> palabra) + 1);
        char *simbolo_alfabeto = malloc(strlen(aux_transiciones -> palabra) + 1);
        char *simbolo_pila = malloc(strlen(aux_transiciones -> palabra) + 1);
        char *estado2 = malloc(strlen(aux_transiciones -> palabra) + 1);
        char *palabra_pila = malloc(strlen(aux_transiciones -> palabra) + 1);

        int ok = sscanf(aux_transiciones -> palabra, "(%[^,],%[^,],%[^=]=%[^,],%[^)])", estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila);
        
        // Se espera el formato (E,A,B=E,CD)
        if (ok != 5) {
            liberarMemoriaValidacionLinea7(estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila, lista_linea1, lista_linea2, lista_linea3, lista_transiciones);
            return (false);
        }

        // --- Validar estados ---
        if (!validarExisteEnLista(lista_linea1, estado1) || !validarExisteEnLista(lista_linea1, estado2)) {
            liberarMemoriaValidacionLinea7(estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila, lista_linea1, lista_linea2, lista_linea3, lista_transiciones);
            return (false);
        }

        // --- Validar simbolo del alfabeto ---
        if (!validarExisteEnLista(lista_linea2, simbolo_alfabeto)) {
            liberarMemoriaValidacionLinea7(estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila, lista_linea1, lista_linea2, lista_linea3, lista_transiciones);
            return (false);
        }

        // --- Validar simbolo de pila leida ---
        if (strcmp(simbolo_pila, "#") != 0 && !validarExisteEnLista(lista_linea3, simbolo_pila)) {
            liberarMemoriaValidacionLinea7(estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila, lista_linea1, lista_linea2, lista_linea3, lista_transiciones);
            return (false);
        }

        // --- Validar palabra de pila escrita ---
        int l = strlen(palabra_pila);
        if (l > 2) { // maximo 2 simbolos
            liberarMemoriaValidacionLinea7(estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila, lista_linea1, lista_linea2, lista_linea3, lista_transiciones);
            return (false);
        }
        int i;
        for (i=0; i<l; i++) {
            char s[2] = { palabra_pila[i], '\0' };
            if (strcmp(s, "#") != 0 && !validarExisteEnLista(lista_linea3, s)) {
                liberarMemoriaValidacionLinea7(estado1, simbolo_alfabeto, simbolo_pila, estado2, palabra_pila, lista_linea1, lista_linea2, lista_linea3, lista_transiciones);
                return (false);
            }
        }

        free(estado1);
        free(simbolo_alfabeto);
        free(simbolo_pila);
        free(estado2);
        free(palabra_pila);

        aux_transiciones = aux_transiciones->siguiente;
    }
    liberarListaDinamica(lista_linea1);
    liberarListaDinamica(lista_linea2);
    liberarListaDinamica(lista_linea3);
    liberarListaDinamica(lista_transiciones);

    return (true);
}

char* validarLineasIngresadas1to7(NODO *lista){
    int i = 1;
    NODO *aux = lista;
    NODO *linea1 = NULL;
    NODO *linea2 = NULL;
    NODO *linea3 = NULL;
    NODO *linea4 = NULL;
    NODO *linea5 = NULL;
    NODO *linea6 = NULL;
    NODO *linea7 = NULL;
    while(aux != NULL){
        switch(i){
            case 1: linea1 = aux;
                break;
            case 2: linea2 = aux;
                break;
            case 3: linea3 = aux;
                break;
            case 4: linea4 = aux;
                break;
            case 5: linea5 = aux;
                break;
            case 6: linea6 = aux;
                break;
            case 7: linea7 = aux;
                break;
        }
        aux = aux->siguiente;
        i++;
    }
   // Estados
    if (!validarLinea1(linea1)){
        return ("Error encontrado en 1");
    }
    // Alfabeto de la cinta
    if (!validarLinea2(linea2)){
        return ("Error encontrado en 2");
    }
    // Alfabeto de la pila
    if (!validarLinea3(linea3)){
        return ("Error encontrado en 3");
    }
    // Estado de inicio (1)
    if (!validarLinea4(linea4, linea1)){
        return ("Error encontrado en 4");
    }
    // Estados de fin
    if (!validarLinea5(linea5, linea1)){
        return ("Error encontrado en 5");
    }
    // Fondo de la pila (1)
    if (!validarLinea6(linea6, linea3)){
        return ("Error encontrado en 6");
    }
    // Transicion
    if (!validarLinea7(linea7, linea1, linea2, linea3)){
        return ("Error encontrado en 7");
    }
    return ("NADA");
}

void imprimirLecturaAutomata(int posicion_linea8_actual, const char* linea8, const char* estado_actual, PILA *p){
    int i, l = strlen(linea8);
    // Ejemplo: "0.00111"
    for (i=0; i<l; i++){
        // Se pone un . atras del simbolo donde se este trabajando (...  .0  ...)
        if (i == posicion_linea8_actual){
            printf(".");
        }
        printf("%c", linea8[i]);
    }
    if (posicion_linea8_actual == l) {
        printf(".");
    }
    // Ejemplo: " q1 "
    printf(" %s ", estado_actual);
    // Ejemplo: "AL"
    imprimirPila(p);
    // RESULTADO: "0.00111 q1 AL"
    printf("\n");
}
bool lecturaAutomata(NODO *lista_lineas){
    NODO *aux = lista_lineas;
    NODO *linea4 = NULL; // Estado Inicial
    NODO *linea5 = NULL; // Estados Finales
    NODO *linea6 = NULL; // Fondo de Pila
    NODO *linea7 = NULL; // Transiciones
    NODO *linea8 = NULL; // Palabra de Entrada
    int i_linea = 1;
    while(aux != NULL){
        if (i_linea == 4) linea4 = aux;
        else if (i_linea == 5) linea5 = aux;
        else if (i_linea == 6) linea6 = aux;
        else if (i_linea == 7) linea7 = aux;
        else if (i_linea == 8) linea8 = aux;
        aux = aux -> siguiente;
        i_linea++;
    }

    // Estado Actual
    char estado_actual_buffer[11];
    strcpy(estado_actual_buffer, linea4 -> palabra);

    // Pila 
    PILA *p = (PILA *)malloc(sizeof(PILA));
    if (p == NULL) return false;
    inicioPila(p);
    pushPila(p, linea6 -> palabra[0]);

    // Cinta y Transiciones
    int indice_cinta = 0;
    const char *palabra_entrada = linea8 -> palabra;
    int len_palabra = strlen(palabra_entrada);
    NODO *lista_transiciones = dividirEnLista(linea7 -> palabra);

    // Buffers para sscanf
    char e1[11], e2[11];
    char s_alfa[2], s_pila[2]; 
    char p_pila[3]; 

    // Imprimimos el estado inicial (antes de cualquier movimiento)
    imprimirLecturaAutomata(indice_cinta, palabra_entrada, estado_actual_buffer, p);

    while (true) {
        
        // A) Obtener informacion del estado actual (SIN MODIFICAR LA PILA)
        
        // 1. Tope de Pila (SIMULACION DE PEEK)
        char tope_pila_char;
        if (isEmptyPila(p)) {
            // La pila esta vacia y no hay transiciones de este tipo, el computo finaliza.
            break;
        }
        tope_pila_char = p->x[p->cima]; // Acceso directo al tope

        // 2. Simbolo de Entrada a buscar
        char simbolo_cinta_char = '\0';
        if (indice_cinta < len_palabra) {
            simbolo_cinta_char = palabra_entrada[indice_cinta];
        } 
        // Si el indice esta al final, 'simbolo_cinta_char' sigue siendo '\0', lo que solo
        // permitira buscar transiciones epsilon.

        // B) Busqueda de la unica Transicion Aplicable
        NODO *aux_transiciones = lista_transiciones;
        NODO *transicion_simbolo = NULL;
        NODO *transicion_epsilon = NULL;

        while (aux_transiciones != NULL) {
            sscanf(aux_transiciones->palabra, "(%[^,],%[^,],%[^=]=%[^,],%[^)])", e1, s_alfa, s_pila, e2, p_pila);
            
            bool coincide_estado_pila = (strcmp(e1, estado_actual_buffer) == 0 && s_pila[0] == tope_pila_char);

            if (coincide_estado_pila) {
                
                bool es_simbolo = (s_alfa[0] != '#');
                bool es_epsilon = (s_alfa[0] == '#');

                // Chequeo 1: Transicion de Simbolo (solo si no se ha consumido toda la palabra)
                if (es_simbolo && indice_cinta < len_palabra && s_alfa[0] == simbolo_cinta_char) {
                    transicion_simbolo = aux_transiciones;
                }

                // Chequeo 2: Transicion Epsilon
                if (es_epsilon) {
                    transicion_epsilon = aux_transiciones;
                }
            }
            aux_transiciones = aux_transiciones->siguiente;
        }

        // Seleccion de la transicion
        NODO *transicion_definitiva = NULL;

        if (transicion_simbolo != NULL) {
            // Si encontramos una transicion de simbolo, la usamos (Prioridad 1)
            transicion_definitiva = transicion_simbolo;
        } else if (transicion_epsilon != NULL) {
            // Si solo encontramos una transicion epsilon, la usamos (Prioridad 2)
            transicion_definitiva = transicion_epsilon;
        }
        
        // Si no se encuentra ninguna transicion valida
        if (transicion_definitiva == NULL) {
            break; 
        }
        
        // C) Ejecucion de la Transicion Encontrada
        
        // Re-escanear para tener los valores definitivos
        sscanf(transicion_definitiva->palabra, "(%[^,],%[^,],%[^=]=%[^,],%[^)])", e1, s_alfa, s_pila, e2, p_pila);

        if (s_pila[0] != '#') {
            popPila(p); 
        }      
        if (p_pila[0] != '#') {
            int len_pila = strlen(p_pila);
            for (int i_push = len_pila - 1; i_push >= 0; i_push--) { 
                pushPila(p, p_pila[i_push]);
            }
        }
        
        // 3. ESTADO: Actualizacion
        strcpy(estado_actual_buffer, e2); 
        
        // 4. CINTA: Avance
        if (s_alfa[0] != '#') {
            indice_cinta++;
        }
        
        // 5. Impresion del estado actual
        imprimirLecturaAutomata(indice_cinta, palabra_entrada, estado_actual_buffer, p);

    } // Fin del bucle while(true)

    // --- 3. Verificacion de Aceptacion ---
    
    // Aceptacion: Final de Palabra Y Estado Final Y Solo Fondo de Pila
    bool fin_palabra = (indice_cinta == len_palabra);
    
    // Solo el simbolo de fondo de pila: p->cima debe ser 0 (el fondo es el unico elemento)
    bool fondo_pila_correcto = (!isEmptyPila(p) && p->cima == 0 && p->x[0] == linea6->palabra[0]); 
    
    // Chequear Estado Final
    NODO *lista_estados_finales = dividirEnLista(linea5->palabra);
    bool estado_final = validarExisteEnLista(lista_estados_finales, estado_actual_buffer);

    // Decision Final
    bool aceptado = fin_palabra && fondo_pila_correcto && estado_final;

    if (aceptado) {
        printf("Aceptado\n");
    } else {
        printf("Rechazado\n");
    }

    free(p);
    liberarListaDinamica(lista_transiciones);
    liberarListaDinamica(lista_estados_finales);

    return (aceptado);
}