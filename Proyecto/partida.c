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
                printf("------------GANA EN 1-------------");
                return PART_GANA_JUGADOR_1;
            }
            if(tab->grilla[i][0] == PART_JUGADOR_2) {
                printf("------------GANA EN 1-------------");
                return PART_GANA_JUGADOR_2;
            }
        }
    }

    // Chequeo por columna
    for(i = 0; i < 3; ++i) {
        if(tab->grilla[0][i] == tab->grilla[1][i] && tab->grilla[0][i] == tab->grilla[2][i]) {
            if(tab->grilla[0][i] == PART_JUGADOR_1) {
                    printf("------------GANA EN 2-------------");
                return PART_GANA_JUGADOR_1;
            }
            if(tab->grilla[0][i] == PART_JUGADOR_2) {
                printf("------------GANA EN 2-------------");
                return PART_GANA_JUGADOR_2;
            }
        }
    }

    // Chequeo por diagonales
    if(tab->grilla[0][2] == tab->grilla[1][1] && tab->grilla[0][2] == tab->grilla[2][0]) {
        if(tab->grilla[0][2] == PART_JUGADOR_1) {
                printf("------------GANA EN 3-------------");
            return PART_GANA_JUGADOR_1;
        }
        if(tab->grilla[0][2] == PART_JUGADOR_2) {
            printf("------------GANA EN 3-------------");
            return PART_GANA_JUGADOR_2;
        }
    }

    if(tab->grilla[0][0] == tab->grilla[1][1] && tab->grilla[0][0] == tab->grilla[2][2]) {
        if(tab->grilla[0][0] == PART_JUGADOR_1) {
                printf("------------GANA EN 4-------------");
            return PART_GANA_JUGADOR_1;
        }
        if(tab->grilla[0][0] == PART_JUGADOR_2) {
            printf("------------GANA EN 4-------------");
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

int PedirYRealizarMovimientoJugador(tPartida partida) {
    int x, y, control;

    ImprimirTablero(partida->tablero);
    control = 0;
    printf("\nTurno de %s\n", (partida->turno_de == PART_JUGADOR_1) ? partida->nombre_jugador_1 : partida->nombre_jugador_2);

    do {
        printf("Ingrese su movimiento\n");
        printf("x: "); scanf("%i", &x);
        printf("y: "); scanf("%i", &y);
        control = ((x>=0) && (x<3)) && ((y>=0) && (y<3));
    } while ( !control );

    return nuevo_movimiento(partida,x,y);

}

int RealizarMovimientoIA(tPartida partida) {
    tBusquedaAdversaria b;
    int x, y, auxRet;

    printf("Creo la busqueda\n");
    crear_busqueda_adversaria(&b,partida);
    printf("Pido el siguiente movimiento\n");// FLAG
    proximo_movimiento(b,&x,&y);
    auxRet = nuevo_movimiento(partida,x,y);

    destruir_busqueda_adversaria(&b);
    return auxRet;
}


int main() {
    tPartida partida;
    char* j1[50];
    char* j2[50];
    char* aux;
    int opt, empieza, state = PART_EN_JUEGO;

    /*PIDO LOS DATOS DE LA PARTIDA*/

    while(opt != 1 && opt != 2) {
        printf("Seleccione modo de juego: \n");
        printf("1) Humano vs Humano. \n");
        printf("2) Humano vs IA.\n\n");

        printf("Ingrese (3) para ver las reglas\n\n");

        scanf("%d", &opt);

        if(opt == 3) {
            printf("\n\n\n\n\n");
            printf("\t\t\t  Bienvenidx al TaTeTi\n");
            printf("Primero seleccione un modo de juego: \n");
            printf("Humano vs Humano: Permite jugar el clasico TaTeTi uno contra uno\n");
            printf("Humano vs IA: Permite desafiar a una mega avanzada inteligencia artificial\n");
            printf("\nLas celdas del tablero son:\n\n");

            printf("\t\t\t [0, 0] | [0, 1] | [0, 2] \n");
            printf("\t\t\t--------+--------+--------\n");
            printf("\t\t\t [1, 0] | [1, 1] | [1, 2] \n");
            printf("\t\t\t--------+--------+--------\n");
            printf("\t\t\t [2, 0] | [2, 1] | [2, 2] \n");

            printf("\nSeleccione un par [x, y] para colocar la ficha deseada y ceda el turno al siguiente jugador.\n\n");

            printf("\t\t\t\tGL HF!\n\n\n\n\n");
        }
    }

    printf("Ingrese nombre del jugador 1: ");
    scanf("%s", &j1);

    printf("Ingrese nombre del jugador 2: ");
    scanf("%s", &j2);

    printf("Empieza jugador 1 o 2? ");
    scanf("%i", &empieza);

    nueva_partida(&partida, opt, empieza, j1, j2);

    /*JUEGO*/


    switch(opt) {

        case 1:
            /*MODO JUGADOR VS JUGADOR*/
            // Mientras el movimiento sea valido
            while(state == PART_EN_JUEGO || state == PART_MOVIMIENTO_ERROR) {
                state = PedirYRealizarMovimientoJugador(partida);
            }
            break;

        case 2:
            /*MODO JUGADOR VS PC*/
            while(state == PART_EN_JUEGO || state == PART_MOVIMIENTO_ERROR) {
                if(partida->turno_de == PART_JUGADOR_1) {
                    state = PedirYRealizarMovimientoJugador(partida);
                }
                else {
                    state = RealizarMovimientoIA(partida);
                }
            }
            break;
        default:
            exit(0);

    }

    if(state == PART_EMPATE) {
            printf("\n\n\t\t\tEMPATE\n\n");
    }
    else {
        ImprimirTablero(partida->tablero);
        printf("\n\n\t\t\tGANADOR: %s\n\n", (state == PART_GANA_JUGADOR_1) ? partida->nombre_jugador_2 : partida->nombre_jugador_1);
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
