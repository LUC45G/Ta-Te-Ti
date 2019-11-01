#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ia.h"
#include "partida.h"

char GetChar(int *x) {
    if(*x == PART_JUGADOR_1) {
        return 'X';
    }
    if (*x == PART_JUGADOR_2 ) {
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

int main() {
    tPartida partida = (tPartida) malloc(sizeof(struct partida));
    char* j1 = malloc(300);
    char* j2 = malloc(300);
    char* aux = malloc(21);
    int opt;

    printf("Seleccione modo de juego: \n");
    printf("1) Humano vs Humano. \n");
    printf("2) Humano vs IA.\n\n");

    scanf("%d", &opt);

    printf("Ingrese nombre del jugador 1: ");
    scanf("%c", &aux);
    scanf("%s", &j1);

    printf("Ingrese nombre del jugador 2: ");
    scanf("%c", &aux);
    scanf("%s", &j2);

    printf("llego 1");
    nueva_partida(&partida, opt, 1, j1, j2);


}

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre) {

    int u = 0;

    printf("llego %i", ++u);
    // Creo el tablero
    tTablero tab = (tTablero) malloc(sizeof(struct tablero));
    tBusquedaAdversaria b;

    printf("llego %i", ++u);

    // Inicializo celdas vacias
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) {
            tab->grilla[i][j] = PART_SIN_MOVIMIENTO;
        }
    }

    printf("llego %i", ++u);

    // Leo los nombres
    char c;
    int i = 0;
    printf("llego %i", ++u);
    c = (*j1_nombre);

    printf("llego %i", ++u);

    while(c != '\0') {
        ((*p)->nombre_jugador_1)[i++] = c;
        (j1_nombre)++;
    }

    i = 0; c = *j2_nombre;

    while(c!='\0') {
        ((*p)->nombre_jugador_2)[i++] = c;
        (j2_nombre)++;
    }

    printf("llego %i", ++u);

    //Seteo los porongos de la partida
    (*p)->estado           = PART_EN_JUEGO;
    (*p)->modo_partida     = modo_partida;
    (*p)->tablero          = tab;
    (*p)->turno_de         = comienza;

    printf("llego %i", ++u);

    if(modo_partida == 2) {
        crear_busqueda_adversaria(&b, p);
    }
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y) {
    p->tablero->grilla[mov_x][mov_y] = p->turno_de;
    p->turno_de = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;
}

void finalizar_partida(tPartida * p) {

}
