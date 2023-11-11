#include <stdio.h>

#define TAM 6

typedef struct posicao {
    int i[4];
    int j[4];
} Posicao;

typedef struct peca {
    int i;
    int j;
    char time;
} Peca;


void inicializarStruct(Posicao *p) {
    for (int i = 0; i < 4; i++) {
        p->i[i] = -1;
        p->j[i] = -1;
    }
}

void inicializarArcoP (Peca arcoP[24], Peca jogo[TAM][TAM]) {
    for (int i = 0, j = 0, k = 5; i < 24; i++, j++) {
        if (i < 6) {
            arcoP[i].i = jogo[1][j].i;
            arcoP[i].j = jogo[1][j].j;
            arcoP[i].time = jogo[1][j].time;
            if (i == 5) {
                j = -1;
            }
        } else if (i < 12) {
            arcoP[i].i = jogo[j][4].i;
            arcoP[i].j = jogo[j][4].j;
            arcoP[i].time = jogo[j][4].time;
            if (i == 11) {
                j = -1;
            }
        } else if (i < 18) {
            arcoP[i].i = jogo[4][k].i;
            arcoP[i].j = jogo[4][k].j;
            arcoP[i].time = jogo[4][k].time;
            k--;
            if (i == 17) {
                k = 5;
            }
        } else {
            arcoP[i].i = jogo[k][1].i;
            arcoP[i].j = jogo[k][1].j;
            arcoP[i].time = jogo[k][1].time;
            k--;
        }
    }
}

// temq arrumar
void inicializarArcoG (Peca arcoG[24], Peca jogo[TAM][TAM]) {
    for (int i = 0; i < 24; i++) {
        if (i < 6) {
            for (int j = 0; j < TAM; j++) {
                arcoG[i] = jogo[2][j];
            }
            
        } else if (i < 12) {
            for (int j = 0; j < TAM; j++) {
                arcoG[i] = jogo[j][3];
            }
        } else if (i < 18) {
            for (int j = 0; j < TAM; j++) {
                arcoG[i] = jogo[3][j];
            }
        } else {
            for (int j = 0; j < TAM; j++) {
                arcoG[i] = jogo[j][2];
            }
        }
    }
}

void podeComerArcoP (int vetL[4], Peca jogo[TAM][TAM], Peca pecaAtacando, Posicao *pecasAComer) {
    int achou, bloqueado, cont, casasAndadas, contPecasComer = 0;
    Peca arcoP[24];
    jogo[pecaAtacando.i][pecaAtacando.j].time = '-';
    inicializarArcoP(arcoP, jogo);

    if (vetL[0] == 1 && (pecaAtacando.j == 1 || pecaAtacando.j == 4)) {
        if (pecaAtacando.j == 1) {
            achou = 0;
            bloqueado = 0;
            cont = 0;
            while (!achou && !bloqueado && cont < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont++;
            }
        } else if (pecaAtacando.j == 4) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 5;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont--;
                if (cont == -1) {
                    cont = 23;
                }
                casasAndadas++;
            }
        }
    }
    if (vetL[1] == 1 && (pecaAtacando.i == 1 || pecaAtacando.i == 4)) {
        if (pecaAtacando.i == 1) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 6;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont++;
                if (cont == 24) {
                    cont = 0;
                }
                casasAndadas++;
            }
        } else if (pecaAtacando.i == 4) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 11;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont--;
                if (cont == -1) {
                    cont = 23;
                }
                casasAndadas++;
            }
        }
    }
    if (vetL[2] == 1 && (pecaAtacando.j == 1 || pecaAtacando.j == 4)) {
        if (pecaAtacando.j == 1) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 17;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont--;
                if (cont == -1) {
                    cont = 23;
                }
                casasAndadas++;
            }
        } else if (pecaAtacando.j == 4) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 12;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont++;
                if (cont == 24) {
                    cont = 0;
                }
                casasAndadas++;
            }
        }
    }
    if (vetL[3] == 1 && (pecaAtacando.i == 1 || pecaAtacando.i == 4)) {
        if (pecaAtacando.i == 1) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 23;
            while (!achou && !bloqueado && cont >= 0) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont--;
            }
        } else if (pecaAtacando.i == 4) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 18;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoP[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoP[cont].time != pecaAtacando.time && arcoP[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoP[cont].i;
                    pecasAComer->j[contPecasComer] = arcoP[cont].j;
                    contPecasComer++;
                }
                cont++;
                if (cont == 23) {
                    cont = 0;
                }
                casasAndadas++;
            }
        }
    }
    jogo[pecaAtacando.i][pecaAtacando.j].time = pecaAtacando.time;
}

void verificarLivre(int vetPos[], Peca tabuleiro[TAM][TAM], int posI, int posJ) {
    int cont = 0;

    for (int i = posI - 1; i >= 0; i--) {
        if (tabuleiro[i][posJ].time != '-') {
            vetPos[cont] = 0;
            break;
        }
    }
    cont++;

    for (int j = posJ + 1; j < TAM; j++) {
        if (tabuleiro[posI][j].time != '-') {
            vetPos[cont] = 0;
            break;
        }
    }
    cont++;

    for (int i = posI + 1; i < TAM; i++) {
        if (tabuleiro[i][posJ].time != '-') {
            vetPos[cont] = 0;
            break;
        }
    }
    cont++;

    for (int j = posJ - 1; j >= 0; j--) {
        if (tabuleiro[posI][j].time != '-') {
            vetPos[cont] = 0;
            break;
        }
    }
    cont++;
}

// t = time

int main()
{
    Posicao p;
    inicializarStruct(&p);
    Peca jogo[TAM][TAM];    

    // Inicia o tabuleiro

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            jogo[i][j].i = i;
            jogo[i][j].j = j;
            
            // if (i == 0 || i == 1) {
                // jogo[i][j].time = 'B';
            // } else if (i == 4 || i == 5){
                // jogo[i][j].time = 'R';
            // } else {
                jogo[i][j].time = '-';
            // }
        }
    }

    int x = 4, y = 4;
    jogo[x][y].time = 'B';

    jogo[5][4].time = 'R';
    jogo[3][4].time = 'R';
    jogo[4][3].time = 'R';
    int vetL[4];
    for (int i = 0; i < 4; i++) {
        vetL[i] = 1;
    }

    verificarLivre(vetL, jogo, jogo[x][y].i, jogo[x][y].j);
    podeComerArcoP(vetL, jogo, jogo[x][y], &p);

    printf("Vetor de caminhos livres: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", vetL[i]);
    }

    printf("\nPossiveis comidas: ");
    for (int i = 0; i < 4; i++)
    {
        printf(" Peca %d: i = %d j = %d", i+1, p.i[i], p.j[i]);
    }
    
    
    // exibir tabuleiro
    printf("\n-----------\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", jogo[i][j].time);
        }
        printf("\n");
    }

    return 0;
}
