
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"


// void fEliminar();

int main() {
    tArbol arbol;
    tNodo raiz = malloc(sizeof(tNodo));
    int condition = 1, control2 = 0, control1 = 0, index = 0, padre = 0, hermano = 0, aAgregar = 0, i = 0, insertado = 0;

    printf("Recuerde crear la lista antes de utilizar las operaciones Agregar y Mostrar.\n\n");




    while(condition) {
        printf("Ingrese numero : \n1->Crear arbol vacío \n2->Crear raiz  \n3->Agregar elemento \n4->Eliminar elemento \n5-> Falta algo?  \n0->Salir\n\n");
        scanf("%i", &condition);

        switch(condition) {
            case 1:
                system("cls");  //limpia la pantalla
                crear_arbol(&arbol);
                printf("\nLista creada con exito\n\n");
                control1 = 1;
                control2 = 0;
                break;

            case 2:
                system("cls");
                if (control1){ //SI SE CREÓ EL ARBOL:
                    printf("Ingrese el valor a agregar: \n");
                    scanf("%d", &i);
                    crear_raiz(arbol,&i);
                    raiz = a_raiz(arbol);
                    printf("\nElemento %i agregado con exito\n\n", i);
                    control2 = 1;
                }else{
                    printf("Primero debe crear la Lista\n\n");
                }

                break;

            case 3:
                system("cls");
                if(control2){
                    if(!insertado) {
                        printf("Que queres agregar\n");
                        scanf("%i", &aAgregar);

                        a_insertar(arbol, raiz, NULL, &aAgregar);
                        insertado = 1;
                        break;
                    }

                    printf("Padre de donde insertar\n");
                    scanf("%i", &padre);
                    printf("Ahora el hermano\n");
                    scanf("%i", &hermano);
                    printf("Que queres agregar\n");
                    scanf("%i", &aAgregar);

                    tNodo p = buscarNodo(arbol, raiz, &padre);
                    tNodo h = buscarNodo(arbol, raiz, &hermano);

                    if(p == NULL || h == NULL){
                        printf("Choto, le erraste");
                        break;
                    }

                    a_insertar(arbol, p, h, aAgregar);



                }else{
                    printf("Recuerde crear la lista e ingresar al menos un elemento \n\n");
                }

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
