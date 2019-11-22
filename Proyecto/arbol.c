#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void destruirRecursivo(tArbol * a, void (*fEliminar)(tElemento), tNodo  n);
void Profundidad(tNodo raiz);
void (*fEliminarParaDestruir) (tElemento);
void fEliminarLocal(tElemento e);


void crear_arbol(tArbol *a){

    *a=(tArbol) malloc(sizeof(struct arbol));

    if((*a)==NULL) exit(ARB_ERROR_MEMORIA);

    (*a)->raiz=NULL;
}

void crear_raiz(tArbol a, tElemento e) {

    if((a->raiz)!=NULL) exit(ARB_OPERACION_INVALIDA);

    // Creo un nodo auxiliar que sera la raiz
    a->raiz=(tNodo) malloc(sizeof(struct nodo));
    if(a->raiz==NULL) exit(ARB_ERROR_MEMORIA);

    // Creo e inicializo como vacia la lista de hijos
    tLista listaHijos;
    crear_lista(&listaHijos);
    a->raiz->elemento = e;
    a->raiz->hijos = listaHijos;
    a->raiz->padre = NULL;

}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){//nh hermano derecho

    tPosicion nhPos = NULL, primerHermano = NULL, ultimoHermano = NULL;
    tLista hermanos = NULL;

    //creo el nodo a insertar
    tNodo nuevo = (tNodo)malloc(sizeof(struct nodo));
    if (nuevo == NULL) exit(ARB_ERROR_MEMORIA);

    //creo una lista de hijos vac�a para el nuevo nodo
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
        if(nhPos == NULL ) { exit(ARB_POSICION_INVALIDA); }

        l_insertar(np->hijos,nhPos,(tElemento) nuevo);

    }else{  //nuevo es el primer hijo de np
        l_insertar(np->hijos, l_fin(np->hijos), (tElemento) nuevo);
    }
    return nuevo;
}


void f(tElemento e) {}

void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento)) {

    tPosicion hijo = NULL, ultimoHermano = NULL, paPos = NULL, primerHermano = NULL;
    tNodo padre = NULL, hijoNodo = NULL;
    int length = 0;
    tLista hermanos = NULL;

    tLista hijos = pa->hijos;
    hijo = l_primera(pa->hijos); // Hijo es puntero al primer hijo de la lista

    if( a->raiz == pa ) { // Si pa es la raiz
        if(l_longitud(pa->hijos) == 0) {

            l_destruir(&(pa->hijos), fEliminar);
            fEliminar(pa->elemento);
            free(pa);
            a->raiz = NULL;
        } else {
            if(l_longitud(pa->hijos) == 1) { // Si no, si el siguiente al siguiente es nulo, la lista tiene un solo elemento
                a->raiz = l_recuperar(hijos, hijo);
            } else {
                exit(ARB_OPERACION_INVALIDA);
            }

        }

    } else { // Si pa no es la raiz
        padre = pa->padre; // Padre del nodo a eliminar
        hermanos = padre->hijos; // Lista de hijos del padre del nodo a eliminar
        primerHermano = l_primera(hermanos); // Principio de la lista de hermanos
        ultimoHermano = l_fin(hermanos); // El final de la lista anterior

        while(primerHermano != ultimoHermano) { // Se busca al nodo dentro de la lista de hijos del padre
            if(l_recuperar(hermanos, primerHermano) == pa) {
                paPos = (ultimoHermano = l_primera(hermanos)) ? hermanos : l_anterior(hermanos, ultimoHermano);
                break;
            }
            primerHermano = l_siguiente(hermanos, primerHermano);
        }

        if(l_recuperar(hermanos, ultimoHermano) == pa) {
                paPos = (ultimoHermano = l_primera(hermanos)) ? hermanos : l_anterior(hermanos, ultimoHermano);
        }



        //Hijo es puntero al primer hijo de la lista
        length = l_longitud(pa->hijos);
        while( length > 0 ) { // Agrega todos los hijos a la lista de hermanos
            hijoNodo = l_recuperar(hijos, hijo);
            hijoNodo->padre = padre;
            l_insertar(hermanos, ultimoHermano, hijoNodo);

            hijo = l_siguiente(hijos, hijo);
            ultimoHermano = l_siguiente(hermanos, ultimoHermano);
            length--;
        }

//        ultimaInsercion = l_recuperar(hijos, hijo);
//        ultimaInsercion->padre = padre;
//        l_insertar(hermanos,ultimoHermano,ultimaInsercion);

        // free y cosas

        l_eliminar(hermanos, paPos, &f);
        l_destruir(&(pa->hijos), &f);
        fEliminar(pa->elemento);
        free(pa);
    }
}


