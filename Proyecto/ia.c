#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "arbol.h"
#include "ia.h"
#include "partida.h"
#include <time.h>

// Prototipos de funciones auxiliares.
/**
    Procedimiento que libera un estado
*/
void fElimBusq(void * est){
    free(est);
    est=NULL;
}
/**
    Procedimiento que no elimina nada
*/
void f_no_eliminar(void * nada){}

static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);
int gano(tEstado e, int ficha);

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

    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){

        tNodo raiz = a_raiz(b->arbol_busqueda); // Raiz de la busqueda
        tLista movimientos = a_hijos(b->arbol_busqueda, raiz); // Movimientos sucesores

        tEstado estado_actual = (tEstado) a_recuperar(b->arbol_busqueda, raiz); // Estado de la raiz
        tPosicion fin = l_fin(movimientos); // Ultimo movimiento posible
        tPosicion cursor = l_primera(movimientos); // Cursor que marca la posicion actual
        tNodo hijoActual = NULL; // Hijo actual
        tEstado estadoHijo = NULL; // Estado del hijo actual
        tNodo mejor_sucesor = NULL; // Nodo que contiene al mejor movimiento sucesor

        int nuevo_valor = 0; // Valor de control
        int mejor_valor = IA_INFINITO_NEG; // Mejor valor posible, tambien para control

        while(cursor != fin) { // Recorre exhaustivamente
            hijoActual = l_recuperar(movimientos,cursor); // Guarda al hijo actual
            estadoHijo = a_recuperar(b->arbol_busqueda,hijoActual); // Pide su estado
            nuevo_valor = estadoHijo->utilidad; // Pide su utilidad

            if(mejor_valor < nuevo_valor) { // Si el valor actual es mejor que el mejor valor guardado previamente
                mejor_sucesor = l_recuperar(movimientos, cursor); // Se actualiza el nodo al mejor movimiento sucesor
                mejor_valor = nuevo_valor; // Se actualiza el mejor valor actual
            }
            cursor = l_siguiente(movimientos, cursor); // Sigue caminando por la lista
        }

        diferencia_estados(estado_actual, (tEstado) a_recuperar(b->arbol_busqueda, mejor_sucesor), x, y); // Pide las coordenadas
}

