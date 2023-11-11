#ifndef LOGICADOJOGO_H
#define LOGICADOJOGO_H

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

void inicializarStruct(Posicao *p);
void inicializarArcoP (Peca arcoP[24], Peca jogo[TAM][TAM]);
void inicializarArcoG (Peca arcoG[24], Peca jogo[TAM][TAM]);
void podeComerArcoP (int vetL[4], Peca jogo[TAM][TAM], Peca pecaAtacando, Posicao *pecasAComer);
void podeComerArcoG (int vetL[4], Peca jogo[TAM][TAM], Peca pecaAtacando, Posicao *pecasAComer);
void verificarLivre(int vetPos[], Peca tabuleiro[TAM][TAM], int posI, int posJ);
void iniciarTabuleiro (Peca jogo[TAM][TAM]);
#endif