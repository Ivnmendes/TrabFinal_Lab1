#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720
#define TAM 6

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void limpaTela() {
system(CLEAR);
}
typedef struct posicao {
    int i[8];
    int j[8];
} Posicao;

typedef struct peca {
    int i;
    int j;
    char time;
    float x;
    float y;
    float raio;
} Peca;

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

void inicializarArcoG (Peca arcoG[24], Peca jogo[TAM][TAM]) {
    for (int i = 0, j = 0, k = 5; i < 24; i++, j++) {
        if (i < 6) {
            arcoG[i].i = jogo[2][j].i;
            arcoG[i].j = jogo[2][j].j;
            arcoG[i].time = jogo[2][j].time;
            if (i == 5) {
                j = -1;
            }
        } else if (i < 12) {
            arcoG[i].i = jogo[j][3].i;
            arcoG[i].j = jogo[j][3].j;
            arcoG[i].time = jogo[j][3].time;
            if (i == 11) {
                j = -1;
            }
        } else if (i < 18) {
            arcoG[i].i = jogo[3][k].i;
            arcoG[i].j = jogo[3][k].j;
            arcoG[i].time = jogo[3][k].time;
            k--;
            if (i == 17) {
                k = 5;
            }
        } else {
            arcoG[i].i = jogo[k][2].i;
            arcoG[i].j = jogo[k][2].j;
            arcoG[i].time = jogo[k][2].time;
            k--;
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

void podeComerArcoG (int vetL[4], Peca jogo[TAM][TAM], Peca pecaAtacando, Posicao *pecasAComer) {
    int achou, bloqueado, cont, casasAndadas, contPecasComer = 0;
    Peca arcoG[24];
    jogo[pecaAtacando.i][pecaAtacando.j].time = '-';
    inicializarArcoG(arcoG, jogo);

    if (vetL[0] == 1 && (pecaAtacando.j == 2 || pecaAtacando.j == 3)) {
        if (pecaAtacando.j == 2) {
            achou = 0;
            bloqueado = 0;
            cont = 0;
            while (!achou && !bloqueado && cont < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
                    contPecasComer++;
                }
                cont++;
            }
        } else if (pecaAtacando.j == 3) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 5;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
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
    if (vetL[1] == 1 && (pecaAtacando.i == 2 || pecaAtacando.i == 3)) {
        if (pecaAtacando.i == 2) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 6;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
                    contPecasComer++;
                }
                cont++;
                if (cont == 24) {
                    cont = 0;
                }
                casasAndadas++;
            }
        } else if (pecaAtacando.i == 3) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 11;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
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
    if (vetL[2] == 1 && (pecaAtacando.j == 2 || pecaAtacando.j == 3)) {
        if (pecaAtacando.j == 2) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 17;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
                    contPecasComer++;
                }
                cont--;
                if (cont == -1) {
                    cont = 23;
                }
                casasAndadas++;
            }
        } else if (pecaAtacando.j == 3) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 12;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
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
    if (vetL[3] == 1 && (pecaAtacando.i == 2 || pecaAtacando.i == 3)) {
        if (pecaAtacando.i == 2) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 23;
            while (!achou && !bloqueado && cont >= 0) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
                    contPecasComer++;
                }
                cont--;
            }
        } else if (pecaAtacando.i == 3) {
            achou = 0;
            bloqueado = 0;
            casasAndadas = 0;
            cont = 18;
            while (!achou && !bloqueado && casasAndadas < 24) {
                if (arcoG[cont].time == pecaAtacando.time) {
                    bloqueado = 1;
                } else if (arcoG[cont].time != pecaAtacando.time && arcoG[cont].time != '-') {
                    achou = 1;
                    pecasAComer->i[contPecasComer] = arcoG[cont].i;
                    pecasAComer->j[contPecasComer] = arcoG[cont].j;
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

    for (int i = 0; i < 4; i++) {
        vetPos[i] = 1;
    }

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

void iniciarTabuleiro (Peca jogo[TAM][TAM]) {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                jogo[i][j].i = i;
                jogo[i][j].j = j;
                
                if (i == 0 || i == 1) {
                    jogo[i][j].time = 'B';
                } else if (i == 4 || i == 5){
                    jogo[i][j].time = 'R';
                } else {
                jogo[i][j].time = '-';
                }
            }
        }
}

void podeAndar (Peca jogo[TAM][TAM], Peca pecaSelecionada, Posicao *posicaoAnda) {
    if (pecaSelecionada.time != '-') {
        int cont = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int ni = pecaSelecionada.i + i;
                int nj = pecaSelecionada.j + j;

                // Verifica se a posição é válida e se está vazia
                if (ni >= 0 && ni < TAM && nj >= 0 && nj < TAM && jogo[ni][nj].time == '-') {
                    posicaoAnda->i[cont] = ni;
                    posicaoAnda->j[cont] = nj;
                    cont++;

                }
            }
        }
    }
}

void inicializarStruct(Posicao *p, Peca jogo[TAM][TAM]) {
    for (int i = 0; i < 8; i++) {
        p->i[i] = -1;
        p->j[i] = -1;
    }
}

void atualizarTabuleiro (Peca jogo[TAM][TAM], ALLEGRO_BITMAP *tabuleiro, Posicao podeAndarPosicoes, Posicao podeComerArcoPPosicoes, Posicao podeComerArcoGPosicoes, Posicao movDica, ALLEGRO_COLOR corTrasparente, int *podeJogar, int situacaoDJogo, int dica) {
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_scaled_bitmap(tabuleiro, 0, 0, al_get_bitmap_width(tabuleiro), al_get_bitmap_height(tabuleiro), 0, 0, 800, 600, 0);
    for (int i = 0, y = 0; i < TAM; i++, y+=67) {
        for (int j = 0, x = 0; j < TAM; j++, x+=87) {
            if (jogo[i][j].time == 'R') {
                al_draw_filled_circle(175+x, 140+y, 30, al_map_rgb(255, 0, 0));

            } else if (jogo[i][j].time == 'B') {
                al_draw_filled_circle(175+x, 140+y, 30, al_map_rgb(0, 0, 255));
            }
            jogo[i][j].x = 175+x;
                jogo[i][j].y = 140+y;
                jogo[i][j].raio = 30;
        }
    }

    if (situacaoDJogo) {
        for (int i = 0; i < 8; i++) {
            if (podeAndarPosicoes.i[i] != -1 && podeAndarPosicoes.j[i] != -1) {
                al_draw_filled_circle(175 + podeAndarPosicoes.j[i] * 87, 140 + podeAndarPosicoes.i[i] * 67, 30, corTrasparente);
                *podeJogar = 1;
            }
            if (podeComerArcoPPosicoes.i[i] != - 1) {
                al_draw_filled_circle(175 + podeComerArcoPPosicoes.j[i] * 87, 140 + podeComerArcoPPosicoes.i[i] * 67, 30, corTrasparente);
                *podeJogar = 1;
            }
            if (podeComerArcoGPosicoes.i[i] != - 1) {
                al_draw_filled_circle(175 + podeComerArcoGPosicoes.j[i] * 87, 140 + podeComerArcoGPosicoes.i[i] * 67, 30, corTrasparente);
                *podeJogar = 1;
            }
        }
    }

    if (dica) {
        if (movDica.i[0] != -1 && movDica.j[0] != -1) {
            al_draw_line(175 + movDica.j[0] * 87 - 20, 140 + movDica.i[0] * 67 - 20, 175 + movDica.j[0] * 87 + 20, 140 + movDica.i[0] * 67 + 20, al_map_rgb(0, 0, 0), 4);
            al_draw_line(175 + movDica.j[0] * 87 - 20, 140 + movDica.i[0] * 67 + 20, 175 + movDica.j[0] * 87 + 20, 140 + movDica.i[0] * 67 - 20, al_map_rgb(0, 0, 0), 4);
        }
        if (movDica.i[1] != -1 && movDica.j[1] != -1) {
            al_draw_line(175 + movDica.j[1] * 87 - 20, 140 + movDica.i[1] * 67, 175 + movDica.j[1] * 87 + 20, 140 + movDica.i[1] * 67, al_map_rgb(0, 0, 0), 4);
        }
    }    
}

