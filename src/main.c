#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "config.h"
#include "asteroide.h"
#include "tiro.h"
#include "placar.h"

#define TEMPO_FRAME_MS 50
#define ORIGEM_X 2
#define ORIGEM_Y 4

static void desenhar_na_arena(int x, int y, char c, screenColor cor) {
    screenGotoxy(ORIGEM_X + 1 + x, ORIGEM_Y + y);
    screenSetColor(cor, BLACK);
    printf("%c", c);
}

void desenhar_tela(int nave_x, Asteroide *lista, Tiro *tiros, int pontos, int vidas) {
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(ORIGEM_X + 10, 0);
    printf("ÓRBITA EM CAOS");

    screenSetColor(WHITE, BLACK);
    screenGotoxy(ORIGEM_X, 2);
    printf("Pontuação: %-6d  Meta: %d  Vidas: %d", pontos, META_VITORIA, vidas);

    for (int i = 0; i < LINHAS; i++) {
        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(ORIGEM_X, ORIGEM_Y + i);
        printf("|%*s|", COLUNAS, "");
    }

    for (Asteroide *a = lista; a != NULL; a = a->next) {
        if (a->y >= 0 && a->y < LINHAS) {
            desenhar_na_arena(a->x, a->y, 'O', BROWN);
        }
    }

    for (Tiro *t = tiros; t != NULL; t = t->next) {
        if (t->y >= 0 && t->y < LINHAS) {
            desenhar_na_arena(t->x, t->y, '!', LIGHTRED);
        }
    }

    desenhar_na_arena(nave_x, LINHA_NAVE, '^', LIGHTCYAN);

    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(ORIGEM_X, ORIGEM_Y + LINHAS + 1);
    printf("A = Esquerda | D = Direita | ESPACO = Atirar | Q = Sair");

    screenUpdate();
}

int main(void) {
    int nave_x = COLUNAS / 2;
    int vidas = 3;
    int pontos = 0;
    int frame = 0;
    int jogando = 1;

    Asteroide *lista = NULL;
    Tiro *tiros = NULL;

    srand(time(NULL));
    screenInit(0);
    keyboardInit();
    timerInit(TEMPO_FRAME_MS);

    desenhar_tela(nave_x, lista, tiros, pontos, vidas);

    while (jogando && vidas > 0 && pontos < META_VITORIA) {
        if (keyhit()) {
            int tecla = readch();

            if ((tecla == 'a' || tecla == 'A') && nave_x > 0) {
                nave_x--;
            }

            if ((tecla == 'd' || tecla == 'D') && nave_x < COLUNAS - 1) {
                nave_x++;
            }

            if (tecla == ' ') {
                adicionar_tiro(&tiros, nave_x, LINHA_NAVE - 1);
            }

            if (tecla == 'q' || tecla == 'Q') {
                jogando = 0;
            }
        }

        if (timerTimeOver()) {
            if (frame % 15 == 0) {
                adicionar_asteroide(&lista);
            }

            atualizar_asteroides(&lista, &vidas, nave_x);
            verificar_colisoes(&tiros, &lista, &pontos);
            atualizar_tiros(&tiros);
            verificar_colisoes(&tiros, &lista, &pontos);

            desenhar_tela(nave_x, lista, tiros, pontos, vidas);
            frame++;
        }
    }

    liberar_asteroides(lista);
    liberar_tiros(tiros);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    if (pontos >= META_VITORIA) {
        printf("=====================================\n");
        printf("            VITÓRIA!\n");
        printf(" Você destruiu %d meteoros!\n", pontos / PONTOS_POR_ASTEROIDE);
        printf(" Pontuação final: %d\n", pontos);
        printf("=====================================\n");
    } else if (vidas <= 0) {
        printf("=====================================\n");
        printf("            GAME OVER!\n");
        printf(" Sua nave foi destruída.\n");
        printf(" Pontuação final: %d\n", pontos);
        printf("=====================================\n");
    } else {
        printf("Jogo encerrado pelo jogador. Pontuação final: %d\n", pontos);
    }

    int top[MAX_SCORES];
    int total = 0;
    int pos = registrar_score(pontos, top, &total);

    mostrar_ranking(top, total, pos);

    return 0;
}
