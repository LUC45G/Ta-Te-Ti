#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partida.h"

char GetChar(int x) {
    if(x == PART_JUGADOR_1) {
        return 'X';
    }
    if ( x == PART_JUGADOR_2 ) {
        return 'O';
    }

    return ' ';
}


void ImprimirTablero(tTablero t) {

    printf(" %c | %c | %c ", GetChar(t->grilla[0,0]), GetChar(t->grilla[0,1]), GetChar(t->grilla[0,2]));
    printf("---+---+---");
    printf(" %c | %c | %c ", GetChar(t->grilla[1,0]), GetChar(t->grilla[1,1]), GetChar(t->grilla[1,2]));
    printf("---+---+---");
    printf(" %c | %c | %c ", GetChar(t->grilla[2,0]), GetChar(t->grilla[2,1]), GetChar(t->grilla[2,2]));

}

int mainPartida() {
    tPartida partida = (tPartida) malloc(sizeof(struct partida));
    char* j1; char* j2;
    int opt;

    printf("Seleccione modo de juego: \n");
    printf("1) Humano vs Humano. \n");
    printf("2) Humano vs IA.\n\n");

    scanf("%d", &opt);

    printf("Ingrese nombre del jugador 1: ");
    scanf("%c", &j1);

    printf("Ingrese nombre del jugador 2: ");
    scanf("%c", &j2);

    struct tm *tm_struct = localtime(time(NULL));
    int hour = (tm_struct->tm_hour) + (tm_struct->tm_min) + (tm_struct->tm_sec);
    nueva_partida(&partida, opt, hour%2, j1, j2);


}

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre) {

    // Creo el tablero
    tTablero tab = (tTablero) malloc(sizeof(struct tablero));

    // Inicializo celdas vacias
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tab->grilla[i][j] = PART_SIN_MOVIMIENTO;

    // Leo los nombres
    char c;
    int i = 0;
    c = *j1_nombre;

    while(c != '\0') {
        ((*p)->nombre_jugador_1)[i++] = c;
        (j1_nombre)++;
    }

    i = 0; c = *j2_nombre;

    while(c!='\0') {
        ((*p)->nombre_jugador_2)[i++] = c;
        (j2_nombre)++;
    }

    //Seteo los porongos de la partida
    (*p)->estado           = PART_EN_JUEGO;
    (*p)->modo_partida     = modo_partida;
    (*p)->tablero          = tab;
    (*p)->turno_de         = comienza;
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y) {
    p->tablero->grilla[mov_x][mov_y] = p->turno_de;
    p->turno_de = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;
}

void finalizar_partida(tPartida * p) {

}
