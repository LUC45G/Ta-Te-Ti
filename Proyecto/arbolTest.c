#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

#define POS_NULA NULL

void recorrido_raiz(tArbol A);
/*void fEliminar(tElemento e);

void fEliminar(tElemento e){
    printf("Elemento a eliminar: %d", *((int*) e));
    free(e);
    printf("hace el free");
}*/


void recorrido_raiz(tArbol A) {
        tLista lista_raiz_1 = a_hijos(A, a_raiz(A));
        tPosicion actual_raiz_1 = l_primera(lista_raiz_1);
        tPosicion fin_raiz_1 = l_fin(lista_raiz_1);

        while (actual_raiz_1 != fin_raiz_1) {
            tNodo nodo = (tNodo) l_recuperar(lista_raiz_1, actual_raiz_1);
            tElemento  elemento = a_recuperar(A, nodo);
            printf("Elemento: %i \n", *((int *) elemento));
            actual_raiz_1 = l_siguiente(lista_raiz_1, actual_raiz_1);

        }
}

int mainBruno(){

    //CREACIÓN DEL ÁRBOL
    printf("Hola");
    tArbol A;
    printf("Hola");
    int * ent=(int*)malloc(sizeof(int));
    crear_arbol(&A);
    if (a_raiz(A) == NULL)
    //printf("Se creo el arbol con exito\n");
    printf("\n");
    printf("\n");

    //CREACIÓN DE LA RAÍZ
    //printf("Creando raiz con rotulo 1\n");
    int e1 = 1;
    crear_raiz(A, &e1);
    if (a_raiz(A) != NULL) {
        //printf("La raiz se creo con exito \n");
        tElemento elem_raiz = a_recuperar(A, a_raiz(A));
        //printf("Rotulo de la raiz (Deberia ser 1): %i \n", *((int *) elem_raiz));
    }
    //printf("\n");
    //printf("\n");
    recorrido_raiz(A);

    //INSERTO ELEMENTOS COMO NODOS HIJOS DE LA RAIZ
    //printf("Inserto hijo1 de raiz (2) e hijo2 de raiz (3) \n");
    int e2 = 2;
    int e3 = 3;
    int e4 = 4;
    int e5 = 5;
    //int e3 = 3;
    tNodo hijo1_raiz = a_insertar(A, a_raiz(A), NULL, &e2);
    tElemento elem = a_recuperar(A, hijo1_raiz);
    tNodo hijo1_raiz3 = a_insertar(A, a_raiz(A), NULL, &e3);
    tNodo hijo1_raiz4 = a_insertar(A, a_raiz(A), NULL, &e4);
    tNodo hijo1_raiz5 = a_insertar(A, a_raiz(A), NULL, &e5);
    printf("Rotulo del hijo1(Deberia ser 1): %i \n", *((int *) elem));
    elem = a_recuperar(A, hijo1_raiz3);
    printf("Rotulo del hijo1(Deberia ser 2): %i \n", *((int *) elem));
    elem = a_recuperar(A, hijo1_raiz4);
    printf("Rotulo del hijo1(Deberia ser 3): %i \n", *((int *) elem));
    elem = a_recuperar(A, hijo1_raiz5);
    printf("Rotulo del hijo1(Deberia ser 4): %i \n", *((int *) elem));





    //printf("Rotulo de la raiz (Deberia ser 1): %i \n", *((int *) elem));
    recorrido_raiz(A);
    //tNodo hijo2_raiz = a_insertar(A, a_raiz(A), NULL, &e3);

    //a_eliminar(A, hijo2_raiz, fEliminar);
    // a_eliminar(A, hijo1_raiz, fEliminar);
    //printf("Elimino sin problemas");
    recorrido_raiz(A);


    //tElemento elem_2 = a_recuperar(A, hijo2_raiz);
    /*printf("Rotulo de la raiz (Deberia ser 1): %i \n", *((int *) elem_2));

    //RECORRO LISTA HIJOS DE RAIZ
    printf("Recorro lista de raiz para ver como se insertaron los elementos \n");

    tLista lista_raiz = a_hijos(A, a_raiz(A));
    tPosicion actual_raiz = l_primera(lista_raiz);
    tPosicion fin_raiz = l_fin(lista_raiz);

    while (actual_raiz != fin_raiz) {
        tNodo nodo = (tNodo) l_recuperar(lista_raiz, actual_raiz);
        tElemento * elemento = a_recuperar(A, nodo);
        printf("Elemento: %i \n", *((int *) elemento));
        actual_raiz = l_siguiente(lista_raiz, actual_raiz);

    }

    printf("\n");
    printf("\n");


    //Veo si los hijos se insertaron
    tElemento elem_hijo1_raiz = a_recuperar(A, hijo1_raiz);
    tElemento elem_hijo2_raiz = a_recuperar(A, hijo2_raiz);
    printf("Elemento del primer hijo (Deberia ser 2): %d \n", *((int *) elem_hijo1_raiz));
    printf("Elemento del segundo hijo (Deberia ser 3): %d \n", *((int *) elem_hijo2_raiz));
    printf("\n");
    printf("\n");

    //INSERTO ELEMENTOS COMO HIJOS DE LOS HIJOS DE LA RAIZ
    printf("Inserto hijos en los hijos de la raiz \n");
    //int * e4 = (int *) 4;
    //int * e5 = (int *) 5;
    int * e6 = (int *) 6;
    int * e7 = (int *) 7;
    //tNodo hijo_a_hijo1 = a_insertar(A, hijo1_raiz, NULL, &e4);
    //tNodo hijo_b_hijo1 = a_insertar(A, hijo1_raiz, NULL, &e5);

    tNodo hijo_a_hijo2 = a_insertar(A, hijo2_raiz, NULL, &e6);
    tNodo hijo_b_hijo2 = a_insertar(A, hijo2_raiz, NULL, &e7);

    //tElemento elem_hijo_a = a_recuperar(A, hijo_a_hijo1);
    //tElemento elem_hijo_b = a_recuperar(A, hijo_b_hijo1);
    //printf("Hijos de hijo_1 (Deberian ser 4 y 5): %i, %i", *((int *)elem_hijo_a), *((int *) elem_hijo_b));
    //printf("\n");

    tElemento elem_hijo2_a = a_recuperar(A, hijo_a_hijo2);
    tElemento * elem_hijo2_b = a_recuperar(A, hijo_b_hijo2);
    printf("Hijos de hijo_2 (Deberian ser 6 y 7): %i, %i", *((int *) elem_hijo2_a), *((int *) elem_hijo2_b));
    printf("\n");
    printf("\n");

    printf("Agrego un tercer elemento al hijo 1 \n");
    int * e8 = (int *) 8;
    tNodo hijo_c_hijo1 = a_insertar(A, hijo1_raiz, NULL, &e8);
    tElemento elem_hijo_c = a_recuperar(A, hijo_c_hijo1);
    printf("Tercer hijo_1 agregado (Deberia ser 8): %i", *((int*) elem_hijo_c));
    printf("\n");
    printf("\n");*/

    //RECORRO LISTA HIJOS DE HIJO_1
    //printf("Recorro lista de hijo_1 para ver como se insertaron los elementos \n");

/*    tLista lista_hijo1 = a_hijos(A, hijo1_raiz);
    tPosicion actual = l_primera(lista_hijo1);
    tPosicion fin = l_fin(lista_hijo1);

    while (actual != fin) {
        tNodo n = (tNodo) l_recuperar(lista_hijo1, actual);
        tElemento * elem = a_recuperar(A, n);
        printf("Elemento: %i \n", *((int *) elem));
        actual = l_siguiente(lista_hijo1, actual);

    }

    printf("\n");
    printf("\n");

    //RECORRO LISTA HIJOS DE HIJO_2
    printf("Recorro lista de hijo_2 para ver como se insertaron los elementos \n");

    tLista lista_hijo2 = a_hijos(A, hijo2_raiz);
    tPosicion actual_hijo2 = l_primera(lista_hijo2);
    tPosicion fin_hijo2 = l_fin(lista_hijo2);

    while (actual_hijo2 != fin_hijo2) {
        tNodo nodito = (tNodo) l_recuperar(lista_hijo2, actual_hijo2);
        tElemento * elemento_hijo2 = a_recuperar(A, nodito);
        printf("Elemento: %i \n", *((int *) elemento_hijo2));
        actual_hijo2 = l_siguiente(lista_hijo2, actual_hijo2);

    }

    printf("\n");
    printf("\n");*/

    //printf("voy a eliminar raiz");
    //a_eliminar(A, a_raiz(A), fEliminar);

    //ELIMINO ELEMENTOS
    //printf("Quiero ver si puedo eliminar la raiz teniendo mas de un hijo en la lista del nodo raiz (Funciona) \n");
    //a_eliminar(A, a_raiz(A), fEliminar); ESTO FUNCIONA
    printf("\n");

    /*printf("Elimino nodo hijo_1 \n");
    a_eliminar(A, hijo1_raiz, fEliminar);
    printf("\n");
    printf("\n");
    printf("Recorro lista de raiz para ver como se insertaron los elementos \n");
    recorrido_raiz(A);
    printf("\n");*/

    /** esto funciona*/
    /*printf("Elimino nodo hijo_2 \n");
    a_eliminar(A, hijo2_raiz, fEliminar);
    printf("\n");
    printf("\n");
    printf("Recorro lista de raiz para ver como se insertaron los elementos \n");
    recorrido_raiz(A)*/

    /*printf("Ahora voy a eliminar los primeros tres hijos de la raiz (4, 5, 8) \n");
    tLista lista_raiz_1 = a_hijos(A, a_raiz(A));
    tPosicion primer_hijo = l_primera(lista_raiz_1);
    a_eliminar(A, (tNodo) l_recuperar(lista_raiz_1, primer_hijo), fEliminar);
    recorrido_raiz(A);

    printf("\n");
    printf("\n")*/

    //DESTRUIR ARBOL
    //printf("Se va a destruir el arbol");
    //a_destruir(A, fEliminar);

    return 0;
}


/*void fEliminar(tElemento e) {
    free(e);
    //void* x=(void*)0;

    //return x;
}*/
