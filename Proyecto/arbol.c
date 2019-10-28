#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void destruirRecursivo(tArbol * a, void (*fEliminar)(tElemento), tNodo  n);
// tPosicion buscarNodo(tNodo raiz, tNodo buscado, tPosicion buscador);


void crear_arbol(tArbol *a){
    tArbol arbol = (tArbol) malloc(sizeof(struct arbol)); //o tNodo?

    // if(arbol == NULL) romper

    //todos los atributos en nulo
    arbol->raiz->elemento = NULL; //ver los -> y .
    arbol->raiz->hijos = NULL;
    *a = arbol;
}

void crear_raiz(tArbol a, tElemento e) {

    if ( a->raiz->elemento != NULL ) exit(ARB_OPERACION_INVALIDA);
    // Creo un nodo auxiliar que sera la raiz
    tNodo nodoAux = (tNodo)malloc(sizeof(struct nodo));


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
    printf("Insertando %i en el arbol como hijo de %i\n\n", e, np->elemento);

    tPosicion nhPos, primerHermano, ultimoHermano;

    tLista hermanos;
    //creo el nodo a insertar
    tNodo nuevo;

    nuevo = (tNodo)malloc(sizeof(struct nodo)); //ACA ES DONDE SE ROMPE
    //creo una lista de hijos vacía para el nuevo nodo
    tLista listaHijos;

    crear_lista(&listaHijos);
    //Set de atributos del nuevo nodo
    nuevo->elemento = e;
    nuevo->padre = np;
    nuevo->hijos = listaHijos;


    if (nh != NULL){

        // Recorrer lista de hijos de np en busca de nh
        hermanos = np->hijos; // Lista de hijos del padre del nodo a eliminar
        primerHermano = l_primera(hermanos); // Principio de la lista de hermanos
        ultimoHermano = l_fin(hermanos); // El final de la lista anterior

        while(primerHermano != ultimoHermano) {
            if(l_recuperar(hermanos, primerHermano) == nh){
                nhPos = primerHermano;
                break;
            }
            primerHermano = l_siguiente(hermanos, primerHermano);
        }
        // Sino tirar arb posicion invalidisima
        l_insertar(np->hijos,nhPos,(tElemento) nuevo);
    }else{  //nuevo es el primer hijo de np
        l_insertar(np->hijos,l_primera(np->hijos),(tElemento) nuevo);
    }
    return nuevo;
}

void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento)) {

    tPosicion hijo, ultimoHermano, fin, paPos, primerHermano;
    tNodo padre;
    tLista hermanos;

    hijo = l_primera(pa->hijos); // Hijo es puntero al primer hijo de la lista
    fin = l_fin(pa->hijos); // Fin es el ultimo elemento de la lista de hijos

    if( a->raiz == pa ) { // Si pa es la raiz
        printf("\nIntentando eliminar la raiz\n\n");
        printf("Longitud lista de hijos: %i", l_longitud(pa->hijos));
        if(l_longitud(pa->hijos) == 0) { // Si el primer elemento es el ultimo, la lista esta vacia
            printf("raiz sin hijos\n");
            l_destruir(&(pa->hijos), fEliminar);
            printf("un hijo 1");
            fEliminar(pa->elemento);
            printf("un hijo 2");
            free(pa);
            printf("un hijo 3");
            a->raiz = NULL;
            printf("un hijo 4");

        } else {

            if(l_longitud(pa->hijos) == 1) { // Si no, si el siguiente al siguiente es nulo, la lista tiene un solo elemento
                printf("raiz con un solo hijo\n");
                a->raiz = hijo->elemento;
            } else {
                exit(ARB_OPERACION_INVALIDA);
            }

        }

    } else { // Si pa no es la raiz

        printf("\nIntentando eliminar un nodo generico\n\n");

        padre = pa->padre; // Padre del nodo a eliminar
        hermanos = padre->hijos; // Lista de hijos del padre del nodo a eliminar
        primerHermano = l_primera(hermanos); // Principio de la lista de hermanos
        ultimoHermano = l_fin(hermanos); // El final de la lista anterior

        printf("Padre de %i: %i\n%i tiene hijos: %i\n\n", pa->elemento, padre->elemento, pa->elemento, l_longitud(pa->hijos) );

        while(primerHermano != ultimoHermano) {
            if(l_recuperar(hermanos, primerHermano) == pa) {
                paPos = primerHermano;
                printf("Elemento encontrado en la lista de hermanos");
                break;
            }
            primerHermano = l_siguiente(hermanos, primerHermano);
        }



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

    while( auxPos != fin) {
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
    return n->hijos;
}

void MostrarArbol(tArbol arbol, tNodo raiz) {

    tLista hijos  = raiz->hijos;

    if(hijos == NULL)
        return;

    tPosicion primer = l_primera(hijos);
    tPosicion fin    = l_fin(hijos);

    Profundidad(raiz);
    printf("%i\n", (int) raiz->elemento);

    while(primer != hijos && primer != fin) {
        MostrarArbol(arbol, l_recuperar(hijos, primer));
        primer = l_siguiente(hijos, primer);
    }

    if( primer != hijos )
        MostrarArbol(arbol, l_recuperar(hijos, primer));


}

void Profundidad(tNodo raiz) {
    tNodo p = raiz->padre;

    while(p!=NULL) {
        printf("--");
        p = p->padre;
    }

}

tNodo buscarNodo(tArbol a, tNodo raizActual, tElemento e) {
    tLista lista = raizActual->hijos;

    if(lista == NULL) {
        return NULL;
    }
    if(raizActual->elemento == e) {
        return raizActual;
    }

    tPosicion auxFin = l_fin(lista);
    tPosicion aux = l_primera(lista);

    while ( aux != lista && aux != auxFin) {

        tNodo recursive = buscarNodo(a, l_recuperar(lista, aux), e);
        if(recursive != NULL)
            return recursive;
        aux = l_siguiente(lista, aux);
    }

    if (aux != lista)
        return buscarNodo(a, l_recuperar(lista, aux), e); // Caso especial en que la lista tiene un solo elemento

    return NULL;
}


void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) { //caso particular para ver si n = a
    //busco al nodo n en a
    //tNodo raiz = n;
    tNodo raiz = buscarNodo(a, a->raiz, n->elemento);

    if(raiz == NULL)
        return;

    if(raiz->padre == NULL) {
        sa = &a;
        a = NULL;
        return;
    }

    tLista hermanos = raiz->padre->hijos;
    tPosicion primera = l_primera(hermanos);
    tPosicion fin = l_fin(hermanos);

    while ( primera != NULL && primera != fin ) {
        if ( l_recuperar(hermanos, primera) == n ) {
            tNodo nuevaRaiz = (tNodo) malloc(sizeof(struct nodo));
            nuevaRaiz->elemento = n->elemento;
            nuevaRaiz->hijos = n->hijos;
            nuevaRaiz->padre = NULL;
            n->hijos = NULL;
            (*sa)->raiz = nuevaRaiz;
            //l_eliminar(hermanos, primera, &fEliminar);
            return;
        }
        primera = l_siguiente(hermanos, primera);
    }



}
