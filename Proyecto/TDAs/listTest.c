#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
    tLista list;// = (tLista*) malloc(sizeof(struct celda));
    tPosicion auxInsert, auxMostrar;
    //  int* p = (int*) malloc(sizeof(int)),
    int condition = 1, i, index = 0;




    while(condition) {
        printf("\n\nIngrese numero : \n1->Crear lista \n2->Agregar elemento \n3->Mostrar lista \n0->Salir\n\n");
        scanf("%i", &condition);

        switch(condition) {
            case 1:
                crear_lista(&list);
                auxInsert = list;
                auxMostrar = list;

                printf("\nLISTA CREADA CON EXITO\n\n");
                break;

            case 2:
                printf("Ingrese el valor a agregar: \n");
                scanf("%i", &i);
                l_insertar(list, auxInsert, &i);
                auxInsert = l_fin(list);
                break;

            case 3:
                auxMostrar = l_siguiente(list, list);
                while( auxMostrar->siguiente != NULL ) {
                    printf("Elemento %i: %i\n\n", index++, (int) (auxMostrar)->elemento );
                    auxMostrar = l_siguiente(list, auxMostrar);
                }
                printf("Elemento %i: %i\n\n", index, (int) (auxMostrar)->elemento );

            default:
                condition=0;
                break;
        }
    }

                // destruir la lista

    return 0;
}
