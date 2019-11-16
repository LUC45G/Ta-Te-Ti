#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre) {

    *p = (tPartida) malloc(sizeof(struct partida));

    if((*p)==NULL)
        exit(PART_ERROR_MEMORIA);


    // Creo el tablero
    tTablero tab = (tTablero) malloc(sizeof(struct tablero));

    if(tab == NULL)
        exit(PART_ERROR_MEMORIA);


    // Inicializo celdas vacias
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) {
            tab->grilla[i][j] = PART_SIN_MOVIMIENTO;
        }
    }


    // Leo los nombres
    int i = 0;

    for(i = 0; i < 50; i++) {
        (*p)->nombre_jugador_1[i] = '\0';
        (*p)->nombre_jugador_2[i] = '\0';
    }

    while(j1_nombre[i] != '\n' && j1_nombre[i] != '\0') {
        (*p)->nombre_jugador_1[i] = j1_nombre[i];
        i++;
    }

    i = 0;

    while(j2_nombre[i] != '\n' && j2_nombre[i] != '\0') {
        (*p)->nombre_jugador_2[i] = j2_nombre[i];
        i++;
    }

    //Seteo los datos de la partida
    (*p)->estado           = PART_EN_JUEGO;
    (*p)->modo_partida     = modo_partida;
    (*p)->tablero          = tab;
    (*p)->turno_de         = (comienza==1)?PART_JUGADOR_1:PART_JUGADOR_2;
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y) {

    if (mov_x < 0 || mov_x > 2 ||
        mov_y < 0 || mov_y > 2  ) {
        return PART_MOVIMIENTO_ERROR;
    }

    // Si la casilla esta ocupada, avisa
    if(p->tablero->grilla[mov_x][mov_y] != PART_SIN_MOVIMIENTO) {
        return PART_MOVIMIENTO_ERROR;
    }

    // Caso contrario, juega el movimiento
    p->tablero->grilla[mov_x][mov_y] = p->turno_de;
    p->turno_de = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    return PART_MOVIMIENTO_OK;
}

void finalizar_partida(tPartida * p) {
    while(*p != NULL) {
        free((*p)->tablero);
        free(p);
    }
}
