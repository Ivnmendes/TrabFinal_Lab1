#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//#include "logicadojogo.h"

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

// código teste, apagar a partir daqui até o luan 7
#define TAM 6
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
// Luan 7
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

void atualizarTabuleiro (Peca jogo[TAM][TAM], ALLEGRO_BITMAP *tabuleiro) {
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
    al_flip_display();
}

int main()
{
    // Variaveis da janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_BITMAP *tabuleiro = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

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

    al_install_mouse();
    if (!al_install_mouse()) {
        printf("Falha ao inicializar o mouse");
        return -1;
    }


    // Criando a janela principal
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela) {
        printf("Falha ao criar a janela");
        return -1;
    }

    // Carregando a fonte
    //font = al_load_font("./OptimusPrinceps.ttf", 36, 0);
    font = al_create_builtin_font();
    if (!font) {
        printf("Falha ao carregar \"font.ttf\".\n");
        return -1;
    }

    // Carregando a imagem do tabuleiro
    tabuleiro = al_load_bitmap("./tabuleiro.png");
    if (!tabuleiro) {
        printf("Falha ao carregar \"tabuleiro.png\".\n");
        return -1;
    }

    // Criando a fila de eventos
    fila_eventos = al_create_event_queue();
    if (!fila_eventos) {
        printf("Falha ao criar fila de eventos.");
        return -1;
    }


    // Registrando os eventos da janela principal e do mouse
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    // Variaveis do jogo - flags
    int rodando = 1, situacao = 1, situacaoDJogo = 0;
    
    // Constante da tela, botões e posicionamentos
    int xBotao = LARGURA_TELA / 2 - 100, yBotao = ALTURA_TELA / 4 + 50;
    ALLEGRO_COLOR corVermelhoPeca = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR corAzulPeca = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR corTrasparente = al_map_rgba(255, 200, 0, 100);
    
    // Variáveis da lógica do jogo
    char turno = 'R';
    int podeJogar = 0;
    Peca jogo[TAM][TAM];
    Peca pecaEscolhida;
    Posicao podeAndarPosicoes;
    Posicao podeComerArcoGPosicoes;
    Posicao podeComerArcoPPosicoes;


    int lixo;

    while (rodando) {
        while (!al_is_event_queue_empty(fila_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }

            if (situacao == 1 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 200 && evento.mouse.y >= yBotao && evento.mouse.y <= yBotao + 50) {
                    situacao = 2;
                    iniciarTabuleiro(jogo);
                }
                else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 200 && evento.mouse.y >= yBotao + 80 && evento.mouse.y <= yBotao + 130) {
                    situacao = 3;
                }
                else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 200 && evento.mouse.y >= yBotao + 160 && evento.mouse.y <= yBotao + 210) {
                    situacao = 4;
                }
                else if (evento.mouse.x >= xBotao && evento.mouse.x <= xBotao + 200 && evento.mouse.y >= yBotao + 230 && evento.mouse.y <= yBotao + 280) {
                    situacao = 5;
                }
            }
            if (situacao == 2 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (evento.mouse.x >= 0 && evento.mouse.x <= 800 && evento.mouse.y >= 0 && evento.mouse.y <= 600) {
                    int i = (evento.mouse.y - 140) / 67;
                    int j = (evento.mouse.x - 175) / 87;
                    int achou;
                    for (int i = 0; i < TAM; i++) {
                        for (int j = 0; j < TAM; j++) {
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio && jogo[i][j].time == turno) {
                                pecaEscolhida.i = jogo[i][j].i;
                                pecaEscolhida.j = jogo[i][j].j;
                                pecaEscolhida.time = jogo[i][j].time;
                                achou = 1;
                                i=6;
                                situacaoDJogo = 1;
                                atualizarTabuleiro(jogo, tabuleiro);
                                inicializarStruct(&podeAndarPosicoes, jogo);
                                podeAndar(jogo, pecaEscolhida, &podeAndarPosicoes);
                                break;
                            } else {
                                situacaoDJogo = 0;
                                achou = 0;
                            }
                        }
                    }
                    
                    if (achou) {
                        printf("Peca escolhida: %c %d %d\n", pecaEscolhida.time, pecaEscolhida.i, pecaEscolhida.j);
                    } else {
                        printf("Nao achou\n");
                    }
                }
            }
            if (situacao == 2 && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (podeJogar == 1 && evento.mouse.x >= 0 && evento.mouse.x <= 800 && evento.mouse.y >= 0 && evento.mouse.y <= 600) {
                    for (int k = 0; k < 8; k++) {
                        if (podeAndarPosicoes.i[k] != -1) {
                            int i = podeAndarPosicoes.i[k];
                            int j = podeAndarPosicoes.j[k];
                            printf("jogo %d %d, x = %d, y = %d\n", jogo[i][j].i, jogo[i][j].j, jogo[i][j].x, jogo[i][j].y);
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio) {
                                printf("aqui 2\n");
                                jogo[pecaEscolhida.i][pecaEscolhida.j].time = '-';
                                jogo[i][j].time = pecaEscolhida.time;
                                turno = (turno == 'R') ? 'B' : 'R';
                                situacaoDJogo = 0;
                                podeJogar = 0;
                                // CONTINUAR DAQUI
                                break;
                            }
                        }
                    }
                }
            }
        }
        switch (situacao)
        {
        case 1:  
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 5, ALLEGRO_ALIGN_CENTER, "Surakarta");
            al_draw_rectangle(xBotao, ALTURA_TELA / 4 + 50, xBotao + 200, ALTURA_TELA / 4 + 100, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 70, ALLEGRO_ALIGN_CENTER, "Jogar jxj");
            al_draw_rectangle(xBotao, ALTURA_TELA / 4 + 130, xBotao + 200, ALTURA_TELA / 4 + 180, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 150, ALLEGRO_ALIGN_CENTER, "Jogar jxpc");
            al_draw_rectangle(xBotao, ALTURA_TELA / 4 + 210, xBotao + 200, ALTURA_TELA / 4 + 260, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 230, ALLEGRO_ALIGN_CENTER, "Ajuda");
            al_draw_rectangle(xBotao, ALTURA_TELA / 4 + 290, xBotao + 200, ALTURA_TELA / 4 + 340, al_map_rgb(0, 0, 0), 2);
            al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 4 + 310, ALLEGRO_ALIGN_CENTER, "Historico");
            al_flip_display();
            break;
        case 2:
            if (podeJogar != 1) {
                atualizarTabuleiro(jogo, tabuleiro);
                printf("Aqui turno: %c\n", turno);
            }
            switch (situacaoDJogo)
            {
                case 1:
                    inicializarStruct(&podeAndarPosicoes, jogo);
                    podeAndar(jogo, pecaEscolhida, &podeAndarPosicoes);
                    for (int i = 0; i < 8; i++) {
                        printf("i = %d j = %d\n", podeAndarPosicoes.i[i], podeAndarPosicoes.j[i]);
                        if (podeAndarPosicoes.i[i] != -1 && podeAndarPosicoes.j[i] != -1) {
                            al_draw_filled_circle(175 + podeAndarPosicoes.j[i] * 87, 140 + podeAndarPosicoes.i[i] * 67, 30, corTrasparente);
                            podeJogar = 1;
                        }
                    }
                    if (podeJogar) {
                        situacaoDJogo = 3;
                    } else {
                        situacaoDJogo = 0;
                    }
                    al_flip_display();
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;
        default:
            al_clear_to_color(al_map_rgb(255, 0, 0));
            al_flip_display();
            break;
        }
        
    }
    al_destroy_display(janela);
    al_destroy_bitmap(tabuleiro);
    al_destroy_event_queue(fila_eventos);
    al_destroy_font(font);
    return 0;
}
