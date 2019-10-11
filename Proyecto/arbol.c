#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void destruirRecursivo(tArbol * a, void (*fEliminar)(tElemento), tNodo  n);
// tPosicion buscarNodo(tNodo raiz, tNodo buscado, tPosicion buscador);

void crear_arbol(tArbol *a){
    tArbol arbol = (tArbol) malloc(sizeof(tArbol)); //o tNodo?
    //todos los atributos en nulo
    arbol->raiz->elemento = NULL; //ver los -> y .
    arbol->raiz->hijos = NULL;

    *a = arbol;
}

void crear_raiz(tArbol a, tElemento e) {

    if ( a->raiz->elemento != NULL ) exit(ARB_OPERACION_INVALIDA);

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

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){//nh hermano derecho
//creo el nodo a insertar
    tNodo nuevo = malloc(sizeof(tNodo));
    //creo una lista de hijos vacía para el nuevo nodo
    tLista listaHijos = malloc(sizeof(tLista));
    crear_lista(&listaHijos);

    //Set de atributos del nuevo nodo
    nuevo->elemento = e;
    nuevo->padre = np;
    nuevo->hijos = listaHijos;

    if(nh==NULL) {
        l_insertar(a->raiz->hijos, l_primera(a->raiz->hijos), nuevo);
        return;
    }

    if (nh->padre != np) exit(ARB_POSICION_INVALIDA);




    tPosicion nhPos = malloc(sizeof(tPosicion));
    if (nh != NULL){
        // Recorrer lista de hijos de np en busca de nh
        // Sino tirar arb posicion invalidisima
        l_insertar(np->hijos,nhPos,(tElemento) nuevo);
    }else{  //nuevo es el primer hijo de np
        l_insertar(np->hijos,l_primera(np->hijos),(tElemento) nuevo);
    }

    return nuevo;
}

void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento)) {

    tPosicion hijo, ultimoHermano, fin, paPos;
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

        // free y cosas, falta buscar papos
        l_eliminar(hermanos, paPos, fEliminar);
        l_destruir(&(pa->hijos), fEliminar);
        fEliminar(pa->elemento);
        free(pa);
    }
}

void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    destruirRecursivo(a, fEliminar, (*a)->raiz);
}

void destruirRecursivo(tArbol * a, void (*fEliminar)(tElemento), tNodo  n) {

    tPosicion auxPos = l_primera(n->hijos);
    tPosicion fin = l_fin(n->hijos);

    while( l_siguiente(n->hijos, auxPos) != NULL) {
        destruirRecursivo(a,fEliminar, l_recuperar(n->hijos, auxPos->elemento));
        auxPos = l_siguiente(n->hijos, auxPos);
    }


    a_eliminar(*a, n, fEliminar);
}

tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}

tNodo a_raiz(tArbol a) {
    return a->raiz;
}

tLista a_hijos(tArbol a, tNodo n){
    printf("hijoooooooooos\n");
    return n->hijos;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) { //caso particular para ver si n = a
    //busco al nodo n en a
    tNodo raiz = malloc(sizeof(tNodo));
    int encontre;
    if (a->raiz != n){
        encontre = 0;
        tLista hijosdeA;
        crear_lista(&hijosdeA);

        tPosicion buscador = (tPosicion) malloc(sizeof(struct celda));
        buscador = NULL;//SI BUSCADOR QUEDO EN NULL ES PORQUE n = a
        raiz = a->raiz;
        //UNA VEZ ENCONTRADA LA POSICION DEL NODO SETEARLE EL PADRE NULL Y SACARLO DE LA LISTA DE HIJOS DE SU PADRE
    }
    tPosicion posDelNodo = (tPosicion) malloc(sizeof(tPosicion));


}

tNodo buscarNodo(tArbol a, tNodo raizActual, tElemento e) {
    tLista lista = raizActual->hijos;
    if(lista == NULL) {
        return;
    }
    tPosicion auxFin = l_fin(lista);
    tPosicion aux = l_primera(raizActual->hijos);

    while (aux != auxFin) {
            printf("Entro al while");
        if(( (tNodo)l_recuperar(lista, aux) )->elemento == e)
            return l_recuperar(lista, aux);
        else {
            buscarNodo(a, l_recuperar(lista, aux), e);
        }

        aux = l_siguiente(lista, aux);
    }

    return NULL;
}
