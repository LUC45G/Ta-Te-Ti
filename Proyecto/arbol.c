#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void crear_arbol(tArbol *a){
    tArbol arbol = (tArbol) malloc(sizeof(tArbol)); //o tNodo?
    //todos los atributos en nulo
    arbol->raiz->elemento = NULL; //ver los -> y .
    arbol->raiz->hijos = NULL;

    *a = arbol;
}

void crear_raiz(tArbol a, tElemento e) {

    if ( a->raiz != NULL ) exit(ARB_OPERACION_INVALIDA);

    // Creo un nodo iliar que sera la raiz
    tNodo nodoAux = malloc(sizeof(tNodo));

    // Creo e inicializo como vacia la lista de hijos
    tLista listaHijos;
    crear_lista(&listaHijos);

    // Inicializo el nuevo nodo que sera raiz
    nodoAux->elemento = e;
    nodoAux->hijos = listaHijos;
    nodoAux->padre = NULL;

    // Asigno la nueva raiz
    a->raiz = nodoAux;

}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){

    if (nh->padre != np) exit(ARB_POSICION_INVALIDA);

    //creo el nodo a insertar
    tNodo nuevo = malloc(sizeof(tNodo));
    //creo una lista de hijos vacía para el nuevo nodo
    tLista listaHijos;
    crear_lista(&listaHijos);
    //Set de atributos del nuevo nodo
    nuevo->elemento = e;
    nuevo->padre = np;
    nuevo->hijos = listaHijos;

    if (nh != NULL){
        // Recorrer lista de hijos de np en busca de nh
        // Sino tirar arb posicion invalidisima
        l_insertar(np->hijos,nh,(tElemento) nuevo);
    }else{  //nuevo es el primer hijo de np
        l_insertar(np->hijos,l_primera(np->hijos),(tElemento) nuevo);
    }

    return nuevo;
}

void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento)) {

    tPosicion hijo, ultimoHermano, fin;
    tNodo padre;
    tLista hermanos;

    hijo = l_primera(pa->hijos); // Hijo es puntero al primer hijo de la lista
    fin = l_fin(pa->hijos); // Fin es el ultimo elemento de la lista de hijos

    if( a->raiz == pa ) { // Si pa es la raiz

        if(hijo == fin) { // Si el primer elemento es el ultimo, la lista esta vacia
            l_destruir(&(pa->hijos), fEliminar);
            fEliminar(pa->elemento);
            free(pa);
        } else {

            if(l_siguiente(pa->hijos, hijo) == NULL) { // Si no, si el siguiente al siguiente es nulo, la lista tiene un solo elemento
                a->raiz = hijo->elemento;
            } else {
                exit(ARB_OPERACION_INVALIDA);
            }

        }

    } else { // Si pa no es la raiz

        padre = pa->padre; // Padre del nodo a eliminar
        hermanos = padre->hijos; // Lista de hijos del padre del nodo a eliminar
        ultimoHermano = l_fin(hermanos); // El final de la lista anterior

        while( hijo != fin ) { // Agrega todos los hijos a la lista de hermanos
            l_insertar(hermanos, ultimoHermano, hijo->elemento);
            hijo = l_siguiente(hermanos, hijo->elemento);
            ultimoHermano = l_siguiente(hermanos, ultimoHermano);
        }

        l_insertar(hermanos, ultimoHermano, hijo->elemento);

        // free y cosas
        l_eliminar(hermanos, pa, fEliminar);
        l_destruir(&(pa->hijos), fEliminar);
        fEliminar(pa->elemento);
        free(pa);
    }
}

void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    destruirRecursivo(a, fEliminar, (*a)->raiz);
}

void destruirRecursivo(tArbol * a, void (*fEliminar)(tElemento), tNodo  n) {

    destruirRecursivo(a,fEliminar, l_primera(n->hijos));

    a_eliminar(*a, n, fEliminar);
}

tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}

tNodo a_raiz(tArbol a) {
    return a->raiz;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) {

}
