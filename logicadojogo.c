#include <stdio.h>

#define TAM 6

typedef struct posicao {
    int i[4];
    int j[4];
    int d[4];
} Posicao;

void inicializarStruct(Posicao *p) {
    for (int i = 0; i < 4; i++) {
        p->i[i] = -1;
        p->j[i] = -1;
        p->d[i] = -1;
    }
}


void verificarLivre(int vetPos[], char tabuleiro[TAM][TAM], int posI, int posJ) {
    int cont = 0;
    for (int i = 0; i < 4; i++) {
        vetPos[i] = 1;
    }

    for (int i = posI + 1; i < TAM; i++) {
        if (tabuleiro[i][posJ] != ' ') {
            vetPos[cont] = 0;
            cont++;
            break;
        }
    }

    for (int i = posI - 1; i >= 0; i--) {
        if (tabuleiro[i][posJ] != ' ') {
            vetPos[cont] = 0;
            cont++;
            break;
        }
    }

    for (int j = posI + 1; j < TAM; j++) {
        if (tabuleiro[j][posI] != ' ') {
            vetPos[cont] = 0;
            cont++;
            break;
        }
    }

    for (int j = posI - 1; j >= 0; j--) {
        if (tabuleiro[j][posI] != ' ') {
            vetPos[cont] = 0;
            cont++;
            break;
        }
    }
}

// t = time
Posicao podeComerArcoP (char t, char tabuleiro[TAM][TAM], int posI, int posJ) {
    Posicao p;
    inicializarStruct(&p);

    if ((posI == 1 && posJ == 1) || (posI == 1 && posJ == 4) || (posI == 4 && posJ == 1) || (posI == 4 && posJ == 4)) {
        int vetPos[4];
        int rodando = 1;
        int achou;
        int auxI, auxJ;
        verificarLivre(vetPos, tabuleiro, posI, posJ);

        if (vetPos[0] == 1) {
            achou = 0;
            while (rodando) {
                auxI = 
            }
        }

        if (vetPos[1] == 1) {
            achou = 0;
            while (rodando) {
                
            }
        }

        if (vetPos[2] == 1) {
            achou = 0;
            while (rodando) {
                
            }
        }

        if (vetPos[3] == 1) {
            achou = 0;
            while (rodando) {
                
            }
        }
    }
    

    return p;
}

Posicao podeComerArcoG (char t, char tabuleiro[TAM][TAM], int posI, int posJ) {
    Posicao p;
    inicializarStruct(&p);

    

    return p;
}

int main()
{
    char jogo[] = {
        'r', 'r', 'r', 'r', 'r', 'r',
        'r', 'r', 'r', 'r', 'r', 'r',
        ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ',
        'b', 'b', 'b', 'b', 'b', 'b',
        'b', 'b', 'b', 'b', 'b', 'b',
    };

    return 0;
}