void exibirJogo (Peca jogo[TAM][TAM], Posicao podeAndarPosicoes, Posicao podeComerArcoPPosicoes, Posicao podeComerArcoGPosicoes, Posicao movDica, ALLEGRO_BITMAP *tabuleiro, ALLEGRO_FONT *font, int horas, int minutos, int segundos, int turno, ALLEGRO_COLOR corTrasparente, int vezDoComputador, int situacaoDJogo, int *podeJogar, int totDicasV, int totDicasA, int dica) {    
    char vetColunas[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int auxPodeJogar = *podeJogar;
    atualizarTabuleiro(jogo, tabuleiro, podeAndarPosicoes, podeComerArcoPPosicoes, podeComerArcoGPosicoes, movDica, corTrasparente, &auxPodeJogar, situacaoDJogo, dica);
    *podeJogar = auxPodeJogar;
    al_draw_textf(font, al_map_rgb(0, 0, 0), LARGURA_TELA, 10, ALLEGRO_ALIGN_RIGHT, "Tempo: %02d:%02d:%02d", horas, minutos, segundos);
    
    al_draw_rectangle(LARGURA_TELA - 190, ALTURA_TELA - 240, LARGURA_TELA, ALTURA_TELA - 170, al_map_rgb(0, 0, 0), 2);
    al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA - 95, ALTURA_TELA - 220, ALLEGRO_ALIGN_CENTER, "Dica");
    al_draw_rectangle(LARGURA_TELA - 190, ALTURA_TELA - 150, LARGURA_TELA, ALTURA_TELA - 80, al_map_rgb(0, 0, 0), 2);
    al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA - 95, ALTURA_TELA - 130, ALLEGRO_ALIGN_CENTER, "Pausar");
    
    if (turno == 'R' && vezDoComputador == 0) {
        al_draw_text(font, al_map_rgb(255, 0, 0), LARGURA_TELA, 40, ALLEGRO_ALIGN_RIGHT, "Turno do vermelho");
        al_draw_textf(font, al_map_rgb(255, 0, 0), LARGURA_TELA, 80, ALLEGRO_ALIGN_RIGHT, "Total de dicas: %d", totDicasV);
    } else if (turno == 'B' && vezDoComputador == 0){
        al_draw_text(font, al_map_rgb(0, 0, 255), LARGURA_TELA, 40, ALLEGRO_ALIGN_RIGHT, "Turno do azul");
        al_draw_textf(font, al_map_rgb(0, 0, 255), LARGURA_TELA, 80, ALLEGRO_ALIGN_RIGHT, "Total de dicas: %d", totDicasA);
    } else {
        al_draw_text(font, al_map_rgb(0, 0, 255), LARGURA_TELA, 40, ALLEGRO_ALIGN_RIGHT, "Computador jogando");
    }

    al_draw_line(0, 610, 800, 610, al_map_rgb(0, 0, 0), 4);
    for (int i = 1, x = 0; i <= 6; i++, x+=87) {
        al_draw_line(175+x, 620, 175+x, 600, al_map_rgb(0, 0, 0), 4);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 175+x, 630, ALLEGRO_ALIGN_CENTER, "%c", vetColunas[i-1]);
    }
    al_draw_line(800, 610, 800, 0, al_map_rgb(0, 0, 0), 4);
    for (int i = 0, y = 0; i < 6; i++, y+=67) {
        al_draw_line(810, 143+y, 790, 143+y, al_map_rgb(0, 0, 0), 4);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 830, 135+y, ALLEGRO_ALIGN_CENTER, "%d", i);
    }
    //al_flip_display();
}

