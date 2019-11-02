#include <stdlib.h>

#include "lista.h"
#include "arbol.h"
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);

static int max(a,b) {
    return (((a) > (b)) ? (a) : (b));
}

static int min(a,b) {
    return (((a) < (b)) ? (a) : (b));
}

void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la búsqueda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representarán a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;
    //printf("Llego-1   ");
    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));
    //printf("Llego-2   ");
    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);
    //printf("Llego 1");
    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
    //printf("Llego2");
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){
    printf("PROXIMO MOVIMIENTO\n");
    tNodo raiz                  = a_raiz(b->arbol_busqueda);
    tLista sucesores            = a_hijos(b->arbol_busqueda, raiz);
    printf("%i\n",sucesores == NULL);
    printf("Lleg0\n");
    int cantidad                = l_longitud(sucesores);
    printf("Lleg1\n");
    tPosicion posListaSucesores = l_primera(sucesores);
    tNodo nodoSucesor           = l_recuperar(sucesores, posListaSucesores);
    tEstado estadoSucesor       = a_recuperar(b->arbol_busqueda, nodoSucesor);
    tEstado estadoInicial       = a_recuperar(b->arbol_busqueda, raiz);
    tEstado estadoGana          = NULL;
    tEstado estadoEmpata        = NULL;
    tEstado estadoPierde        = NULL;
    tEstado estadoReturn        = NULL;

    while(cantidad > 0 && estadoGana == NULL) {
        cantidad--;

        if (estadoSucesor->utilidad == IA_GANA_MAX) {
            estadoGana   = estadoSucesor;
        }

        if (estadoSucesor->utilidad == IA_EMPATA_MAX) {
            estadoEmpata = estadoSucesor;
        }

        if (estadoSucesor->utilidad == IA_PIERDE_MAX) {
            estadoPierde = estadoSucesor;
        }

        if (cantidad > 0) {
            tPosicion posListaSucesores = l_siguiente(sucesores, posListaSucesores);
            tNodo nodoSucesor           = l_recuperar(sucesores, posListaSucesores);
            tEstado estadoSucesor       = a_recuperar(b->arbol_busqueda, nodoSucesor);
        }
    }
    if (estadoGana != NULL) {
        estadoReturn = estadoGana;
    }
    else if (estadoEmpata != NULL) {
        estadoReturn = estadoEmpata;
    }
    else {
        estadoReturn = estadoPierde;
    }
    printf("PROXIMO MOVIMIENTO LLEGO");
    diferencia_estados(estadoInicial, estadoReturn, x, y);


}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    free(b);
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;

    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/

