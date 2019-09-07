#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


/* Metodos para operar con la lista */

void crear_lista(tLista * l){
    // Crea una lista con el nodo centinela, elemento nulo y siguiente nulo (esta vacia)
    l = (tLista*) malloc(sizeof(tLista));
    (*l)->siguiente = NULL;
    (*l)->elemento = NULL;
}

void l_insertar(tLista l, tPosicion p, tElemento e) {
    tPosicion aux = (tPosicion) malloc(sizeof(tPosicion));
    aux->elemento = e;
    aux->siguiente = p->siguiente; // Crea el nodo y lo inicializa
    p->siguiente = aux; // Cambia el puntero del nodo previo
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) {
    tPosicion aux = p->siguiente; // Nodo auxiliar, almacena el nodo a eliminar
    p->siguiente = aux->siguiente; // Mueve el puntero al lugar deseado
    free(aux->elemento); // Libera memoria del valor
    free(aux); // Libera memoria del nodo
}

void l_destruir(tLista * l, void (*fEliminar)(tElemento)) {

}

tElemento l_recuperar(tLista l, tPosicion p) {
    return p->elemento;
}

tPosicion l_primera(tLista l) {
    return l->siguiente;
}

tPosicion l_siguiente(tLista l, tPosicion p) {
    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p) {
    tPosicion aux = l;

    if ( p == l->siguiente) {
        // Avisar del error, no se como
        printf("ERROR NRO %d", LST_NO_EXISTE_ANTERIOR);
        return NULL;
    }
    // Busco el anterior a p
    while( aux->siguiente != NULL && aux->siguiente != p ) {
        aux = aux->siguiente;
    }

    if (aux->siguiente != NULL) {
        return aux;
    } else {
        return NULL;
    }

}

tPosicion l_ultima(tLista l) {
    tPosicion aux = l;
    tPosicion finAux = l_fin(l);

    // La posicion que apunta al ultimo elemento es aquella que apunta al que apunta al final.
    // C > 1 > 2 > 3 > 5 > U ==> [3] es ultima
    while( aux->siguiente != finAux ) {
        aux = aux->siguiente;
    }

    return aux;
}

tPosicion l_fin(tLista l) {
    tPosicion aux = l;

    // Busco el ultimo, es decir, el elemento cuyo siguiente sea nulo
    while( aux->siguiente != NULL ) {
        aux = aux->siguiente;
    }

    return aux;

}
