# ⚙️ DPDA_AutomataDePilaDeterministico_Simulator_C

## 📝 Descripción del Proyecto

Este proyecto es un **simulador de un Automata de Pila Determinista (DPDA)** (Pushdown Automaton - PDA) implementado en el lenguaje C. Su función principal es leer la definición completa de un autómata (estados, alfabeto, transiciones, etc.) y simular su funcionamiento en tiempo real sobre una palabra de entrada, determinando si la palabra es **aceptada** o **rechazada** según las reglas del autómata definido.

A pesar de que el nombre del repositorio sugiere un Automata Finito Determinista (DFA), la complejidad de la implementación (manejo de la **Pila** y transiciones con consumo de símbolos de pila) lo clasifica como un DPDA, una estructura más avanzada utilizada en la Teoría de la Computación.

## ✨ Características Principales

* **Ingreso Interactivo:** Permite al usuario ingresar la definición completa del autómata línea por línea (estados, alfabeto de cinta, alfabeto de pila, estado inicial, estados finales, fondo de pila y transiciones).
* **Validación de Formato:** Realiza una validación exhaustiva de las **primeras 7 líneas** de entrada, verificando la unicidad, formato y pertenencia de todos los símbolos y estados.
* **Determinismo:** Asegura la condición de **determinismo** en las transiciones (q, a, b), garantizando que no haya repeticiones de la terna (Estado, Símbolo de Entrada, Tope de Pila) que puedan generar ambigüedad.
* **Simulación Paso a Paso:** Imprime el estado actual del cómputo en cada transición:
    * Cinta de entrada (marcando el símbolo actual).
    * Estado actual.
    * Contenido actual de la Pila.
* **Estructuras de Datos Dinámicas:** Utiliza estructuras de datos dinámicas (`lista_dinamica.c` y `pila.c`) para el manejo eficiente de la definición del autómata y la pila de ejecución.

## 🛠 Tecnologías Utilizadas

| Componente | Descripción |
| :--- | :--- |
| **Lenguaje** | C (Implementación nativa y de bajo nivel para eficiencia). |
| **Estructuras** | Pila (`structs_and_functions/pila.c`) y Listas Dinámicas (`structs_and_functions/lista_dinamica.c`). |

## 🚀 Uso del Programa

El programa espera la entrada de la definición del Automata de Pila, la cual debe seguir un formato estricto de 8 líneas, con la última línea siendo la palabra a evaluar:

### Formato de Entrada (Ejemplo)

1.  **Estados:** `q0 q1 qf` (Separados por espacio)
2.  **Alfabeto de Cinta:** `0 1` (Símbolos separados por espacio)
3.  **Alfabeto de Pila:** `A B Z` (Símbolos separados por espacio)
4.  **Estado Inicial:** `q0` (Un solo estado)
5.  **Estados Finales:** `qf` (Uno o más estados separados por espacio)
6.  **Fondo de Pila:** `Z` (Un solo símbolo perteneciente al alfabeto de la pila)
7.  **Funciones de Transición:** `(q0,0,Z=q0,AZ) (q0,1,A=q1,#) (q1,#,Z=qf,#)` (Transiciones separadas por espacio)
    * *Formato de Transición:* `(Estado_Origen, Simbolo_Cinta, Tope_Pila = Estado_Destino, Palabra_a_Push)`
    * `#` representa la cadena vacía ($\epsilon$ o $\lambda$).
8.  **Palabra de Entrada:** `0011`

## ⚙️ Compilación y Ejecución

Para compilar y ejecutar este simulador, sigue los siguientes pasos:

1.  Asegúrate de tener un compilador de C (como GCC) instalado en tu sistema.
2.  Compila el archivo principal (`main.c`) junto con las dependencias:
    ```bash
    gcc main.c structs_and_functions/pila.c structs_and_functions/lista_dinamica.c -o DPDA_Simulator
    ```
3.  Ejecuta el programa:
    ```bash
    ./DPDA_Simulator
    ```
4.  El programa solicitará la entrada de las 8 líneas de la definición del autómata.
