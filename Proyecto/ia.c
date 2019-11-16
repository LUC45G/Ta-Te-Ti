#include <stdlib.h>
#include <stdio.h>
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

void f_no_eliminar(void * nada){}

static int max(int a, int b) {
    // Calcula el maximo entre a y b
    return (((a) > (b)) ? (a) : (b));
}

static int min(int a, int b) {
    // Calcula el minimo entre a y b
    return (((a) < (b)) ? (a) : (b));
}

void fEliminarBusqueda(tElemento e){
    tEstado aux=(tEstado)e;
    // liberador de estados
    free(aux);
}

void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la b�squeda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representar�n a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un �rbol para la b�squeda adversaria inicialmente vac�o.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la ra�z del �rbol de b�squeda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){

    // Declaracion de variables
    tNodo raiz                  = a_raiz(b->arbol_busqueda);
    tLista sucesores            = a_hijos(b->arbol_busqueda, raiz);
    int cantidad                = l_longitud(sucesores);
    tPosicion posListaSucesores = l_primera(sucesores);
    tNodo nodoSucesor           = l_recuperar(sucesores, posListaSucesores);
    tEstado estadoSucesor       = a_recuperar(b->arbol_busqueda, nodoSucesor);
    tEstado estadoInicial       = a_recuperar(b->arbol_busqueda, raiz);
    tEstado estadoGana          = NULL;
    tEstado estadoEmpata        = NULL;
    tEstado estadoPierde        = NULL;
    tEstado estadoReturn        = NULL;

    while(cantidad > 0 && estadoGana == NULL) { // Mientras haya estados que computar
        cantidad--;

        // Pide el valor de utilidad y lo pone en su "casillero" correspondiente
        if (estadoSucesor->utilidad == IA_GANA_MAX) {
            estadoGana   = estadoSucesor;
        }

        if (estadoSucesor->utilidad == IA_EMPATA_MAX) {
            estadoEmpata = estadoSucesor;
        }

        if (estadoSucesor->utilidad == IA_PIERDE_MAX) {
            estadoPierde = estadoSucesor;
        }

        // Si puede seguir avanzando, avanza
        if (cantidad > 0) {
            posListaSucesores = l_siguiente(sucesores, posListaSucesores);
            nodoSucesor       = l_recuperar(sucesores, posListaSucesores);
            estadoSucesor     = a_recuperar(b->arbol_busqueda, nodoSucesor);
        }
    }

    if (estadoGana != NULL) {
        // Si puede ganar, gana
        estadoReturn = estadoGana;
    }
    else if (estadoEmpata != NULL) {
        // Si no puede ganar pero puede empatar, empata
        estadoReturn = estadoEmpata;
    }
    else {
        // Si no puede nada, pierde
        estadoReturn = estadoPierde;
    }

    // Calcula el par x,y donde jugara la IA
    diferencia_estados(estadoInicial, estadoReturn, x, y);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    a_destruir(&(*b)->arbol_busqueda,&fEliminarBusqueda); // Destruye el arbol de busqueda
    free(*b); // Libera el struct busqueda
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecuci�n del algoritmo Min-Max para la generaci�n del �rbol de b�squeda adversaria, considerando como
estado inicial el estado de la partida almacenado en el �rbol almacenado en B.
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
- A referencia al �rbol de b�squeda adversaria.
- N referencia al nodo a partir del cual se construye el sub�rbol de b�squeda adversaria.
- ES_MAX indica si N representa un nodo MAX en el �rbol de b�squeda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el �rbol de b�squeda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/

static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min) { /*

    // Si es un nodo terminal
    if ( valor_utilidad(a_recuperar(a,n), (es_max)?jugador_max:jugador_min) != IA_NO_TERMINO) {
        // Calcula su valor de utilidad
        ((tEstado)a_recuperar(a, n))->utilidad = valor_utilidad((tEstado)a_recuperar(a, n), (es_max)?jugador_max:jugador_min);
        // y sale
        return;
    }

    // Si es un nodo a calcular, inicia
    // Creo las variables
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

            primerSucesor = l_siguiente(sucesores, primerSucesor);

        }


        ((tEstado)a_recuperar(a, n))->utilidad = alpha;
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

            primerSucesor = l_siguiente(sucesores, primerSucesor);
        }


        ((tEstado)a_recuperar(a, n))->utilidad = beta;
    }

    l_destruir(&sucesores,f_no_eliminar);*/

    ///Guardo en una variable auxiliar el elemento del nodo encontrado en el arbol y el nodo pasados por paramentro.
    ///Ejecuto la funcion minimax pasando por parametro el elemento del nodo anteriormente guardado,el entero que identifica al jugador y dos variables que identifican el valor de utilidad.
    ///Declaracion de variables.
    tEstado estado=n->elemento;
    tLista sucesores;
    tPosicion posActualSucesores;
    tPosicion finSucesores;
    tEstado sucesorAct;
    int encontro = 0;

    ///Si es un estado final devuelve la utilidad.
    estado->utilidad=valor_utilidad(estado,jugador_max);
    if(estado->utilidad==IA_NO_TERMINO){
        ///Si esJugadorMax !=0 significa que es un estado max.
        if(es_max){
            ///Inicializo las variables.
            sucesores = estados_sucesores(estado,jugador_max);
            posActualSucesores = l_primera(sucesores);
            finSucesores = l_fin(sucesores);
            ///Exploro la lista de estados hijos del estado actual.
            while(posActualSucesores!=finSucesores&&!encontro){
                ///Recupero el estado de la posicion de la lista de hijos.
                sucesorAct = (tEstado) l_recuperar(sucesores,posActualSucesores);
                ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado min.
                sucesorAct->utilidad=valor_utilidad(sucesorAct,jugador_max);
                tNodo hijoActual = a_insertar(a,n,NULL,sucesorAct);
                crear_sucesores_min_max(a,hijoActual,0,alpha,beta,jugador_max,jugador_min);//Este esta bien.Creo, le paso 0 para que vaya al else.
                ///Si la utilidad del hijo es mayor a la anteriormente calculada la reemplazo por el nuevo valor.
                tEstado estadoSucesor = hijoActual->elemento;
                //if(estadoSucesor->utilidad<mejorValorSucesores)
                //    mejorValorSucesores= caca->utilidad;
                ///Si alpha es menor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                if(alpha<estadoSucesor->utilidad)
                    alpha = estadoSucesor->utilidad;
                ///Si beta es menor  o igual a alpha, podo.
                if(beta<=alpha){
                    encontro = 1;
                }
                ///Actualizo la posicion en la lista de hijos.
                posActualSucesores = l_siguiente(sucesores,posActualSucesores);
            }
            estado->utilidad = alpha;
        }
            ///Si esJugadorMax =0 significa que es un estado min.
        else{
            ///Inicializo las variables.
            sucesores = estados_sucesores(estado,jugador_min);
            posActualSucesores = l_primera(sucesores);
            finSucesores = l_fin(sucesores);
            ///Exploro la lista de estados hijos del estado actual.
            while(posActualSucesores!=finSucesores&&!encontro){
                ///Recupero el estado de la posicion de la lista de hijos.
                sucesorAct = (tEstado) l_recuperar(sucesores,posActualSucesores);
                ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado max.
                tNodo hijoActual =a_insertar(a,n,NULL,sucesorAct);
                sucesorAct->utilidad=valor_utilidad(sucesorAct,jugador_max);
                crear_sucesores_min_max(a,hijoActual,1,alpha,beta,jugador_max,jugador_min);//Este le paso para que en el sig vaya al if y no al else
                ///Si la utilidad del hijo es menor a la anteriormente calculada la reemplazo por el nuevo valor.
                tEstado estadoSucesor=hijoActual->elemento;
                ///Si beta es mayor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                if(estadoSucesor->utilidad<beta)
                    beta = estadoSucesor->utilidad;
                ///Si beta es menor  o igual a alpha, podo.
                if(beta<=alpha){
                    encontro = 1;
                }
                ///Actualizo la posicion en la lista de hijos.
                posActualSucesores = l_siguiente(sucesores,posActualSucesores);
            }
            estado->utilidad = beta;
        }
        l_destruir(&sucesores,f_no_eliminar);
    }
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX gan� la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empat� la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdi� la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max) {

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
Un estado sucesor corresponde a la clonaci�n del estado E, junto con la incorporaci�n de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posici�n que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocaci�n de la funci�n
estados_sucesores(estado, ficha) retornar�a dos listas L1 y L2 tal que:
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
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonaci�n del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e) {
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
Se asume que entre ambos existe s�lo una posici�n en el que la ficha del estado anterior y nuevo difiere.
La posici�n en la que los estados difiere, es retornada en los par�metros *X e *Y.
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
