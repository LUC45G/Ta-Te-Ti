#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
    tLista list;// = (tLista*) malloc(sizeof(struct celda));
    tPosicion auxInsert, auxMostrar;
    //  int* p = (int*) malloc(sizeof(int)),
    int condition = 1, i, index = 0;

    printf("Recuerde crear la lista antes de utilizar las operaciones Agregar y Mostrar.\n\n");




    while(condition) {
        printf("Ingrese numero : \n1->Crear lista \n2->Agregar elemento \n3->Mostrar lista \n0->Salir\n\n");
        scanf("%i", &condition);

        switch(condition) {
            case 1:
                system("cls");

                crear_lista(&list);
                auxInsert = list;
                auxMostrar = list;

                printf("\nLista creada con exito\n\n");
                break;

            case 2:
                system("cls");
                printf("Ingrese el valor a agregar: \n");
                scanf("%i", &i);
                l_insertar(list, auxInsert, i);
                auxInsert = l_fin(list);
                printf("\nElemento %i agregado con exito\n\n", i);
                break;

            case 3:
                system("cls");
                auxMostrar = l_siguiente(list, list);
                index = 1;

                while( auxMostrar->siguiente != NULL ) { // tengo que usar auxMostrar->siguiente en lugar de l_siguiente(list, auxMostrar) porque se rompe sino
                    printf("Elemento %i: %i\n\n", index++, (int) l_recuperar(list, auxMostrar) );
                    auxMostrar = l_siguiente(list, auxMostrar);
                }

                printf("Elemento %i: %i\n\n", index, (int) l_recuperar(list, auxMostrar) );

                break;
            default:
                condition=0;
                break;
        }
    }

                // destruir la lista

    return 0;
}
