#include <stdio.h>
#include <stdlib.h>

/* Estructura del nodo */
typedef struct Nodo {
    int value;
    struct Nodo *sig;
} Nodo;

/* Metodos para operar con la lista */

void EliminarElemento(Nodo n, Nodo l) {
    Nodo aux = * (n.sig); // Nodo auxiliar, almacena el nodo a eliminar
    n.sig = aux.sig; // Mueve el puntero al lugar deseado
    //free(aux->value); // Libera memoria del valor
    //free(&aux); // Libera memoria del nodo
}

void AgregarElemento(int v, Nodo n, Nodo l) {

    Nodo* aux = (Nodo*) malloc(sizeof(struct Nodo));
    aux->value = v;
    aux->sig = n.sig; // Crea el nodo y lo inicializa

    n.sig = aux; // Cambia el puntero del nodo previo
}

int main() {
    Nodo* list, *aux, *saux; int i;
    list = (Nodo*) malloc(sizeof(struct Nodo));

    list->value = 1;

    saux = list;

    for(i = 2; i<7; i++) {
        aux = (Nodo*) malloc(sizeof(struct Nodo));
        aux->value = i;
        saux->sig = aux;
        saux = aux;
    }

    i= 0;

    while(i < 6) {
        printf("El: %i\n", list->value);
        list = list->sig;
        i++;
    }

    return 0;
}
