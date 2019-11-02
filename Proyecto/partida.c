#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ia.h"
#include "partida.h"

char GetChar(int* x) {
    if(x == PART_JUGADOR_1) {
        return 'X';
    }
    if(x == PART_JUGADOR_2 ) {
        return 'O';
    }

    return ' ';
}


void ImprimirTablero(tTablero t) {

    printf("\n\n\n\n\n");

    printf("\t\t\t %c | %c | %c \n", GetChar(t->grilla[0][0]), GetChar(t->grilla[0][1]), GetChar(t->grilla[0][2]));
    printf("\t\t\t---+---+---\n");
    printf("\t\t\t %c | %c | %c \n", GetChar(t->grilla[1][0]), GetChar(t->grilla[1][1]), GetChar(t->grilla[1][2]));
    printf("\t\t\t---+---+---\n");
    printf("\t\t\t %c | %c | %c \n", GetChar(t->grilla[2][0]), GetChar(t->grilla[2][1]), GetChar(t->grilla[2][2]));

    printf("\n\n\n");

}

int ControlVictoria(tTablero tab) {

    int i, j;

    // Chequeo por fila
    for(i = 0; i < 3; ++i) {
        if(tab->grilla[i][0] == tab->grilla[i][1] && tab->grilla[i][0] == tab->grilla[i][2]) {
            if(tab->grilla[i][0] == PART_JUGADOR_1) {
                return PART_GANA_JUGADOR_1;
            }
            if(tab->grilla[i][0] == PART_JUGADOR_2) {
                return PART_GANA_JUGADOR_2;
            }
        }
    }

    // Chequeo por columna
    for(i = 0; i < 3; ++i) {
        if(tab->grilla[0][i] == tab->grilla[i][1] && tab->grilla[1][i] == tab->grilla[2][i]) {
            if(tab->grilla[0][i] == PART_JUGADOR_1) {
                return PART_GANA_JUGADOR_1;
            }
            if(tab->grilla[0][i] == PART_JUGADOR_2) {
                return PART_GANA_JUGADOR_2;
            }
        }
    }

    // Chequeo por diagonales
    if(tab->grilla[0][2] == tab->grilla[1][1] && tab->grilla[0][2] == tab->grilla[2][0]) {
        if(tab->grilla[0][2] == PART_JUGADOR_1) {
            return PART_GANA_JUGADOR_1;
        }
        if(tab->grilla[0][2] == PART_JUGADOR_2) {
            return PART_GANA_JUGADOR_2;
        }
    }

    if(tab->grilla[0][0] == tab->grilla[1][1] && tab->grilla[0][0] == tab->grilla[2][2]) {
        if(tab->grilla[0][0] == PART_JUGADOR_1) {
            return PART_GANA_JUGADOR_1;
        }
        if(tab->grilla[0][0] == PART_JUGADOR_2) {
            return PART_GANA_JUGADOR_2;
        }
    }

    // Si no gano nadie, se fija si se puede seguir jugando
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(tab->grilla[i][j] == PART_SIN_MOVIMIENTO) {
                return PART_EN_JUEGO;
            }
        }
    }

    // Si no puede seguir jugando y nadie gano, devuelve empate
    return PART_EMPATE;
}


int main() {
    tPartida partida;
    char* j1[50];
    char* j2[50];
    char* aux;
    int opt, empieza, x, y, control, state;
    tBusquedaAdversaria b;

    /*PIDO LOS DATOS DE LA PARTIDA*/

    printf("Seleccione modo de juego: \n");
    printf("1) Humano vs Humano. \n");
    printf("2) Humano vs IA.\n\n");

    printf("Ingrese (3) para ver las reglas\n\n");

    scanf("%d", &opt);

    printf("Ingrese nombre del jugador 1: ");
    scanf("%s", &j1);

    printf("Ingrese nombre del jugador 2: ");
    scanf("%s", &j2);

    printf("Empieza jugador 1 o 2? ");
    scanf("%i", &empieza);

    nueva_partida(&partida, opt, empieza, j1, j2);

    /*JUEGO*/

    state = PART_EN_JUEGO;

    switch(opt) {

        case 1:
            /*MODO JUGADOR VS JUGADOR*/
            // Mientras el movimiento sea valido
            while(state == PART_EN_JUEGO || state == PART_MOVIMIENTO_ERROR) {
                ImprimirTablero(partida->tablero);
                control = 0;
                printf("\nTurno de %s\n", (partida->turno_de == PART_JUGADOR_1) ? partida->nombre_jugador_1 : partida->nombre_jugador_2);

                do {
                    printf("Ingrese su movimiento\n");
                    printf("x: "); scanf("%i", &x);
                    printf("y: "); scanf("%i", &y);
                    control = ((x>=0) && (x<3)) && ((y>=0) && (y<3));
                } while ( !control );

                state = nuevo_movimiento(partida,y,x);


            }
            break;

        case 2:
            /*MODO JUGADOR VS PC*/
            break;
        case 3:
            /*IMPRIMIR REGLAS*/
            break;
        default:
            exit(0);

    }

    if(partida->estado == PART_EMPATE) {
            printf("\n\n\t\t\tEMPATE\n\n");
    }
    else {
        printf("\n\n\t\t\tGANADOR: %s\n\n", (partida->estado == PART_GANA_JUGADOR_1) ? partida->nombre_jugador_1 : partida->nombre_jugador_2);
    }




}

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

    while(j1_nombre[i] != '\n' && j1_nombre[i] != '\0') {
        (*p)->nombre_jugador_1[i] = j1_nombre[i];
        i++;
    }

    i = 0;

    while(j2_nombre[i] != '\n' && j2_nombre[i] != '\0') {
        (*p)->nombre_jugador_2[i] = j2_nombre[i];
        i++;
    }

    //Seteo los porongos de la partida
    (*p)->estado           = PART_EN_JUEGO;
    (*p)->modo_partida     = modo_partida;
    (*p)->tablero          = tab;
    (*p)->turno_de         = (comienza==1)?PART_JUGADOR_1:PART_JUGADOR_2;
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y) {

    if(p->tablero->grilla[mov_x][mov_y] != PART_SIN_MOVIMIENTO) {
        return PART_MOVIMIENTO_ERROR;
    }

    p->tablero->grilla[mov_x][mov_y] = p->turno_de;
    p->turno_de = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    return ControlVictoria(p->tablero);
}

void finalizar_partida(tPartida * p) {

}
