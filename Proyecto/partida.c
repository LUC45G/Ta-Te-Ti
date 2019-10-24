#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partida.h"


int mainPartida() {
    tPartida partida = malloc(sizeof(tPartida));
    char* j1; char* j2;
    int opt;

    printf("Seleccione modo de juego: \n");
    printf("1) Humano vs Humano. \n");
    printf("2) Humano vs IA.");

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
    tTablero tab = malloc(sizeof(tTablero));
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

    (*p)->estado           = PART_EN_JUEGO;
    (*p)->modo_partida     = modo_partida;
    (*p)->tablero          = tab;
    (*p)->turno_de         = comienza;
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y) {

}

void finalizar_partida(tPartida * p) {

}
