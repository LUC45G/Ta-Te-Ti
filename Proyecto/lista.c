#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"

/* Metodos para operar con la lista */

void crear_lista(tLista * l){
    // Crea una lista con el nodo centinela, elemento nulo y siguiente nulo (esta vacia)
    /*
    printf("Crear_Lista\n");
    tLista header = (tLista) malloc(sizeof(struct celda));
    if (header == NULL) exit(LST_ERROR_MEMORIA);
    printf("Lleg0");

    header->siguiente = NULL;
    printf("Lleg1");

    header->elemento = NULL;
    printf("Lleg2");
    *l = header;
    printf("Lleg3");
*/
    void crear_lista(tLista* l){
    ///Asigno memoria.
    *l=(tLista) malloc(sizeof(struct celda));
    ///Si la memoria no se asigno produce un error.
    if(*l==NULL)
        exit(LST_ERROR_MEMORIA);

    (*l) -> elemento=NULL; ///elemento nulo.
    (*l) -> siguiente=NULL; ///el puntero al sig elemento es nulo.

}

}

void l_insertar(tLista l, tPosicion p, tElemento e) {
    tPosicion aux = (tPosicion) malloc(sizeof(struct celda)); // Reservo memoria
    if(aux==NULL) {
        exit(LST_ERROR_MEMORIA); // Para evitar errores de punteros
    }
    aux->elemento = e;
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
    while (aux->siguiente != NULL ){ // Por cada elemento dentro de la lista
        fEliminar( (tElemento) aux->elemento); // Lo elimina con la funcion previa
        auxAnterior = aux;
        aux = l_siguiente(*l, aux); // Movimiento de punteros
        free(auxAnterior); // Liberación de memoria
    }
}

tElemento l_recuperar(tLista l, tPosicion p) {
    if ( p == NULL) exit(LST_POSICION_INVALIDA); // Si la posicion es nula, salir
    if ( p->elemento == NULL ) exit(LST_ELEMENTO_NULO); // Si es el centinela, salir
    return p->elemento; // Si no, devuelvo el elemento
}


tPosicion l_primera(tLista l) {
    if(l->siguiente == NULL) // Si la lista esta vacia
        return l; // Devuelvo el centinela

    return l->siguiente; // Sino, devuelvo el siguiente al centinela
}

tPosicion l_siguiente(tLista l, tPosicion p) {
    if ( p->siguiente == NULL ) exit(LST_NO_EXISTE_SIGUIENTE); // Si se le pide el siguiente al ultimo, salir

    return p->siguiente; // Sino devuelvo el siguiente
}

tPosicion l_anterior(tLista l, tPosicion p) {
    tPosicion aux = l; // Nodo de control

    if ( p == l->siguiente) exit(LST_NO_EXISTE_ANTERIOR); // Si se le pide el anterior al primer elemento, salir

    // Busco el anterior a p
    while( aux->siguiente != NULL && aux->siguiente != p ) {
        aux = aux->siguiente;
    }

    if (aux->siguiente != NULL) { // Si el siguiente no es nulo
        return aux; // Significa que encontro el elemento deseado, entonces devuelvo el anterior
    } else {
        exit(LST_NO_EXISTE_ANTERIOR); // Si no lo encontro, salir
    }

}

tPosicion l_ultima(tLista l) {
    tPosicion aux = l;
    tPosicion finAux = l_fin(l);

    // La posicion que apunta al ultimo elemento es aquella que apunta al que apunta al final.
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
    tPosicion prim = l; // Guardo el primero
    tPosicion fin = l_fin(l); // Guardo el ultimo
    int q = 0; // Contador

    while(prim != fin) {
        prim = prim->siguiente; // Mientras no termine la lista
        q++; // Sumo uno
    }
    if(l->siguiente != NULL) {
        q++;
    }

    return q;
}
