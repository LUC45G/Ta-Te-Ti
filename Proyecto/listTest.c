#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void fEliminarLista(tElemento e) {
    free(e);
}

int mainLista() {
    tLista list;
    tPosicion auxInsert, auxMostrar, auxFin;

    int condition = 1, i, control2 = 0, control1 = 0, index = 0;

    printf("Recuerde crear la lista antes de utilizar las operaciones Agregar y Mostrar.\n\n");




    while(condition) {
        printf("Ingrese numero : \n1->Crear lista \n2->Agregar elemento \n3->Mostrar lista \n0->Salir\n\n");
        scanf("%i", &condition);

        switch(condition) {
            case 1:

                crear_lista(&list);
                auxInsert = list;
                auxMostrar = list;

                printf("\nLista creada con exito\n\n");
                control1 = 1;
                control2 = 0;
                break;

            case 2:
                if (control1){
                    printf("Ingrese el valor a agregar: \n");
                    scanf("%i", &i);
                    l_insertar(list, auxInsert, (tElemento) i);
                    auxInsert = l_fin(list);
                    printf("\nElemento %i agregado con exito\n\n", i);
                    control2 = 1;
                }else{
                    printf("Primero debe crear la Lista\n\n");
                }

                break;

            case 3:
                if(control2){
                    auxMostrar = list;
                    int fin = l_longitud(list);
                    index = 1;

                    while( index < fin ) {
                        printf("Elemento %i: %i\n\n", index++, (int) l_recuperar(list, auxMostrar) );
                        auxMostrar = l_siguiente(list, auxMostrar);
                    }

                    printf("Elemento %i: %i\n\n", index, (int) l_recuperar(list, auxMostrar) );
                }else{
                    printf("Recuerde crear la lista e ingresar al menos un elemento \n\n");
                }

                break;
            default:
                if ( control1 ) l_destruir(&list, &fEliminarLista);
                condition=0;
                break;
        }

    }


    return 0;
}