static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min) {
    if ( valor_utilidad(a_recuperar(a,n), (es_max)?jugador_max:jugador_min) != IA_NO_TERMINO) {
        ((tEstado)a_recuperar(a, n))->utilidad = valor_utilidad((tEstado)a_recuperar(a, n), (es_max)?jugador_max:jugador_min);
        return;
    }

    tLista sucesores;
    tPosicion ultimoSucesor;
    tPosicion primerSucesor;

    int mejor_valor_sucesores, valorSucesor;

    if (es_max) {
        mejor_valor_sucesores = IA_INFINITO_NEG;
        sucesores = estados_sucesores(a_recuperar(a, n), jugador_max);
        ultimoSucesor = l_fin(sucesores);
        primerSucesor = l_primera(sucesores);

        while (primerSucesor != ultimoSucesor ) {

            crear_sucesores_min_max(a, n, !es_max, alpha, beta, jugador_max, jugador_min);
            valorSucesor = ((tEstado)a_recuperar(a, n))->utilidad;

            mejor_valor_sucesores = max(mejor_valor_sucesores,valorSucesor);
            alpha = max(alpha, mejor_valor_sucesores);

            if (beta <= alpha) {
                break;
            }

        }
    }
    else {
        mejor_valor_sucesores = IA_INFINITO_POS;
        sucesores = estados_sucesores(a_recuperar(a, n), jugador_min);
        ultimoSucesor = l_fin(sucesores);
        primerSucesor = l_primera(sucesores);

        while (primerSucesor != ultimoSucesor ){

            crear_sucesores_min_max(a, n, !es_max, alpha, beta, jugador_max, jugador_min);
            valorSucesor = ((tEstado)a_recuperar(a, n))->utilidad;

            mejor_valor_sucesores = min(mejor_valor_sucesores,valorSucesor);
            alpha = min(alpha, mejor_valor_sucesores);

            if (beta >= alpha) {
                break;
            }
        }

    }



}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max) {

    int i, j, min, max;

    if( jugador_max == PART_JUGADOR_1 ) {
        min = PART_JUGADOR_2;
        max = PART_JUGADOR_1;
    }
    else {
        min = PART_JUGADOR_1;
        max = PART_JUGADOR_2;
    }

    // Chequeo por fila
    for(i = 0; i < 3; ++i) {
        if(e->grilla[i][0] == e->grilla[i][1] && e->grilla[i][0] == e->grilla[i][2]) {
            if(e->grilla[i][0] == max) {
                return IA_GANA_MAX;
            }
            if(e->grilla[i][0] == min) {
                return IA_PIERDE_MAX;
            }
        }
    }

    // Chequeo por columna
    for(i = 0; i < 3; ++i) {
        if(e->grilla[0][i] == e->grilla[i][1] && e->grilla[1][i] == e->grilla[2][i]) {
            if(e->grilla[0][i] == max) {
                return IA_GANA_MAX;
            }
            if(e->grilla[0][i] == min) {
                return IA_PIERDE_MAX;
            }
        }
    }

    // Chequeo por diagonales
    if(e->grilla[0][2] == e->grilla[1][1] && e->grilla[0][2] == e->grilla[2][0]) {
        if(e->grilla[0][2] == max) {
            return IA_GANA_MAX;
        }
        if(e->grilla[0][2] == min) {
            return IA_PIERDE_MAX;
        }
    }

    if(e->grilla[0][0] == e->grilla[1][1] && e->grilla[0][0] == e->grilla[2][2]) {
        if(e->grilla[0][0] == max) {
            return IA_GANA_MAX;
        }
        if(e->grilla[0][0] == min) {
            return IA_PIERDE_MAX;
        }
    }

    // Si no gano nadie, se fija si se puede seguir jugando
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(e->grilla[i][j] == PART_SIN_MOVIMIENTO) {
                return IA_NO_TERMINO;
            }
        }
    }

    // Si no puede seguir jugando y nadie gano, devuelve empate
    return IA_EMPATA_MAX;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador) {

    tLista listaReturn;
    crear_lista(&listaReturn);
    int i, j;
    tEstado sigEstado;

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(e->grilla[i][j] == PART_SIN_MOVIMIENTO) {                                // Si el par [i, j] actual esta libre
                sigEstado = clonar_estado(e);                                           // Clono el estado
                sigEstado->grilla[i][j] = ficha_jugador;                                // Agrego la ficha pertinente
                sigEstado->utilidad     = valor_utilidad(sigEstado, ficha_jugador);     // Calculo su valor de utilidad

                if ((int) &sigEstado % 3 == 0) {                                              // Si su puntero es divisible por 3
                    l_insertar(listaReturn, listaReturn, sigEstado);                    // Lo coloco al principio
                }
                else {                                                                  // Sino
                    l_insertar(listaReturn, l_fin(listaReturn), sigEstado);             // Lo coloco al final
                }                                                                       // Esto le da la aleatoriedad
            }
        }
    }

    return listaReturn;

}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e) {
    tEstado newE = malloc(sizeof(struct estado));
    int i, j;

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            newE->grilla[i][j] = e->grilla[i][j]; // Esto me genera dudas, porque en java funcionaria pero esto no es java
        }
    }

    return newE;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}