void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    ///Destruyo el arbol encontrado dentro de la estructura busqueda adversaria pasada por paramtero.
    a_destruir(&(*b)->arbol_busqueda,fElimBusq);
    ///Libero el espacio en memoria ocupado por la estructura busqueda adversaria pasada por parametro.
    free(*b);
    *b=NULL;
    free(b);
    b=NULL;
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    ///Guardo en una variable auxiliar el arbol encontrado en la estructura busqueda adversaria pasada por paramtero.
    tArbol a = b->arbol_busqueda;
    ///Guardo en una variable auxiliar la raiz de la variable arbol anteriormente guardada.
    tNodo r = a_raiz(a);
    ///Guardo en variables auxilares los enteros que identifican a jugadores encontrados en la estructura busqueda adversaria pasada por parametro.
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;
    ///Utilizo la funcion crear_sucesores_min_max con los parametro del arbol anteriormente guardado, su raiz, un entero numeros infinitos y las variables que identifican jugadores anteriormente guardadas.
    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){

    int util = valor_utilidad((tEstado)a_recuperar(a, n), jugador_max);
    //printf("%d", util);
    if ( util != IA_NO_TERMINO) {
        ((tEstado)a_recuperar(a, n))->utilidad = util;
        return;
    }

    tLista sucesores;
    tPosicion ultimoSucesor;
    tPosicion primerSucesor;
    tEstado sucesorActual, estado = a_recuperar(a, n);
    int mejor_valor, valor_actual;


    if (es_max) {
        mejor_valor = IA_INFINITO_NEG;
        sucesores = estados_sucesores(estado, jugador_max);
        ultimoSucesor = l_fin(sucesores);
        primerSucesor = l_primera(sucesores);

        while (primerSucesor != ultimoSucesor ) {

            sucesorActual = (tEstado) l_recuperar(sucesores, primerSucesor);
            sucesorActual->utilidad = valor_utilidad(sucesorActual, jugador_max);
            tNodo hijoActual = a_insertar(a, n, NULL, sucesorActual);
            crear_sucesores_min_max(a, hijoActual, !es_max, alpha, beta, jugador_max, jugador_min);
            primerSucesor = l_siguiente(sucesores, primerSucesor);
            valor_actual = sucesorActual->utilidad;

            if(mejor_valor < valor_actual) {
                mejor_valor = valor_actual;
            }

            if (alpha < mejor_valor) {
                alpha = mejor_valor;
            }

            if (beta <= alpha) {
                break;
            }
        }

        estado->utilidad = alpha;
    }
    else {
        mejor_valor = IA_INFINITO_POS;
        sucesores = estados_sucesores(estado, jugador_min);
        ultimoSucesor = l_fin(sucesores);
        primerSucesor = l_primera(sucesores);

        while (primerSucesor != ultimoSucesor ){

            sucesorActual = (tEstado) l_recuperar(sucesores, primerSucesor);
            sucesorActual->utilidad = valor_utilidad(sucesorActual, jugador_max);
            tNodo hijoActual = a_insertar(a, n, NULL, sucesorActual);
            crear_sucesores_min_max(a, hijoActual, !es_max, alpha, beta, jugador_max, jugador_min);
            primerSucesor = l_siguiente(sucesores, primerSucesor);
            valor_actual = sucesorActual->utilidad;

            if(mejor_valor > valor_actual) {
                mejor_valor = valor_actual;
            }

            if (mejor_valor < beta) {
                beta = mejor_valor;
            }

            if (beta <= alpha) {
                break;
            }
        }
        estado->utilidad = beta;
    }

    l_destruir(&sucesores,f_no_eliminar);
}
/**
    Calcula el valor utilidad de un estado de partida respecto del jugador max
    Retorna IA_GANA_MAX si gana max, IA_PIERDE_MAX si pierde y IA_EMPATA_MAX si hay empate.
*/
static int valor_utilidad(tEstado e, int jugador_max){

    int i, j, min, max;

    if( jugador_max == PART_JUGADOR_1 ) {
        min = PART_JUGADOR_2;
        max = PART_JUGADOR_1;
    }                           // Elige quien hace de min y quien de max
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
        if(e->grilla[0][i] == e->grilla[1][i] && e->grilla[0][i] == e->grilla[2][i]) {
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
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){

    tLista listaReturn;
    crear_lista(&listaReturn);
    int i, j;
    tEstado sigEstado;

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(e->grilla[i][j] == PART_SIN_MOVIMIENTO) {                                // Si el par [i, j] actual esta libre
                sigEstado = clonar_estado(e);                                           // Clono el estado
                sigEstado->grilla[i][j] = ficha_jugador;

                if ( rand() % 3 == 0) {                                                 // Si su puntero es divisible por 3
                    l_insertar(listaReturn, listaReturn, sigEstado);                    // Lo coloco al principio
                }
                else {                                                                  // Sino
                    l_insertar(listaReturn, l_ultima(listaReturn), sigEstado);             // Lo coloco al final
                }                                                                       // Esto le da la aleatoriedad
            }
        }
    }

    return listaReturn;
}

/**
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    tEstado newE = malloc(sizeof(struct estado));
    if(newE == NULL) { exit(IA_ERROR_MEMORIA); }
    int i, j;

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            newE->grilla[i][j] = e->grilla[i][j]; // Esto me genera dudas, porque en java funcionaria pero esto no es java
        }
    }

    newE->utilidad = e->utilidad;

    return newE;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    ///Declaro 3 variables enteras auxiliares.
    int i,j, hallado = 0;
    ///Recorro la grillas de las matrices encontradas en las estructuras estado pasadas por parametro hasta que se terminen o hasta que halle la posicion diferente entre dos estructuras estado.
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            ///Si encuentro la posicion que difiere actualizo los puntero a enteros pasados por parametro e indico que halle la diferencia.
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}
