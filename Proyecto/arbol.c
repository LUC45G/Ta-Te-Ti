#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void destruirRecursivo(tArbol * a, void (*fEliminar)(tElemento), tNodo  n);
void Profundidad(tNodo raiz);
// tPosicion buscarNodo(tNodo raiz, tNodo buscado, tPosicion buscador);


void crear_arbol(tArbol *a){
    //tArbol arbol = (tArbol) malloc(sizeof(struct arbol));
    *a=(tArbol) malloc(sizeof(struct arbol));
    // if(arbol == NULL) romper
    if((*a)==NULL)
        exit(ARB_ERROR_MEMORIA);
    //todos los atributos en nulo
    (*a)->raiz=NULL;
/*
    arbol->raiz->elemento = NULL; //ver los -> y .
    arbol->raiz->hijos = NULL;
    *a = arbol;*/
}

void crear_raiz(tArbol a, tElemento e) {

    //if ( a->raiz->elemento != NULL ) exit(ARB_OPERACION_INVALIDA);
    if((a->raiz)!=NULL) exit(ARB_OPERACION_INVALIDA);
    // Creo un nodo auxiliar que sera la raiz
    //tNodo nodoAux;// = (tNodo)malloc(sizeof(struct nodo));
    a->raiz=(tNodo) malloc(sizeof(struct nodo));

    if(a->raiz==NULL) exit(ARB_ERROR_MEMORIA);
    // Creo e inicializo como vacia la lista de hijos
    tLista listaHijos;
    crear_lista(&listaHijos);
    a->raiz->elemento = e;
    a->raiz->hijos = listaHijos;
    a->raiz->padre = NULL;
    // Inicializo el nuevo nodo que sera raiz
    /*nodoAux->elemento = e;
    nodoAux->hijos = listaHijos;
    nodoAux->padre = NULL;

    // Asigno la nueva raiz
    a->raiz = nodoAux;
    */


}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){//nh hermano derecho

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

/*
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){//nh hermano derecho
        //Creo el nuevo nodo y lo inicializo
        tNodo nuevo = (tNodo) malloc(sizeof(struct nodo));
        tLista hijosDeNuevo = (tLista) malloc(sizeof(struct celda));
        crear_lista(&hijosDeNuevo);
        nuevo->elemento = e;
        nuevo->padre = np;
        nuevo->hijos = hijosDeNuevo;
        //Hijos del padre del nuevo nodo
        tLista hijosDePa = np->hijos;

        if (nh == NULL){
            l_insertar(hijosDePa,l_fin(hijosDePa),(tElemento) nuevo);
        }else{
            //Vamos a buscar la posicion del hermano "nh" para agregar al "nuevo"
            tPosicion primerHijoDePa = l_primera(hijosDePa);
            tPosicion ultimoHijoDePa = l_fin(hijosDePa);
            tPosicion nodoHermano;
            int encontre = 0; //Lo uso para terminar el while siencuentro a nh

            while (primerHijoDePa != ultimoHijoDePa && !encontre){
                if (l_recuperar(hijosDePa,primerHijoDePa) == nh){ //Si encentro a la posicion de nh:
                        encontre = 1;
                        nh = primerHijoDePa;
                }else{
                    l_siguiente(hijosDePa,primerHijoDePa);
                }
            }
            //Si cuando sale del while, no encontró a nh entonces es porque el ultimo es nh
            //Aca podríamos comparar una vez mas y tirar el error si no es == nh
            if (!encontre){
                nodoHermano = ultimoHijoDePa;
            }
            //Una vez que encontre la posicion de "nh", inserto al "nuevo"
            l_insertar(hijosDePa,nodoHermano,(tElemento) nuevo);
        }

        return nuevo;

}
*/

void f(tElemento e) {}

void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento)) {

    tPosicion hijo, ultimoHermano, fin, paPos, primerHermano;
    tNodo padre;
    tLista hermanos;

    tLista hijos = pa->hijos;
    hijo = l_primera(pa->hijos); // Hijo es puntero al primer hijo de la lista
    fin = l_fin(pa->hijos); // Fin es el ultimo elemento de la lista de hijos

    if( a->raiz == pa ) { // Si pa es la raiz
        if(l_longitud(pa->hijos) == 0) { // Si el primer elemento es el ultimo, la lista esta vacia

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

        while(primerHermano != ultimoHermano) {
            if(l_recuperar(hermanos, primerHermano) == pa) {
                paPos = (ultimoHermano = l_primera(hermanos)) ? hermanos : l_anterior(hermanos, ultimoHermano);
                break;
            }
            primerHermano = l_siguiente(hermanos, primerHermano);
        }

        if(l_recuperar(hermanos, ultimoHermano) == pa) {
                paPos = (ultimoHermano = l_primera(hermanos)) ? hermanos : l_anterior(hermanos, ultimoHermano);
        }

    //borrar al nodo actual con el fEliminar que borre el nodo
        //borrar la estructura de la lista pero no borrar los nodos
        //tener cuidado con el centinela en la lista de los hijos
        tNodo hijoNodo;

        //Hijo es puntero al primer hijo de la lista
        while( hijo != fin ) { // Agrega todos los hijos a la lista de hermanos
            hijoNodo = l_recuperar(hijos, hijo);
            hijoNodo->padre = padre;
            l_insertar(hermanos, ultimoHermano, hijoNodo);//ESTABLECER EL NUEVO PADRE
            //ACTUALIZAR EL PADRE A LOS NODOS HIJOS
            //tNodo padreDeHijoNodo = hijoNodo->padre;
            //padreDeHijoNodo = padre;

            hijo = l_siguiente(hijos, hijo);
            ultimoHermano = l_siguiente(hermanos, ultimoHermano);
        }
        //printf("LLEGO ");

        //if(!(hijo == hermanos || hijo == fin)) {
        if (hijo != fin){
          //printf("LLEGO 10");
            hijoNodo = l_recuperar(hijos, hijo);
          //printf("LLEGO 20");
            hijoNodo->padre = padre;
          //printf("LLEGO 30");
            l_insertar(hermanos, ultimoHermano, hijoNodo);
          //printf("LLEGO 40");
        }
        tNodo ultimaInsercion = l_recuperar(hijos, hijo);
        ultimaInsercion->padre = padre;
        l_insertar(hermanos,ultimoHermano,ultimaInsercion);

        // free y cosas, falta buscar papos

        l_eliminar(hermanos, paPos, &f);
        l_destruir(&(pa->hijos), &f);
        //fEliminar(pa->elemento);
        free(pa);
        //printf("LLEGO5 \n\n");
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
