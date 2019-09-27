#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void crear_raiz(tArbol a, tElemento e) {

    if ( a.raiz != NULL ) exit(ARB_OPERACION_INVALIDA);

    // Creo un nodo iliar que sera la raiz
    tNodo nodoAux = malloc(sizeof(tNodo));

    // Creo e inicializo como vacia la lista de hijos
    tLista listaHijos;
    crear_lista(&listaHijos);

    // Inicializo el nuevo nodo que sera raiz
    nodoAux.elemento = e;
    nodoAux.hijos = listaHijos;
    nodoAux.padre = NULL;

    // Asigno la nueva raiz
    a.raiz = nodoAux;

}

void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento)) {

    tPosicion hijo, ultimoHermano, fin;
    tNodo padre;
    tLista hermanos;

    hijo = l_primera(pa.hijos); // Hijo es puntero al primer hijo de la lista
    fin = l_fin(pa.hijos); // Fin es el ultimo elemento de la lista de hijos

    if( a.raiz == pa ) { // Si pa es la raiz

        if(hijo == fin) { // Si el primer elemento es el ultimo, la lista esta vacia
            // Eliminar el nodo sin problemas
        } else {

            if(l_siguiente(pa.hijos, hijo) == NULL) { // Si no, si el siguiente al siguiente es nulo, la lista tiene un solo elemento

            } else {
                exit(ARB_OPERACION_INVALIDA);
            }

        }

    } else { // Si pa no es la raiz

        padre = pa.padre; // Padre del nodo a eliminar
        hermanos = Padre.hijos; // Lista de hijos del padre del nodo a eliminar
        ultimoHermano = l_fin(Hermanos); // El final de la lista anterior

        while( hijo != fin ) { // Agrega todos los hijos a la lista de hermanos
            l_insertar(hermanos, ultimoHermano, hijo.elemento);
            hijo = l_siguiente(hermanos, hijo.elemento);
            ultimoHermano = l_siguiente(hermanos, ultimoHermano);
        }

        l_insertar(Hermanos, UltimoHermano, hijo.elemento);

        // free y cosas
        l_eliminar(hermanos, pa, fEliminar);
    }
}

tElemento a_recuperar(tArbol a, tNodo n){
    return n.elemento;
}

tNodo a_raiz(tArbol a) {
    return a.raiz;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) {

}
