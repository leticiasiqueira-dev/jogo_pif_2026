#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "asteroide.h"
#include "tiro.h"
#include "terminal.h"
#include "placar.h"

void desenhar_tela(int nave_x, Asteroide *lista, Tiro *tiros, int pontos, int vidas){
    char tela[LINHAS][COLUNAS];
    char saida[2048];
    int n = 0;

    for (int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            tela[i][j] = ' ';
        }
    }

    for (Asteroide *a = lista; a != NULL; a = a->next){
        if (a->y >= 0 && a->y < LINHAS){
            tela[a->y][a->x] = 'O';
        }
    }

    for (Tiro *t = tiros; t != NULL; t = t->next) {
        if (t->y >= 0 && t->y < LINHAS) tela[t->y][t->x] = '!';
    }

    tela[LINHA_NAVE][nave_x] = '^';

    n += sprintf(saida + n, "          ÓRBITA EM CAOS\n\n");
    n += sprintf(saida + n, "Pontuação: %-6d  Meta: %d  Vidas: %d\n\n", pontos, META_VITORIA, vidas);

    for(int i = 0; i < LINHAS; i++){
        saida[n++] = '|';

        for(int j = 0; j < COLUNAS; j++){
            saida[n++] = tela[i][j];
        }
        n += sprintf(saida + n, "|\n");
    }
    n += sprintf(saida + n, "\nA = Esquerda | D = Direita | ESPACO = Atirar | Q = Sair\n");

    saida[n] = '\0';
    fputs(saida, stdout);
}

int main(void){
    int nave_x = 15, vidas = 3, pontos = 0, frame = 0, jogando = 1;
    Asteroide *lista = NULL;
    Tiro *tiros = NULL;

    configurar_terminal();
    srand(time(NULL));
    esconder_cursor();
    limpar_tela();

    while (jogando && vidas > 0 && pontos < META_VITORIA){

        if (tecla_disponivel()){
            int tecla = ler_tecla();

            if((tecla == 'a' || tecla == 'A') && nave_x > 0){
                nave_x--;
            }
            if((tecla == 'd' || tecla == 'D') && nave_x < 30){
                nave_x++;
            }
            if (tecla == ' ') {
                adicionar_tiro(&tiros, nave_x, LINHA_NAVE - 1);
            }
            if(tecla == 'q' || tecla == 'Q'){
                jogando = 0;
            }
        }

        if (frame % 15 == 0){
            adicionar_asteroide(&lista);
        }

        atualizar_asteroides(&lista, &vidas, nave_x);
        verificar_colisoes(&tiros, &lista, &pontos);
        atualizar_tiros(&tiros);
        verificar_colisoes(&tiros, &lista, &pontos);

        voltar_cursor();

        desenhar_tela(nave_x, lista, tiros, pontos, vidas);

        frame++;
        if (pontos >= META_VITORIA || vidas <= 0 || !jogando) break;
        esperar_frame();

    }

    liberar_asteroides(lista);
    liberar_tiros(tiros);
    limpar_tela();
    restaurar_terminal();

    if (pontos >= META_VITORIA) {
        printf("=====================================\n");
        printf("            VITORIA!\n");
        printf(" Voce destruiu %d meteoros!\n", pontos / PONTOS_POR_ASTEROIDE);
        printf(" Pontuacao final: %d\n", pontos);
        printf("=====================================\n");
    } else if (vidas <= 0) {
        printf("=====================================\n");
        printf("            GAME OVER!\n");
        printf(" Sua nave foi destruida.\n");
        printf(" Pontuacao final: %d\n", pontos);
        printf("=====================================\n");
    } else {
        printf("Jogo encerrado pelo jogador. Pontuacao final: %d\n", pontos);
    }
    
    int top[MAX_SCORES];
    int total = 0;
    int pos = registrar_score(pontos, top, &total);
    mostrar_ranking(top, total, pos);

    return 0;
}
