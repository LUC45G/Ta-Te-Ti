#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
    tLista list;
    tPosicion aux;
    int i; int* p = (int*) malloc(sizeof(int));


    crear_lista(&list);
    aux = list;


    for(i = 2; i<7; i++) {
        p = &i;
        l_insertar(list, aux, p);
        aux = l_siguiente(list, aux);
    }

    i = 0;
    aux = l_siguiente(list, list);

    while(i < 6) {
        printf("El: %i\n", *(int *) l_recuperar(list, aux) );
        aux = l_siguiente(list, aux);
        i++;
    }

    return 0;
}
