
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"


// void fEliminar();

int main() {
    tArbol arbol;
    tNodo raiz = malloc(sizeof(tNodo));
    int condition = 1, control2 = 0, control1 = 0, index = 0, padre = 0, hermano = 0, aAgregar = 0, i = 0, insertado = 0;

    printf("Recuerde crear el arbol antes de utilizar las operaciones.\n\n");




    while(condition) {
        printf("Ingrese numero : \n1->Crear arbol vac�o \n2->Crear raiz  \n3->Agregar elemento \n4->Mostrar Arbol \n5-> Falta algo?  \n0->Salir\n\n");
        scanf("%i", &condition);

        switch(condition) {
            case 1:

                crear_arbol(&arbol);
                printf("\nArbol creado, puede crear su raiz.\n\n");
                control1 = 1;
                control2 = 0;
                break;

            case 2:

                if (control1){ //SI SE CRE� EL ARBOL:
                    printf("Ingrese el valor a agregar: \n");
                    scanf("%d", &i);
                    crear_raiz(arbol,i);
                    raiz = a_raiz(arbol);
                    printf("\nElemento %i agregado con exito.\n\n", i);
                    printf("\nRaiz: %i\n\n", a_recuperar(arbol, raiz));
                    control2 = 1;
                }else{
                    printf("Primero debe crear el arbol.\n\n");
                }

                break;

            case 3:
                //-1073741819
                printf("\n\n");

                if(control2){

                    printf("Padre de donde insertar\n");
                    scanf("%i", &padre);
                    tNodo p = buscarNodo(arbol, raiz, padre);

                    if(p == NULL){
                        printf("\n\nNo se encontro a %i como padre.\n\n", padre);
                        break;
                    }

                    if( l_primera(a_hijos(arbol, p)) == NULL  ) {
                        printf("Que queres agregar\n");
                        scanf("%i", &aAgregar);

                        a_insertar(arbol, raiz, NULL, aAgregar);
                        printf("\nElemento %i agregado con exito1.\n\n", a_recuperar(arbol, l_recuperar(arbol, l_primera(a_hijos(arbol, raiz)))));
                        insertado = 1;
                        break;
                    }



                    printf("Ahora el hermano\n");
                    scanf("%i", &hermano);
                    printf("Que queres agregar\n");
                    scanf("%i", &aAgregar);

                    printf("\n\nUsted quiere agregar al nodo %i como hijo de %i y hermano de %i\n\n", aAgregar, padre, hermano);

                    tNodo h = buscarNodo(arbol, raiz, hermano);


                    if(h == NULL){
                        printf("\n\nNo se encontro a %i como hermano.\n\n", hermano);
                        break;
                    }

                    a_insertar(arbol, p, h, aAgregar);
                    printf("\nElemento %i agregado con exito2.\n\n", a_recuperar(arbol, buscarNodo(arbol, raiz, aAgregar)));

                } else{
                    printf("Recuerde crear el arbol y su raiz.\n\n");
                }

                break;
            case 4:
                if(!control2) {
                    printf("Recuerde crear el arbol y al menos su raiz.");
                    break;
                }

                MostrarArbol(arbol, raiz);
                break;
            case 5:
                printf("Ingrese numero que ser� raiz del nuevo sub-arbol\n");
                int raizSA;
                scanf("%i", &raizSA);
                tArbol subArbol;
                crear_arbol(&subArbol);
                a_sub_arbol(arbol,buscarNodo(arbol,raiz,raizSA),&subArbol);

                printf("Operaci�n realizada con �xito\n\n");

                MostrarArbol(subArbol, a_raiz(subArbol));
                printf("\n\n");

                break;
            default:
                condition=0;
                break;
        }

    }


    return 0;
}

/*void fEliminar(tElemento e) {
    free(e);
    //void* x=(void*)0;

    //return x;
}*/