void a_destruir(tArbol * a, void (*fEliminar)(tElemento)) {
    fEliminarParaDestruir = fEliminar;
    l_destruir(&((*a)->raiz->hijos), &fEliminarLocal);

    fEliminar((*a)->raiz->elemento);
    (*a)->raiz->elemento = NULL;

    free((*a)->raiz);
    (*a)->raiz = NULL;

    free(*a);
    a = NULL;
    fEliminarParaDestruir = NULL;
}

void fEliminarLocal(tElemento e) {
    tNodo nodoABorrar = (tNodo) e;
    l_destruir(&nodoABorrar->hijos, &fEliminarLocal);
    fEliminarParaDestruir(nodoABorrar->elemento);
    nodoABorrar->elemento = NULL;
    nodoABorrar->padre = NULL;
    free(nodoABorrar);
}

tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento; // Devuelve el elemento
}

tNodo a_raiz(tArbol a) {
    return a->raiz; // Devuelve la raiz
}

tLista a_hijos(tArbol a, tNodo n){
    return n->hijos; // Devuelve la lista de hijos
}

void MostrarArbol(tArbol arbol, tNodo raiz) {
    // Este procedimiento solo fue utilizado en nuestro programa de prueba

    tLista hijos  = raiz->hijos; // Pide la lista de hijos

    if(hijos == NULL) // Si no tiene hijos, sale porque no tiene nada que mostrar
        return;

    tPosicion primer = l_primera(hijos);
    int length = l_longitud(hijos);

    Profundidad(raiz); // Calcula la profundidad del nodo
    printf("%i\n", (int) raiz->elemento); // Imprime su elemento, asumiendo que es un entero

    while(length > 0) { // Luego por cada hijo
        MostrarArbol(arbol, l_recuperar(hijos, primer)); // Repite
        primer = l_siguiente(hijos, primer);
        length--;
    }
}

void Profundidad(tNodo raiz) {
    tNodo p = raiz->padre; // Pide el padre

    while(p!=NULL) { // Mientras el padre no sea nulo, es decir, no haya llegado a la raiz
        printf("--"); // Imprime dos guiones en representacion a un nivel
        p = p->padre;
    }

}

tNodo buscarNodo(tArbol a, tNodo raizActual, tElemento e) {
    tLista lista = raizActual->hijos; // Pide la lista de hijos
    tPosicion aux = NULL;
    tNodo recursive = NULL;
    int length = 0;

    if(lista == NULL) { // Si no tiene hijos, sale avisando que no encontro nada
        return NULL;
    }

    if(raizActual->elemento == e) {
        return raizActual; // Si el elemento actual es el buscado, lo devuelve
    }

    length = l_longitud(lista);
    aux = l_primera(lista);

    while ( length > 0 ) { // Sino, recorre la lista de hijos en busca del nodo

        recursive = buscarNodo(a, l_recuperar(lista, aux), e);

        if(recursive != NULL) {
            return recursive;
        }

        aux = l_siguiente(lista, aux);
        length--;
    }

    return NULL;
}


void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) { //caso particular para ver si n = a
    //busco al nodo n en a
    tNodo raiz = buscarNodo(a, a->raiz, n->elemento);

    // Si no encuentra al nodo, sale
    if(raiz == NULL)
        return;

    // Si el nodo es la raiz, cambia los punteros
    if(raiz->padre == NULL) {
        sa = &a;
        a = NULL;
        return;
    }

    // Sino, "clona" el arbol
    tLista hermanos   = raiz->padre->hijos;
    tPosicion primera = l_primera(hermanos);
    tPosicion fin     = l_fin(hermanos);

    while ( primera != NULL && primera != fin ) {

        if ( l_recuperar(hermanos, primera) == n ) {

            tNodo nuevaRaiz = (tNodo) malloc(sizeof(struct nodo));
            if (nuevaRaiz == NULL) exit(ARB_ERROR_MEMORIA);

            nuevaRaiz->elemento = n->elemento;
            nuevaRaiz->hijos = n->hijos;
            nuevaRaiz->padre = NULL;
            n->hijos = NULL;
            (*sa)->raiz = nuevaRaiz;
            return;
        }

        primera = l_siguiente(hermanos, primera);
    }



}
