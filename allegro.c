#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "logicadojogo.h"

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

void atualizarTabuleiro (Peca jogo[TAM][TAM]) {
    for (int i = 0, y = 0; i < TAM; i++, y+=67) {
        for (int j = 0, x = 0; j < TAM; j++, x+=87) {
            if (jogo[i][j].time == 'R') {
                al_draw_filled_circle(175+x, 140+y, 30, al_map_rgb(255, 0, 0));
                jogo[i][j].x = 175+x;
                jogo[i][j].y = 140+y;
                jogo[i][j].raio = 30;
            } else if (jogo[i][j].time == 'B') {
                al_draw_filled_circle(175+x, 140+y, 30, al_map_rgb(0, 0, 255));
                jogo[i][j].x = 175+x;
                jogo[i][j].y = 140+y;
                jogo[i][j].raio = 30;
            }
        }
    }
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

    int rodando = 1, situacao = 1, situacaoDJogo = 0;
    int xBotao = LARGURA_TELA / 2 - 100, yBotao = ALTURA_TELA / 4 + 50;
    Peca jogo[TAM][TAM];
    Peca pecaEscolhida;
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
                    // int i = (evento.mouse.y - 140) / 67;
                    // int j = (evento.mouse.x - 175) / 87;
                    int achou;
                    for (int i = 0; i < TAM; i++) {
                        for (int j = 0; j < TAM; j++) {
                            if (evento.mouse.x >= jogo[i][j].x - jogo[i][j].raio && evento.mouse.x <= jogo[i][j].x + jogo[i][j].raio && evento.mouse.y >= jogo[i][j].y - jogo[i][j].raio && evento.mouse.y <= jogo[i][j].y + jogo[i][j].raio) {
                                pecaEscolhida = jogo[i][j];
                                achou = 1;
                                i=6;
                                situacaoDJogo = 1;
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
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_scaled_bitmap(tabuleiro, 0, 0, al_get_bitmap_width(tabuleiro), al_get_bitmap_height(tabuleiro), 0, 0, 800, 600, 0);
            atualizarTabuleiro(jogo);
            al_flip_display();
            switch (situacaoDJogo)
            {
                // parei aqui
            case 1:
                inicializarStruct(&podeAndarPosicoes);
                podeAndar(jogo, pecaEscolhida, &podeAndarPosicoes);
                for (int i = 0; i < 8; i++) {
                if (podeAndarPosicoes.i[i] != -1 && podeAndarPosicoes.j[i] != -1) {
                    printf("Pode andar para: %d %d\n", podeAndarPosicoes.i[i], podeAndarPosicoes.j[i]);
                }
                }
                situacaoDJogo = 2;
                break;
            case 2:
                atualizarTabuleiro(jogo);
                for (int i = 0; i < 8; i++) {
                    printf("i = %d j = %d\n", podeAndarPosicoes.i[i], podeAndarPosicoes.j[i]);
                    if (podeAndarPosicoes.i[i] != -1 && podeAndarPosicoes.j[i] != -1) {
                        printf("desenhou i = %d j = %d\n", podeAndarPosicoes.i[i], podeAndarPosicoes.j[i]);
                        al_draw_filled_circle(175 + podeAndarPosicoes.i[i] * 87, 140 + podeAndarPosicoes.j[i] * 67, 30, al_map_rgb(0, 255, 0));
                    }
                }
                al_flip_display();
                scanf("%d", &situacaoDJogo);
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
