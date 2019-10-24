#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


/* Metodos para operar con la lista */

void crear_lista(tLista * l){
    // Crea una lista con el nodo centinela, elemento nulo y siguiente nulo (esta vacia)

    tLista header = (tLista ) malloc(sizeof(struct celda));

    header->siguiente = NULL;
    header->elemento = NULL;
    *l = header;

}

void l_insertar(tLista l, tPosicion p, tElemento e) {
    tPosicion aux = (tPosicion) malloc(sizeof(struct celda));
    aux->elemento = (void*) e;
    aux->siguiente = p->siguiente; // Crea el nodo y lo inicializa
    p->siguiente = aux; // Cambia el puntero del nodo previo

}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) {

    if ( p == l_fin(l) ) exit(LST_POSICION_INVALIDA);

    tPosicion aux = p->siguiente; // Nodo auxiliar, almacena el nodo a eliminar
    p->siguiente = aux->siguiente; // Mueve el puntero al lugar deseado
    fEliminar(aux->elemento); // Libera memoria del valor
    free(aux); // Libera memoria del nodo
}

void l_destruir(tLista * l, void (*fEliminar)(tElemento)) {
    tPosicion aux = *l, auxAnterior;
    int i = 1;
    while (aux->siguiente != NULL ){
        fEliminar( (tElemento) aux->elemento);
        auxAnterior = aux;
        aux = l_siguiente(*l, aux);
        free(auxAnterior);
        printf("Eliminado elemento nro: %i con exito.\n", i++);//poner afuera
    }


}

tElemento l_recuperar(tLista l, tPosicion p) {
    if ( p == NULL) exit(LST_POSICION_INVALIDA);
    if ( p->elemento == NULL ) exit(LST_ELEMENTO_NULO);
    return p->elemento;
}


tPosicion l_primera(tLista l) {
    if(l->siguiente == NULL)
        return l;

    return l->siguiente;
}

tPosicion l_siguiente(tLista l, tPosicion p) {
    if ( p->siguiente == NULL ) exit(LST_NO_EXISTE_SIGUIENTE);

    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p) {
    tPosicion aux = l;

    if ( p == l->siguiente) exit(LST_NO_EXISTE_ANTERIOR); // Avisar del error

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

int l_longitud(tLista l) {
    tPosicion prim = l->siguiente, fin = l_fin(l);
    int q = 0;

    while(q != NULL && prim != fin) {
        prim = prim->siguiente;
        q++;
    }

    return q;
}