void descobrirMovimentoPossivel (Peca jogo[TAM][TAM], Posicao *movimentoEcontrado, int *matou, int dica, char time) {
    Posicao jogadaPossivel;
    Peca pecaAtual;
    int auxMatou = *matou;
    int vetL[4];
    int achou = 0;
    int posPecaI, posPecaJ;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (jogo[i][j].time == time) {
                inicializarStruct(&jogadaPossivel, jogo);
                pecaAtual.i = i;
                pecaAtual.j = j;
                pecaAtual.time = time;
                if (i == 2 || i == 3 || j == 2 || j == 3) {
                    verificarLivre(vetL, jogo, i, j);
                    podeComerArcoG(vetL, jogo, pecaAtual, &jogadaPossivel);
                }
                if (jogadaPossivel.i[0] != -1) {
                    achou = 1;
                    *matou = 1;
                    posPecaI = i;
                    posPecaJ = j;
                    break;
                }
                if (i == 1 || i == 4 || j == 1 || j == 4) { 
                    verificarLivre(vetL, jogo, i, j); 
                    podeComerArcoP(vetL, jogo, pecaAtual, &jogadaPossivel);
                }
                if (jogadaPossivel.i[0] != -1) {
                    achou = 1;
                    *matou = 1;
                    posPecaI = i;
                    posPecaJ = j;
                    break;
                }
            }
        }
        if (achou) {
            break;
        }
    }

    if (!achou) {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (achou) {
                    break;
                }
                if (jogo[i][j].time == time) {
                    inicializarStruct(&jogadaPossivel, jogo);
                    pecaAtual.i = i;
                    pecaAtual.j = j;
                    pecaAtual.time = time;
                    if (i < 2 && j < 2) {
                        for (int k = j+1; k > j-2 && k >= 0; k--) {
                            if (jogo[i+1][k].time == '-') {
                                jogadaPossivel.i[0] = i+1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            for (int k = i+1; k > i-2 && k >= 0; k--) {
                                if (jogo[k][j+1].time == '-') {
                                    jogadaPossivel.i[0] = k;
                                    jogadaPossivel.j[0] = j+1;
                                    achou = 1;
                                    posPecaI = i;
                                    posPecaJ = j;
                                    break;
                                }
                            }
                        }
                    } else if (i < 2 && j > 3) {
                        for (int k = j-1; k < j+2 && k < TAM; k++) {
                            if (jogo[i+1][k].time == '-') {
                                jogadaPossivel.i[0] = i+1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            for (int k = i+1; k > i-2 && k >= 0; k--) {
                                if (jogo[k][j-1].time == '-') {
                                    jogadaPossivel.i[0] = k;
                                    jogadaPossivel.j[0] = j-1;
                                    achou = 1;
                                    posPecaI = i;
                                    posPecaJ = j;
                                    break;
                                }
                            }
                        }
                    } else if (i > 3 && j < 2) {
                        for (int k = j+1; k > j-2 && k >= 0; k--) {
                            if (jogo[i-1][k].time == '-') {
                                jogadaPossivel.i[0] = i-1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            for (int k = i+1; k > i-2 && k < TAM; k--) {
                                if (jogo[k][j+1].time == '-') {
                                    jogadaPossivel.i[0] = k;
                                    jogadaPossivel.j[0] = j+1;
                                    achou = 1;
                                    posPecaI = i;
                                    posPecaJ = j;
                                    break;
                                }
                            }
                        }
                    } else if (i > 3 && j > 3) {
                        for (int k = j+1; k > j-2 && k < TAM; k--) {
                            if (jogo[i-1][k].time == '-') {
                                jogadaPossivel.i[0] = i-1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            for (int k = i+1; k > i-2 && k < TAM; k--) {
                                if (jogo[k][j-1].time == '-') {
                                    jogadaPossivel.i[0] = k;
                                    jogadaPossivel.j[0] = j-1;
                                    achou = 1;
                                    posPecaI = i;
                                    posPecaJ = j;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (achou) {
                break;
            }
        }
    }

    if (!achou) {
        for (int i = TAM - 1; i >= 0; i--) {
            for (int j = TAM - 1; j >= 0; j--) {
                if (jogo[i][j].time == time) {
                    inicializarStruct(&jogadaPossivel, jogo);
                    pecaAtual.i = i;
                    pecaAtual.j = j;
                    pecaAtual.time = time;
                    podeAndar(jogo, pecaAtual, &jogadaPossivel);
                    if (jogadaPossivel.i[0] != -1) {
                        achou = 1;
                        posPecaI = i;
                        posPecaJ = j;
                        break;
                    }
                }
            }
            if (achou) {
                break;
            }
        }
    }
    
    if (dica) {
        *matou = auxMatou;
    }
    movimentoEcontrado->i[0] = jogadaPossivel.i[0];
    movimentoEcontrado->j[0] = jogadaPossivel.j[0];
    movimentoEcontrado->i[1] = posPecaI;
    movimentoEcontrado->j[1] = posPecaJ;
}

void descobrirMovimentoPossivelOp2 (Peca jogo[TAM][TAM], Posicao *movimentoEcontrado, int *matou, int dica, char time) {
    Posicao jogadaPossivel;
    Peca pecaAtual;
    int auxMatou = *matou;
    int vetL[4];
    int achou = 0;
    int posPecaI, posPecaJ;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (jogo[i][j].time == time) {
                inicializarStruct(&jogadaPossivel, jogo);
                pecaAtual.i = i;
                pecaAtual.j = j;
                pecaAtual.time = time;
                if (i == 1 || i == 4 || j == 1 || j == 4) { 
                    verificarLivre(vetL, jogo, i, j); 
                    podeComerArcoP(vetL, jogo, pecaAtual, &jogadaPossivel);
                }
                if (jogadaPossivel.i[0] != -1) {
                    achou = 1;
                    *matou = 1;
                    posPecaI = i;
                    posPecaJ = j;
                    break;
                }
                if (i == 2 || i == 3 || j == 2 || j == 3) {
                    verificarLivre(vetL, jogo, i, j);
                    podeComerArcoG(vetL, jogo, pecaAtual, &jogadaPossivel);
                }
                if (jogadaPossivel.i[0] != -1) {
                    achou = 1;
                    *matou = 1;
                    posPecaI = i;
                    posPecaJ = j;
                    break;
                }
            }
        }
        if (achou) {
            break;
        }
    }

    if (!achou) {
        for (int i = TAM - 1; i >= 0; i--) {
            for (int j = TAM - 1; j >= 0; j--) {
                if (achou) {
                    break;
                }
                if (jogo[i][j].time == time) {
                    inicializarStruct(&jogadaPossivel, jogo);
                    pecaAtual.i = i;
                    pecaAtual.j = j;
                    pecaAtual.time = time;
                    if (i == 0 && (j == 2 || j == 3)) {
                        for (int k = j-1; k < j+2; k++) {
                            if (jogo[i+1][k].time == '-') {
                                jogadaPossivel.i[0] = i+1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            if (j == 2) {
                                for (int k = i; k < i+2; k++) {
                                    if (jogo[k][j-1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j-1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            } else {
                                for (int k = i; k < i+2; k++) {
                                    if (jogo[k][j+1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j+1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            }
                        }
                    } else if ((i == 2 || i == 3) && j == 1) {
                        for (int k = i-1; k < i+2; k++) {
                            if (jogo[k][j+1].time == '-') {
                                jogadaPossivel.i[0] = k;
                                jogadaPossivel.j[0] = j+1;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            if (i == 2) {
                                for (int k = j; k < j+2; k++) {
                                    if (jogo[i-1][k].time == '-') {
                                        jogadaPossivel.i[0] = i-1;
                                        jogadaPossivel.j[0] = k;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            } else {
                                for (int k = j; k < j+2; k++) {
                                    if (jogo[i+1][k].time == '-') {
                                        jogadaPossivel.i[0] = i+1;
                                        jogadaPossivel.j[0] = k;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            }
                        }
                    } else if (i == 5 && (j == 2 || j == 3)) {
                        for (int k = j-1; k < j+2; k++) {
                            if (jogo[i-1][k].time == '-') {
                                jogadaPossivel.i[0] = i-1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            if (j == 2) {
                                for (int k = i; k > i-2; k--) {
                                    if (jogo[k][j-1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j-1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            } else {
                                for (int k = i; k > i-2; k--) {
                                    if (jogo[k][j+1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j+1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            }
                        }
                    } else if ((i == 2 || i == 3) && j == 5) {
                        for (int k = i-1; k < i+2; k++) {
                            if (jogo[k][j-1].time == '-') {
                                jogadaPossivel.i[0] = k;
                                jogadaPossivel.j[0] = j-1;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            if (i == 2) {
                                for (int k = j; k > j-2; k--) {
                                    if (jogo[i-1][k].time == '-') {
                                        jogadaPossivel.i[0] = i-1;
                                        jogadaPossivel.j[0] = k;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            } else {
                                for (int k = j; k > j-2; k--) {
                                    if (jogo[i+1][k].time == '-') {
                                        jogadaPossivel.i[0] = i+1;
                                        jogadaPossivel.j[0] = k;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            }
                        }
                    } else if (i == 3 && (j == 2 || j == 3)) {
                        for (int k = j-1; k < j+2; k++) {
                            if (jogo[i-1][k].time == '-') {
                                jogadaPossivel.i[0] = i-1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            if (j == 2) {
                                for (int k = i-1; k < i+2; k++) {
                                    if (jogo[k][j-1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j-1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            } else {
                                for (int k = i-1; k < i+2; k++) {
                                    if (jogo[k][j+1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j+1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            }
                        }
                    } else if (i == 2 && (j == 2 || j == 3)) {
                        for (int k = j-1; k < j+2; k++) {
                            if (jogo[i+1][k].time == '-') {
                                jogadaPossivel.i[0] = i+1;
                                jogadaPossivel.j[0] = k;
                                achou = 1;
                                posPecaI = i;
                                posPecaJ = j;
                                break;
                            }
                        }
                        if (!achou) {
                            if (j == 2) {
                                for (int k = i-1; k < i+2; k++) {
                                    if (jogo[k][j-1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j-1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            } else {
                                for (int k = i-1; k < i+2; k++) {
                                    if (jogo[k][j+1].time == '-') {
                                        jogadaPossivel.i[0] = k;
                                        jogadaPossivel.j[0] = j+1;
                                        achou = 1;
                                        posPecaI = i;
                                        posPecaJ = j;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (achou) {
                break;
            }
        }
    }

    if (!achou) {
        for (int i = TAM - 1; i >= 0; i--) {
            for (int j = TAM - 1; j >= 0; j--) {
                if (jogo[i][j].time == time) { 
                    inicializarStruct(&jogadaPossivel, jogo);
                    pecaAtual.i = i;
                    pecaAtual.j = j;
                    pecaAtual.time = time;
                    podeAndar(jogo, pecaAtual, &jogadaPossivel);
                    if (jogadaPossivel.i[0] != -1) {
                        achou = 1;
                        posPecaI = i;
                        posPecaJ = j;
                        break;
                    }
                }
            }
            if (achou) {
                break;
            }
        }
    }
    
    if (dica) {
        *matou = auxMatou;
    }

    movimentoEcontrado->i[0] = jogadaPossivel.i[0];
    movimentoEcontrado->j[0] = jogadaPossivel.j[0];
    movimentoEcontrado->i[1] = posPecaI;
    movimentoEcontrado->j[1] = posPecaJ;
}

void movimento (Peca jogo[TAM][TAM], int iAtual, int jAtual, int iFuturo, int jFuturo) {
    jogo[iFuturo][jFuturo].time = jogo[iAtual][jAtual].time;
    jogo[iAtual][jAtual].time = '-';
}

void jogadaPossivel (Posicao *podeAndarP, Posicao *podeComerArcP, Posicao *podeComerArcG, int vetL[], Peca jogo[TAM][TAM], Peca pecaEscolhida, int podeJogar, int *situacaoDJogo) {
    Posicao podeAndarPosicoes, podeComerArcoPPosicoes, podeComerArcoGPosicoes;
    
    inicializarStruct(&podeAndarPosicoes, jogo);
    inicializarStruct(&podeComerArcoPPosicoes, jogo);
    inicializarStruct(&podeComerArcoGPosicoes, jogo);
    if (pecaEscolhida.i != -1) {
        podeAndar(jogo, pecaEscolhida, &podeAndarPosicoes);
        if (pecaEscolhida.i == 1 || pecaEscolhida.i == 4 || pecaEscolhida.j == 1 || pecaEscolhida.j == 4) {
            verificarLivre(vetL, jogo, pecaEscolhida.i, pecaEscolhida.j);
            podeComerArcoP(vetL, jogo, pecaEscolhida, &podeComerArcoPPosicoes);
        }
        if (pecaEscolhida.i == 2 || pecaEscolhida.i == 3 || pecaEscolhida.j == 2 || pecaEscolhida.j == 3) {
            verificarLivre(vetL, jogo, pecaEscolhida.i, pecaEscolhida.j);
            podeComerArcoG(vetL, jogo, pecaEscolhida, &podeComerArcoGPosicoes);
        }
    }

    *podeAndarP = podeAndarPosicoes;
    *podeComerArcP = podeComerArcoPPosicoes;
    *podeComerArcG = podeComerArcoGPosicoes;
    if (!podeJogar)
    {
        *situacaoDJogo = 0;
    }
}

int main()
{
    // Variaveis da janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *fontTitulo = NULL;
    ALLEGRO_FONT *fontTexto = NULL;
    ALLEGRO_BITMAP *tabuleiro = NULL;
    ALLEGRO_BITMAP *tabuleiroExemplo = NULL;
    ALLEGRO_BITMAP *capturaExemplo = NULL;
    ALLEGRO_BITMAP *capturaExemplo2 = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_TIMER *timer = NULL;

    // Inicializando a biblioteca Allegro
    al_init();
    if (!al_init()) {
        printf("Falha ao inicializar a Allegro");
        return -1;
    }

    al_init_font_addon();
    if (!al_init_font_addon()) {
        printf("Falha ao inicializar add-on allegro_font");
        return -1;
    }

    al_init_image_addon();
    if (!al_init_image_addon()) {
        printf("Falha ao inicializar add-on allegro_image");
        return -1;
    }

    al_init_primitives_addon();
    if (!al_init_primitives_addon()) {
        printf("Falha ao inicializar add-on allegro_primitives");
        return -1;
    }

    al_init_ttf_addon();
    if (!al_init_ttf_addon()) {
        printf("Falha ao inicializar add-on allegro_ttf");
        return -1;
    }

    al_install_mouse();
    if (!al_install_mouse()) {
        printf("Falha ao inicializar o mouse");
        return -1;
    }

    al_install_keyboard();
    if (!al_install_keyboard()) {
        printf("Falha ao inicializar o teclado");
        return -1;
    }

    timer = al_create_timer(1.0);
    al_start_timer(timer);

    // Criando a janela principal
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela) {
        printf("Falha ao criar a janela");
        return -1;
    }
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 20, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Carregando a fonte
    font = al_load_font("./source/font.ttf", 30, 0);
    if (!font) {
        printf("Falha ao carregar \"font.ttf\".\n");
        return -1;
    }

    fontTitulo = al_load_font("./source/font.ttf", 50, 0);
    if (!fontTitulo) {
        printf("Falha ao carregar \"font.ttf\".\n");
        return -1;
    }
    fontTexto = al_load_font("./source/font.ttf", 15, 0);
    if (!fontTexto) {
        printf("Falha ao carregar \"font.ttf\".\n");
        return -1;
    }

    // Carregando a imagem do tabuleiro
    tabuleiro = al_load_bitmap("./source/tabuleiro.png");
    if (!tabuleiro) {
        printf("Falha ao carregar \"tabuleiro.png\".\n");
        return -1;
    }

    tabuleiroExemplo = al_load_bitmap("./source/tabsurakartaexemplo.png");
    if (!tabuleiroExemplo) {
        printf("Falha ao carregar \"tabsurakartaexemplo.png\".\n");
        return -1;
    }

    capturaExemplo = al_load_bitmap("./source/exemploCaptura.png");
    if (!capturaExemplo) {
        printf("Falha ao carregar \"exemploCaptura.png\".\n");
        return -1;
    }

    capturaExemplo2 = al_load_bitmap("./source/exemploCaptura2.png");
    if (!capturaExemplo2) {
        printf("Falha ao carregar \"exemploCaptura2.png\".\n");
        return -1;
    }

    // Criando a fila de eventos
    fila_eventos = al_create_event_queue();
    if (!fila_eventos) {
        printf("Falha ao criar fila de eventos.");
        return -1;
    }

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    // Registrando os eventos da janela principal e do mouse
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));   
    
    // Variaveis do jogo - Contadoras
    int segundos, minutos, horas;
    int tempoDeEspera = 0;
    int rodada;

    // Variaveis do jogo - constantes allegro
    float timeSleep = 0.07;
    int xBotao = LARGURA_TELA / 2 - 140, yBotao = ALTURA_TELA / 4 + 50;
    ALLEGRO_COLOR corVermelhoPeca = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR corAzulPeca = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR corTrasparente = al_map_rgba_f(1, 1, 0, 0.7);
    ALLEGRO_COLOR corBrancoTrasparente = al_map_rgba_f(1, 1, 1, 0.8);

    // Variaveis do jogo - flags
    int rodando = 1, situacao = 1, situacaoAux, situacaoDJogo = 0, podeJogar = 0;
    
    // Variáveis do jogo - lógica
    srand(time(NULL));
    char turno = 'R';
    char vetColunas[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char auxTurno[9];
    int totPecasV, totPecasA, totDicasV, totDicasA;
    int vetL[4];
    int op;
    int vezDoComputador = 0, matou, dica;
    int pagAjuda;
    
    Peca jogo[TAM][TAM];
    Peca pecaEscolhida;
    pecaEscolhida.i = -1;
    Posicao movDica;
    Posicao jogadaDoComputador;
    Posicao podeAndarPosicoes;
    Posicao podeComerArcoGPosicoes;
    Posicao podeComerArcoPPosicoes;

    while (rodando) {
        while (!al_is_event_queue_empty(fila_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_TIMER && (situacao == 2 || situacao == 3)) {
                    segundos++;
                    if (segundos == 60) {
                        minutos++;
                        segundos = 0;
                    }
                    if (minutos == 60) {
                        horas++;
                        minutos = 0;
                    }
                    if (horas == 24) {
                        segundos = 0;
                        minutos = 0;
                        horas = 0;
                    }

                    if (vezDoComputador == 1 && tempoDeEspera <= 1) {
                        tempoDeEspera++;
                    }
            }

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE && situacao == 7) {
                    situacao = situacaoAux;
                    al_rest(timeSleep);
                } else if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE && (situacao == 2 || (situacao == 3 && vezDoComputador == 0))) {
                    situacao = 7;
                    al_rest(timeSleep);
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_TAB) {
                    situacao = 6;
                }
            }

            if (situacao == 1 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 280 && evento.mouse.y >= yBotao && evento.mouse.y <= yBotao + 70) {
                    limpaTela();
                    turno = 'R';
                    situacao = 2;
                    iniciarTabuleiro(jogo);
                    inicializarStruct(&movDica, jogo);
                    inicializarStruct(&podeAndarPosicoes, jogo);
                    inicializarStruct(&podeComerArcoGPosicoes, jogo);
                    inicializarStruct(&podeComerArcoPPosicoes, jogo);
                    rodada = 0;
                    segundos = 0;
                    minutos = 0;
                    horas = 0;
                    situacaoAux = 2;
                    situacaoDJogo = 0;
                    podeJogar = 0;
                    pecaEscolhida.i = -1;
                    totPecasA = 12;
                    totPecasV = 12;
                    totDicasA = 2;
                    totDicasV = 2;
                    dica = 0;
                    al_rest(timeSleep);
                } else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 280 && evento.mouse.y >= yBotao + 90 && evento.mouse.y <= yBotao + 160) {
                    limpaTela();
                    turno = 'R';
                    situacao = 3;
                    iniciarTabuleiro(jogo);
                    inicializarStruct(&movDica, jogo);
                    inicializarStruct(&podeAndarPosicoes, jogo);
                    inicializarStruct(&podeComerArcoGPosicoes, jogo);
                    inicializarStruct(&podeComerArcoPPosicoes, jogo);
                    rodada = 0;
                    segundos = 0;
                    minutos = 0;
                    horas = 0;
                    situacaoAux = 3;
                    situacaoDJogo = 0;
                    podeJogar = 0;
                    pecaEscolhida.i = -1;
                    totPecasA = 12;
                    totPecasV = 12;
                    totDicasV = 2;
                    vezDoComputador = 0;
                    matou = 0;
                    dica = 0;
                    al_rest(timeSleep);
                } else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 280 && evento.mouse.y >= yBotao + 180 && evento.mouse.y <= yBotao + 250) {
                    situacao = 4;
                    pagAjuda = 1;
                    al_rest(timeSleep);
                } else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 280 && evento.mouse.y >= yBotao + 270 && evento.mouse.y <= yBotao + 340) {
                    situacao = 5;
                    al_rest(timeSleep);
                } else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 280 && evento.mouse.y >= yBotao + 360 && evento.mouse.y <= yBotao + 430) {
                    rodando = 0;
                }
            }
            if ((situacao == 2 || situacao == 3) && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && vezDoComputador == 0) {
                if (evento.mouse.x >= 0 && evento.mouse.x <= 800 && evento.mouse.y >= 0 && evento.mouse.y <= 600) {
                    int i = (evento.mouse.y - 140) / 67;
                    int j = (evento.mouse.x - 175) / 87;
                    for (int i = 0; i < TAM; i++) {
                        for (int j = 0; j < TAM; j++) {
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio && jogo[i][j].time == turno) {
                                pecaEscolhida.i = jogo[i][j].i;
                                pecaEscolhida.j = jogo[i][j].j;
                                pecaEscolhida.time = jogo[i][j].time;
                                i=6;
                                situacaoDJogo = 1;
                                podeJogar = 1;
                                break;
                            }
                        }
                    }
                    al_rest(timeSleep);
                }
                
            }
            if ((situacao == 2 || situacao == 3) && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && vezDoComputador == 0) {
                if (podeJogar == 1 && evento.mouse.x >= 0 && evento.mouse.x <= 800 && evento.mouse.y >= 0 && evento.mouse.y <= 600) {
                    for (int k = 0; k < 8; k++) {
                        if (podeAndarPosicoes.i[k] != -1) {
                            int i = podeAndarPosicoes.i[k];
                            int j = podeAndarPosicoes.j[k];
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio) {
                                movimento (jogo, pecaEscolhida.i, pecaEscolhida.j, i, j);
                                if (turno == 'B') {
                                    strcpy(auxTurno, "Azul");
                                    if (dica) {
                                        totDicasA--;
                                        dica = 0;
                                        inicializarStruct(&movDica, jogo);
                                    }
                                } else {
                                    if (dica) {
                                        totDicasV--;
                                        dica = 0;
                                        inicializarStruct(&movDica, jogo);
                                    }
                                    strcpy(auxTurno, "Vermelho");
                                }
                                printf("Rodada: %d, Turno: %s, A peca %c%d foi para %c%d\n", rodada, auxTurno, vetColunas[pecaEscolhida.j], pecaEscolhida.i, vetColunas[j], i);
                                if (situacao == 2) {
                                    turno = (turno == 'R') ? 'B' : 'R';
                                    rodada++;
                                } else {
                                    vezDoComputador = 1;
                                    rodada++;
                                }
                                situacaoDJogo = 0;
                                podeJogar = 0;
                                pecaEscolhida.i = -1;
                                break;
                            }
                        }
                        if (podeComerArcoPPosicoes.i[k] != -1) {
                            int i = podeComerArcoPPosicoes.i[k];
                            int j = podeComerArcoPPosicoes.j[k];
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio) {
                                movimento (jogo, pecaEscolhida.i, pecaEscolhida.j, i, j);
                                if (turno == 'B') {
                                    if (dica) {
                                        totDicasA--;
                                        dica = 0;
                                        inicializarStruct(&movDica, jogo);
                                    }
                                    strcpy(auxTurno, "Azul");
                                    totPecasV--;
                                } else {
                                    if (dica) {
                                        totDicasV--;
                                        dica = 0;
                                        inicializarStruct(&movDica, jogo);
                                    }
                                    strcpy(auxTurno, "Vermelho");
                                    totPecasA--;
                                }
                                printf("Rodada: %d, Turno: %s, A peca %c%d capturou a peca em %c%d\n", rodada, auxTurno, vetColunas[pecaEscolhida.j], pecaEscolhida.i, vetColunas[j], i);
                                if (totPecasA == 0 || totPecasV == 0) {
                                    situacao = 6;
                                    break;
                                }
                                if (situacao == 2) {
                                    turno = (turno == 'R') ? 'B' : 'R';
                                    rodada++;
                                } else {
                                    vezDoComputador = 1;
                                    rodada++;
                                }
                                situacaoDJogo = 0;
                                podeJogar = 0;
                                pecaEscolhida.i = -1;
                                inicializarStruct(&podeComerArcoPPosicoes, jogo);
                                break;
                            }
                        }
                        if (podeComerArcoGPosicoes.i[k] != -1) {
                            int i = podeComerArcoGPosicoes.i[k];
                            int j = podeComerArcoGPosicoes.j[k];
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio) {
                                movimento (jogo, pecaEscolhida.i, pecaEscolhida.j, i, j);
                                if (turno == 'B') {
                                    if (dica) {
                                        totDicasA--;
                                        dica = 0;
                                        inicializarStruct(&movDica, jogo);
                                    }
                                    strcpy(auxTurno, "Azul");
                                    totPecasV--;
                                } else {
                                    if (dica) {
                                        totDicasV--;
                                        dica = 0;
                                        inicializarStruct(&movDica, jogo);
                                    }
                                    strcpy(auxTurno, "Vermelho");
                                    totPecasA--;
                                }
                                printf("Rodada: %d, Turno: %s, A peca %c%d capturou a peca em %c%d\n", rodada, auxTurno, vetColunas[pecaEscolhida.j], pecaEscolhida.i, vetColunas[j], i);
                                if (totPecasA == 0 || totPecasV == 0) {
                                    situacao = 6;
                                    break;
                                }
                                if (situacao == 2) {
                                    turno = (turno == 'R') ? 'B' : 'R';
                                    rodada++;
                                } else {
                                    vezDoComputador = 1;
                                    rodada++;
                                }
                                situacaoDJogo = 0;
                                podeJogar = 0;
                                pecaEscolhida.i = -1;
                                inicializarStruct(&podeComerArcoGPosicoes, jogo);
                                break;
                            }
                        }
                    }
                }   
                al_rest(timeSleep);
            }

            if ((situacao == 2 || situacao == 3) && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && vezDoComputador == 0) {
                if (evento.mouse.x >= LARGURA_TELA - 150 && evento.mouse.x <= LARGURA_TELA && evento.mouse.y >= ALTURA_TELA - 150 && evento.mouse.y <= ALTURA_TELA - 80) {
                    situacao = 7;
                    al_rest(timeSleep);
                }
            }

            if ((situacao == 2 || situacao == 3) && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && vezDoComputador == 0) {
                if (evento.mouse.x >= LARGURA_TELA - 150 && evento.mouse.x <= LARGURA_TELA && evento.mouse.y >= ALTURA_TELA - 240 && evento.mouse.y <= ALTURA_TELA - 170) {
                    if (turno == 'R') {
                        if (totDicasV > 0) {
                            dica = 1;
                            inicializarStruct(&movDica, jogo);
                            if (situacao == 2) {
                                descobrirMovimentoPossivelOp2(jogo, &movDica, &matou, dica, turno);
                            } else if (situacao == 3) {
                                descobrirMovimentoPossivel(jogo, &movDica, &matou, dica, turno);
                            }
                        }
                    } else if (turno == 'B') {
                        if (totDicasA > 0) {
                            dica = 1;
                            inicializarStruct(&movDica, jogo);
                            if (situacao == 2) {
                                descobrirMovimentoPossivelOp2(jogo, &movDica, &matou, dica, turno);
                            } else if (situacao == 3) {
                                descobrirMovimentoPossivel(jogo, &movDica, &matou, dica, turno);
                            }
                        }
                    }
                }
            }
            
            if (situacao == 4 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.y >= ALTURA_TELA - 50 - 40 && evento.mouse.y <= ALTURA_TELA - 50 + 40) {
                    if (evento.mouse.x >= 50 - 40 && evento.mouse.x <= 50 + 40) {
                        pagAjuda--;
                    } else if (evento.mouse.x >= LARGURA_TELA - 50 - 40 && evento.mouse.x <= LARGURA_TELA + 50 + 40) {
                        pagAjuda++;
                    }
                    
                    if (pagAjuda < 1 || pagAjuda > 6) {
                        situacao = 1;
                    }
                }
            }

            if (situacao == 5 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.x >= 50 - 40 && evento.mouse.x <= 50 + 40 && evento.mouse.y >= 50 - 40 && evento.mouse.y <= 50 + 40) {
                    situacao = 1;
                }
            }
            
            if (situacao == 6 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.y >= yBotao + 20 && evento.mouse.y <= yBotao + 100) {
                    if (evento.mouse.x >= xBotao - 180 && evento.mouse.x <= xBotao + 70) {
                        limpaTela();
                        turno = 'R';
                        situacao = situacaoAux;
                        iniciarTabuleiro(jogo);
                        inicializarStruct(&movDica, jogo);
                        inicializarStruct(&podeAndarPosicoes, jogo);
                        inicializarStruct(&podeComerArcoGPosicoes, jogo);
                        inicializarStruct(&podeComerArcoPPosicoes, jogo);
                        rodada = 0;
                        segundos = 0;
                        minutos = 0;
                        horas = 0;
                        situacaoDJogo = 0;
                        podeJogar = 0;
                        pecaEscolhida.i = -1;
                        totPecasA = 12;
                        totPecasV = 12;
                        totDicasV = 2;
                        totDicasA = 2;
                        dica = 0;
                        if (situacaoAux == 3) {
                            vezDoComputador = 0;
                            matou = 0;
                        }
                    } else if (evento.mouse.x >= xBotao + 180 && evento.mouse.x <= xBotao + 430) {
                        situacao = 1;
                        situacaoAux = 1;
                    }
                    al_rest(timeSleep);
                }
            }

            if (situacao == 7 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.x >= xBotao && evento.mouse.x < xBotao + 280) {
                    if (evento.mouse.y >= yBotao && evento.mouse.y <= yBotao + 70) {
                        situacao = situacaoAux;
                    } else if (evento.mouse.y >= yBotao + 90 && evento.mouse.y <= yBotao + 160) {

                    } else if (evento.mouse.y >= yBotao + 180 && evento.mouse.y <= yBotao + 250) {
                        situacao = 1;
                        situacaoAux = 1;
                    }
                }
            }
        }
        switch (situacao)
        {
        case 1:  
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5, ALLEGRO_ALIGN_CENTER, "Surakarta");

            al_draw_rectangle(xBotao, yBotao, xBotao + 280, yBotao + 70, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 70, ALLEGRO_ALIGN_CENTER, "Jogar jxj");

            al_draw_rectangle(xBotao, yBotao + 90, xBotao + 280, yBotao + 160, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 160, ALLEGRO_ALIGN_CENTER, "Jogar jxpc");

            al_draw_rectangle(xBotao, yBotao + 180, xBotao + 280, yBotao + 250, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 250, ALLEGRO_ALIGN_CENTER, "Ajuda");

            al_draw_rectangle(xBotao, yBotao + 270, xBotao + 280, yBotao + 340, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 340, ALLEGRO_ALIGN_CENTER, "Historico");

            al_draw_rectangle(xBotao, yBotao + 360, xBotao + 280, yBotao + 430, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 430, ALLEGRO_ALIGN_CENTER, "Sair");

            al_flip_display();
            break;
        case 2:    
            exibirJogo(jogo, podeAndarPosicoes, podeComerArcoPPosicoes, podeComerArcoGPosicoes, movDica, tabuleiro, font, horas, minutos, segundos, turno, corTrasparente, vezDoComputador, situacaoDJogo, &podeJogar, totDicasV, totDicasA, dica);
            al_flip_display();
            jogadaPossivel(&podeAndarPosicoes, &podeComerArcoPPosicoes, &podeComerArcoGPosicoes, vetL, jogo, pecaEscolhida, podeJogar, &situacaoDJogo);           
            break;
        case 3:  
            exibirJogo(jogo, podeAndarPosicoes, podeComerArcoPPosicoes, podeComerArcoGPosicoes, movDica, tabuleiro, font, horas, minutos, segundos, turno, corTrasparente, vezDoComputador, situacaoDJogo, &podeJogar, totDicasV, totDicasA, dica);
            al_flip_display();
            if (!vezDoComputador) {
                jogadaPossivel(&podeAndarPosicoes, &podeComerArcoPPosicoes, &podeComerArcoGPosicoes, vetL, jogo, pecaEscolhida, podeJogar, &situacaoDJogo);
            } else {
                if (tempoDeEspera > 1) {
                    inicializarStruct(&jogadaDoComputador, jogo);
                    op = rand() % 2;
                    if (op == 1) {
                        descobrirMovimentoPossivel(jogo, &jogadaDoComputador, &matou, dica, 'B');
                    } else {
                        descobrirMovimentoPossivelOp2(jogo, &jogadaDoComputador, &matou, dica, 'B');
                    }
                    movimento (jogo, jogadaDoComputador.i[1], jogadaDoComputador.j[1], jogadaDoComputador.i[0], jogadaDoComputador.j[0]);
                    if (matou == 1) {
                        printf("Rodada: %d, Turno: %s, A peca %c%d capturou a peca em %c%d\n", rodada, "Azul", vetColunas[jogadaDoComputador.j[1]], jogadaDoComputador.i[1], vetColunas[jogadaDoComputador.j[0]], jogadaDoComputador.i[0]);
                        totPecasV--;
                        matou = 0;
                        if (totPecasV == 0) {
                            situacao = 6;
                            turno = 'B';
                        }
                    } else {
                        printf("Rodada: %d, Turno: %s, A peca %c%d foi para %c%d\n", rodada, "Azul", vetColunas[jogadaDoComputador.j[1]], jogadaDoComputador.i[1], vetColunas[jogadaDoComputador.j[0]], jogadaDoComputador.i[0]);
                    }
                    rodada++;
                    vezDoComputador = 0;
                    tempoDeEspera = 0;
                }
            }       
            break;
        case 4:
            switch (pagAjuda) {
                case 1:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 - 100, ALLEGRO_ALIGN_CENTER, "O que e surakarta?");
                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5, ALLEGRO_ALIGN_LEFT, "Surakarta e um jogo de tabuleiro, para 2 pessoas. O jogo possui algumas caracteristicas comuns com o"); 
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 20, ALLEGRO_ALIGN_LEFT, "xadrez, como as pecas se moverem como o rei (horizontal, vertical, diagonal, mas apenas uma casa por lance)");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 40, ALLEGRO_ALIGN_LEFT, "e a captura ser por substituicao, ou seja, a peca que captura move-se para a casa da peca capturada. Porem, o ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 60, ALLEGRO_ALIGN_LEFT, "criterio exigido para que uma captura seja permitida e original, conforme sera explicado mais adiante.");

                    al_draw_circle(50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(30, ALTURA_TELA - 50, 70, ALTURA_TELA - 30, 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));
                    al_draw_circle(LARGURA_TELA - 50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(LARGURA_TELA - 30, ALTURA_TELA - 50, LARGURA_TELA - 70, ALTURA_TELA - 30, LARGURA_TELA - 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));

                    al_flip_display();
                    break;
                case 2:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 - 100, ALLEGRO_ALIGN_CENTER, "Tabuleiro");

                    al_draw_bitmap(tabuleiroExemplo, LARGURA_TELA / 2 - 110, ALTURA_TELA / 5 - 30, 0);

                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5 + 220, ALLEGRO_ALIGN_LEFT, "O jogo e composto por um tabuleiro (matriz 6x6) que possui dois circuitos de 3/4 de circunferencia (circuito"); 
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 240, ALLEGRO_ALIGN_LEFT, "interno e externo) em cada um dos quatro cantos do tabuleiro, e cujo percurso e obrigatorio no momento da ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 260, ALLEGRO_ALIGN_LEFT, "captura. Cada jogador dispoe inicialmente de 12 pecas. A posicao inicial e a que se ve na imagem acima. As pecas ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 280, ALLEGRO_ALIGN_LEFT, "sao posicionadas nas intersecoes das linhas (pontos) e nao no centro dos quadrados por elas formados.");

                    al_draw_circle(50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(30, ALTURA_TELA - 50, 70, ALTURA_TELA - 30, 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));
                    al_draw_circle(LARGURA_TELA - 50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(LARGURA_TELA - 30, ALTURA_TELA - 50, LARGURA_TELA - 70, ALTURA_TELA - 30, LARGURA_TELA - 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));

                    al_flip_display();
                    break;
                case 3:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 - 100, ALLEGRO_ALIGN_CENTER, "O Jogo");

                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5, ALLEGRO_ALIGN_LEFT, "O objetivo do jogo e capturar todas as pecas do adversario ou ter um maior numero de pecas caso mais"); 
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 20, ALLEGRO_ALIGN_LEFT, "nenhuma peca puder ser capturada.");
                    
                    al_draw_circle(50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(30, ALTURA_TELA - 50, 70, ALTURA_TELA - 30, 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));
                    al_draw_circle(LARGURA_TELA - 50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(LARGURA_TELA - 30, ALTURA_TELA - 50, LARGURA_TELA - 70, ALTURA_TELA - 30, LARGURA_TELA - 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));

                    al_flip_display();
                    break;
                case 4:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 - 100, ALLEGRO_ALIGN_CENTER, "Movimento");
                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5, ALLEGRO_ALIGN_LEFT, "Os adversarios se alternam fazendo um lance por vez. O movimento de um jogador consiste em andar com uma de suas"); 
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 20, ALLEGRO_ALIGN_LEFT, "pecas, apenas uma casa por vez, em qualquer direcao, na horizontal, vertical, diagonal, para frente ou para ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 40, ALLEGRO_ALIGN_LEFT, "tras, porem nao e possivel caminhar pelos circulos nos cantos do tabuleiro, a menos que seja para capturar");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 60, ALLEGRO_ALIGN_LEFT, "uma peca do adversario. Nao e permitido saltar unidades proprias ou adversarias. Tambem nao se pode invadir um");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 80, ALLEGRO_ALIGN_LEFT, "ponto ja ocupado, exceto para fazer uma captura, situacao em que a peca atacada e removida definitivamente do ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 100, ALLEGRO_ALIGN_LEFT, "tabuleiro.");

                    al_draw_circle(50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(30, ALTURA_TELA - 50, 70, ALTURA_TELA - 30, 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));
                    al_draw_circle(LARGURA_TELA - 50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(LARGURA_TELA - 30, ALTURA_TELA - 50, LARGURA_TELA - 70, ALTURA_TELA - 30, LARGURA_TELA - 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));

                    al_flip_display();
                    break;
                case 5:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 - 100, ALLEGRO_ALIGN_CENTER, "Captura");
                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5, ALLEGRO_ALIGN_LEFT, "Um movimento de captura consiste em percorrer um circuito interno ou externo em torno de pelo menos"); 
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 20, ALLEGRO_ALIGN_LEFT, "um dos oito cantos do tabuleiro, seguido de pousar em uma peca adversaria, capturando-a. AS pecas capturadas");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 40, ALLEGRO_ALIGN_LEFT, "Sao removidas do jogo.");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 30, ALTURA_TELA / 5 + 60, ALLEGRO_ALIGN_LEFT, "Assim, para caputar uma peca adversaria, e necessario mover a sua e coloca-la no lugar dela, passando");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 80, ALLEGRO_ALIGN_LEFT, "pelo menos uma vez, por um dos circuitos dos cantos do tabuleiro. Para a captura, e somente nessa hipotese, a ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 100, ALLEGRO_ALIGN_LEFT, "peca atacante pode percorrer qualquer numero de posicoes vagas, mas apenas no sentido horizontal ou vertical.");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 30, ALTURA_TELA / 5 + 120, ALLEGRO_ALIGN_LEFT, "Conforme mencionado, a peca atacante deve passar obrigatoriamente, pelo menos uma vez, por um dos oito ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 140, ALLEGRO_ALIGN_LEFT, "circuitos localizados nos cantos do tabuleiro, terminando o movimento na posicao onde se encontra a peca a ser");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 160, ALLEGRO_ALIGN_LEFT, "Capturada. Vale passar por mais de um circuito para fazer uma captura, mas, como nos movimentos normais, aqui");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 180, ALLEGRO_ALIGN_LEFT, "tambem nao se permitem saltos sobre pecas. E importante notar que as capturas nao sao obrigatorias. A Figura");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 200, ALLEGRO_ALIGN_LEFT, "a seguir mostra o movimento realizado na captura.");

                    al_draw_bitmap(capturaExemplo, LARGURA_TELA / 2 - 110, ALTURA_TELA / 5 + 230, 0);

                    al_draw_circle(50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(30, ALTURA_TELA - 50, 70, ALTURA_TELA - 30, 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));
                    al_draw_circle(LARGURA_TELA - 50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(LARGURA_TELA - 30, ALTURA_TELA - 50, LARGURA_TELA - 70, ALTURA_TELA - 30, LARGURA_TELA - 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));

                    al_flip_display();
                    break;
                case 6:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 - 100, ALLEGRO_ALIGN_CENTER, "Captura");
                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5, ALLEGRO_ALIGN_LEFT, "Os circuitos de canto sao usados somente ao fazer uma captura. A peca de captura entra e sai do circuito"); 
                    al_draw_text(fontTexto, al_map_rgb(100, 100, 100), 3, ALTURA_TELA / 5 + 20, ALLEGRO_ALIGN_LEFT, "atraves de uma linha grade tangente ao circulo. Qualquer numero de pontos desocupados pode ser percorrida");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 40, ALLEGRO_ALIGN_LEFT, "mais de uma vez durante a jornada da peca de captura. Somente posicoes desocupadas poderao ser percorridas.");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 30, ALTURA_TELA / 5 + 60, ALLEGRO_ALIGN_LEFT, "A figura a seguir ilustra um exemplo de captura. No exemplo, o tabuleiro esta com apenas tres pecas, duas ");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 80, ALLEGRO_ALIGN_LEFT, "brancas, localizadas em B1 e E2, e uma preta, situada em E3, Se fosse a vez das pretas, a peca em E3 poderia subir, dar a volta pelo circuito interno superior");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 100, ALLEGRO_ALIGN_LEFT, "volta pelo circuito interno superior direito, prosseguir pela linha 5, passar pelo circuito interno superior");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 120, ALLEGRO_ALIGN_LEFT, "esquerdo, e descer pela coluna B, capturando a peca em B1. Nao daria para fazer a captura atraves do circuito inferior");
                    al_draw_text(fontTexto, al_map_rgb(100,100,100), 3, ALTURA_TELA / 5 + 140, ALLEGRO_ALIGN_LEFT, "direito, pois o trajeto  estaria obstruido pela peca em E2.");

                    al_draw_bitmap(capturaExemplo2, LARGURA_TELA / 2 - 110, ALTURA_TELA / 5 + 170, 0);

                    al_draw_circle(50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(30, ALTURA_TELA - 50, 70, ALTURA_TELA - 30, 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));
                    al_draw_circle(LARGURA_TELA - 50, ALTURA_TELA - 50, 40, al_map_rgb(0, 0, 0), 3);
                    al_draw_filled_triangle(LARGURA_TELA - 30, ALTURA_TELA - 50, LARGURA_TELA - 70, ALTURA_TELA - 30, LARGURA_TELA - 70, ALTURA_TELA - 70, al_map_rgb(0, 0, 0));

                    al_flip_display();
                    break;
                default:
                    al_clear_to_color(al_map_rgb(255, 0, 0));
                    al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2, ALLEGRO_ALIGN_CENTER, "Erro");
                    al_flip_display();
                    break;
            }
            break;
        case 5:
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 25, ALLEGRO_ALIGN_CENTER, "Historico");
            al_draw_text(font, al_map_rgb(0, 0, 0), 100, ALTURA_TELA / 5, ALLEGRO_ALIGN_LEFT, "Jogador x Jogador");
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA - 50, ALTURA_TELA / 5, ALLEGRO_ALIGN_RIGHT, "Jogador x Computador");
            al_draw_line(70, ALTURA_TELA / 5 + 35, LARGURA_TELA / 2 - 85, ALTURA_TELA / 5 + 35, al_map_rgb(0, 0, 0), 4);
            al_draw_line(LARGURA_TELA - 585, ALTURA_TELA / 5 + 35, LARGURA_TELA - 35, ALTURA_TELA / 5 + 35, al_map_rgb(0, 0, 0), 4);
            al_draw_line(LARGURA_TELA / 2, ALTURA_TELA / 25 + 80, LARGURA_TELA / 2, ALTURA_TELA - 100, al_map_rgb(0, 0, 0), 4);
            for (int i = 0; i < 5; i++) {
                al_draw_textf(font, al_map_rgb(100, 100, 100), 30, ALTURA_TELA / 5 + 70 + 80 * i, ALLEGRO_ALIGN_LEFT, "%d.", i + 1);
                al_draw_textf(font, al_map_rgb(100, 100, 100), LARGURA_TELA / 2 + 30, ALTURA_TELA / 5 + 70 + 80 * i, ALLEGRO_ALIGN_LEFT, "%d.", i + 1);
            }

            al_draw_circle(50, 50, 40, al_map_rgb(0, 0, 0), 3);
            al_draw_line(30, 30, 70, 70, al_map_rgb(0, 0, 0), 3);
            al_draw_line(30, 70, 70, 30, al_map_rgb(0, 0, 0), 3);
            al_flip_display();
            break;
        case 6:
            al_clear_to_color(al_map_rgb(255, 255, 255));
            if (turno == 'R') {
                al_draw_text(font, al_map_rgb(255, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5, ALLEGRO_ALIGN_CENTER, "Vermelho venceu!");
            } else {
                al_draw_text(font, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, ALTURA_TELA / 5, ALLEGRO_ALIGN_CENTER, "Azul venceu!");
            }
            al_draw_textf(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5 + 50, ALLEGRO_ALIGN_CENTER, "Tempo: %02d:%02d:%02d", horas, minutos, segundos);
            
            al_draw_rectangle(xBotao - 180, yBotao + 20, xBotao + 70, yBotao + 100, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), xBotao - 50, yBotao + 45, ALLEGRO_ALIGN_CENTER, "Recomecar");

            al_draw_rectangle(xBotao + 180, yBotao + 20, xBotao + 430, yBotao + 100, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), xBotao + 310, yBotao + 45, ALLEGRO_ALIGN_CENTER, "Menu");
            
            al_flip_display();
            break;
        case 7:
            al_clear_to_color(al_map_rgb(255, 255, 255));
            exibirJogo(jogo, podeAndarPosicoes, podeComerArcoPPosicoes, podeComerArcoGPosicoes, movDica, tabuleiro, font, horas, minutos, segundos, turno, corTrasparente, vezDoComputador, situacaoDJogo, &podeJogar, totDicasV, totDicasA, dica);
            al_draw_filled_rectangle(0, 0, LARGURA_TELA, ALTURA_TELA, corBrancoTrasparente);
            al_draw_text(fontTitulo, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5, ALLEGRO_ALIGN_CENTER, "Jogo Pausado");

            al_draw_rectangle(xBotao, yBotao, xBotao + 280, yBotao + 70, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 70, ALLEGRO_ALIGN_CENTER, "Voltar");

            al_draw_rectangle(xBotao, yBotao + 90, xBotao + 280, yBotao + 160, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 160, ALLEGRO_ALIGN_CENTER, "Salvar");

            al_draw_rectangle(xBotao, yBotao + 180, xBotao + 280, yBotao + 250, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 250, ALLEGRO_ALIGN_CENTER, "Menu");
            al_flip_display();
            break;
        default:
            al_clear_to_color(al_map_rgb(255, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2, ALLEGRO_ALIGN_CENTER, "Erro");
            al_flip_display();
            break;
        }
        
    }
    al_destroy_display(janela);
    al_destroy_bitmap(tabuleiro);
    al_destroy_event_queue(fila_eventos);
    al_destroy_font(font);
    al_destroy_timer(timer);
    return 0;
}