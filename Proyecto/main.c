#include <stdio.h>
#include <stdlib.h>
#include "ia.h"
#include "partida.h"

char GetChar(int x) {
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
//
//int ControlVictoria(tTablero tab) {
//
//    int i, j;
//
//    // Chequeo por fila
//    for(i = 0; i < 3; ++i) {
//        if(tab->grilla[i][0] == tab->grilla[i][1] && tab->grilla[i][0] == tab->grilla[i][2]) {
//            if(tab->grilla[i][0] == PART_JUGADOR_1) {
//                return PART_GANA_JUGADOR_1;
//            }
//            if(tab->grilla[i][0] == PART_JUGADOR_2) {
//                return PART_GANA_JUGADOR_2;
//            }
//        }
//    }
//
//    // Chequeo por columna
//    for(i = 0; i < 3; ++i) {
//        if(tab->grilla[0][i] == tab->grilla[1][i] && tab->grilla[0][i] == tab->grilla[2][i]) {
//            if(tab->grilla[0][i] == PART_JUGADOR_1) {
//                return PART_GANA_JUGADOR_1;
//            }
//            if(tab->grilla[0][i] == PART_JUGADOR_2) {
//                return PART_GANA_JUGADOR_2;
//            }
//        }
//    }
//
//    // Chequeo por diagonales
//    if(tab->grilla[0][2] == tab->grilla[1][1] && tab->grilla[0][2] == tab->grilla[2][0]) {
//        if(tab->grilla[0][2] == PART_JUGADOR_1) {
//            return PART_GANA_JUGADOR_1;
//        }
//        if(tab->grilla[0][2] == PART_JUGADOR_2) {
//            return PART_GANA_JUGADOR_2;
//        }
//    }
//
//    if(tab->grilla[0][0] == tab->grilla[1][1] && tab->grilla[0][0] == tab->grilla[2][2]) {
//        if(tab->grilla[0][0] == PART_JUGADOR_1) {
//            return PART_GANA_JUGADOR_1;
//        }
//        if(tab->grilla[0][0] == PART_JUGADOR_2) {
//            return PART_GANA_JUGADOR_2;
//        }
//    }
//
//    // Si no gano nadie, se fija si se puede seguir jugando
//    for(i = 0; i < 3; ++i) {
//        for(j = 0; j < 3; ++j) {
//            if(tab->grilla[i][j] == PART_SIN_MOVIMIENTO) {
//                return PART_EN_JUEGO;
//            }
//        }
//    }
//
//    // Si no puede seguir jugando y nadie gano, devuelve empate
//    return PART_EMPATE;
//}

int PedirYRealizarMovimientoJugador(tPartida partida) {
    int x, y, control;
    // Imprime el tablero
    ImprimirTablero(partida->tablero);
    control = 0;
    // Avisa de quien es el turno
    printf("\nTurno de %s\n", (partida->turno_de == PART_JUGADOR_1) ? partida->nombre_jugador_1 : partida->nombre_jugador_2);

    do {
        printf("Ingrese su movimiento\n");
        printf("x: "); scanf("%i", &x);
        printf("y: "); scanf("%i", &y);
        // Pide coordenadas x,y
        // Luego controla si son validas
        control = ((x>=0) && (x<3)) && ((y>=0) && (y<3));
    } while ( !control );

    // Cuando son validas, juega
    return nuevo_movimiento(partida,x,y);

}

int RealizarMovimientoIA(tPartida partida) {
    tBusquedaAdversaria b;
    int x, y, auxRet;

    crear_busqueda_adversaria(&b,partida); // Crea la busqueda adversaria

    proximo_movimiento(b,&x,&y); // Calcula el mejor movimiento
    auxRet = nuevo_movimiento(partida,x,y); // Lo juega

    destruir_busqueda_adversaria(&b); // Destruye la busqueda
    return auxRet; // Devuelve el valor de utilidad
}


int main() {
    tPartida partida;
    char j1[50];
    char j2[50];
    int opt = 0, empieza = 0, state = PART_MOVIMIENTO_OK, i = 0;

    for (i = 0; i < 50; i++) {
        j1[i] = '\0';
        j2[i] = '\0';
    }

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
    scanf("%50s", j1);

    printf("Ingrese nombre del jugador 2: ");
    scanf("%50s", j2);

    printf("Quien empieza? \n1- Jugador 1 \n2- Jugador 2\n3- Random\n\n");
    scanf("%i", &empieza);

    if(empieza = 3) {
        empieza = (rand()%2) + 1;
    }

    nueva_partida(&partida, opt, empieza, j1, j2);


    /*JUEGO*/

    switch(opt) {

        case 1:
            /*MODO JUGADOR VS JUGADOR*/
            // Mientras el movimiento sea valido y la partida no haya terminado
            while(state == PART_MOVIMIENTO_OK || state == PART_MOVIMIENTO_ERROR) {
                state = PedirYRealizarMovimientoJugador(partida); // Jugar
            }
            break;

        case 2:
            /*MODO JUGADOR VS PC*/
            // Mientras el movimiento sea valido y la partida no haya terminado
            while(state == PART_MOVIMIENTO_OK || state == PART_MOVIMIENTO_ERROR) {
                // Si es turno del humano, pedir datos y jugar
                if(partida->turno_de == PART_JUGADOR_1) {
                    state = PedirYRealizarMovimientoJugador(partida);
                }
                else { // Caso contrario, calcular movimiento de la IA
                    state = RealizarMovimientoIA(partida);
                }
            }
            break;
        default:
            finalizar_partida(&partida);
            exit(0);

    }

    ImprimirTablero(partida->tablero);

    if(state == PART_EMPATE) {
        // Si termina en empate, avisa
        printf("\n\n\t\t\tEMPATE\n\n");
    }
    else {
        // Caso contrario, alguien gano y tambien avisa
        printf("\n\n\t\t\tGANADOR: %s\n\n", (state == PART_GANA_JUGADOR_1) ? partida->nombre_jugador_1 : partida->nombre_jugador_2);
    }

    return 0;
}
