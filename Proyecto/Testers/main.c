#include <stdio.h>
#include <stdlib.h>

char fichas [9];
int turno = 0;

void InicializarFichas() {
    for(int i = 0; i < 9; i++) {
        fichas[i] = ' ';
    }
}

void ImprimirTablero() {
    printf(" %c | %c | %c \n", fichas[0], fichas[1], fichas[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", fichas[3], fichas[4], fichas[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", fichas[6], fichas[7], fichas[8]);
}

int ColocarFicha(int x, int y, int jugador) {

    system("cls");

    if ( ( fichas[( 3*(y-1) )+ x-1 ] != ' ') || ( ((3*(y-1))+ x-1) > 9 ) ) {
        ImprimirTablero();
        return 1;
    }

    fichas[( 3*(y-1) )+ x-1 ] = (jugador == 1) ? 'X' : 'O';
    turno++;
    ImprimirTablero();
    return 0;

}

int HayGanador() {
    int ret = 0, i, j; char aux;

    for ( i = 1; turno>2 && !ret && i < 8; i++) { // Recorre todas las posiciones excepto la primera y la ultima

        for( j = 1; !ret && j < 5; j++) { // recorre de 1 a 4, los rangos en que se puede producir una victoria

            if( j == 2 && i != 4 ) continue; // Casos especiales, tengo que revisar una manera mas clean de evitarlos

            aux = fichas[i]; // guarda la ficha 'central'
            if ( aux != ' ') ret = fichas[i-j] == aux && aux == fichas[i+j]; // si la ficha es valida, compara sus simetricos.
                                                                            // Esto puede producir victoria en diagonal, horizontal o vertical
        }
    }

    if ( ret ) { // si hay un ganador
        ret = (fichas[i-1] == 'X') ? 1 : 2; // Devuelve el numero del jugador ganador
        // printf("error con i: %i y con j: %i", i-1, j-1);
    }

    return ret;
}



int main() {
    int x, y, control, winner = 0; // Variables de posicion y control

    InicializarFichas(); // Inicializa el arreglo de caracteres con ' '
    ImprimirTablero(); // Imprime el tablero inicialmente vacio

    while ( turno < 9 && !winner ) {
        // La variable de control 'turno' se incrementa en las llamadas a ColocarFicha
        // La variable de control 'winner' almacena al jugador ganador. En caso de ser 0, es que todavia no gano nadie

        if(turno%2) { // Si turno % 2 == 1 significa que es turno del jugador 2
            do {
                printf("TURNO: %i \nJugador dos, ingrese coordenadas\n", turno);
                printf("x: "); scanf("%i", &x);
                printf("y: "); scanf("%i", &y);
                control = ColocarFicha(x, y, 2);
            } while ( control );
        } else {
            do {
                printf("TURNO: %i \nJugador uno, ingrese coordenadas\n", turno);
                printf("x: "); scanf("%i", &x);
                printf("y: "); scanf("%i", &y);
                control = ColocarFicha(x, y, 1);
            } while ( control ); // Pide coordenadas al jugador y cicla hasta que las coordenadas sean validas
        }

        winner = HayGanador();
    }

    if(winner) {
        printf("\n\n\nEL GANADOR ES EL JUGADOR %i!!!", winner);
    }
    else {
        printf("\n\n\nHAY EMPATE!!!");
    }



    return 0;
}
