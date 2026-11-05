#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define LINHAS 9
#define COLUNAS 31
#define LINHA_NAVE 6

typedef struct Asteroide {
    int x;
    int y;
    int velocidade;
    int contador;
    struct Asteroide *next;
}Asteroide;

Asteroide *criar_asteroide(void){
    Asteroide *a = malloc(sizeof(Asteroide));

    if (a == NULL){
        return NULL;
    }

    a->x = rand() % COLUNAS;
    a->y = 0;
    a->velocidade = 1 + rand() % 4;
    a->contador = 0;
    a->next = NULL;

    return a;
}

void adicionar_asteroide(Asteroide **lista){
    Asteroide *novo = criar_asteroide();

    if (novo == NULL){
        return;
    }

    novo->next = *lista;
    *lista = novo;
}

void atualizar_asteroides(Asteroide **lista, int *vidas, int nave_x){
    Asteroide *atual = *lista;
    Asteroide *anterior = NULL;

    while(atual != NULL){
        atual->contador++;

        if(atual->contador >= atual->velocidade){
            atual->contador = 0;
            atual->y++;
        }

        int remover = 0;

        if(atual->y == LINHA_NAVE && atual->x == nave_x){
            (*vidas)--;
            remover = 1;
        }else if (atual->y >= LINHAS){
            remover = 1;
        }

        if (remover){
            Asteroide *lixo = atual;
            if (anterior == NULL){
                *lista = atual->next;
            }else{
                anterior->next = atual->next;
            }
            atual = atual->next;
            free(lixo);
        }else{
            anterior = atual;
            atual = atual->next;
        }
    }
}

void liberar_asteroides(Asteroide *lista){
    while(lista != NULL){
        Asteroide *next = lista->next;
        free(lista);
        lista = next;
    }
}

void voltar_cursor(void){
    COORD pos = {0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void esconder_cursor(void){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void desenhar_tela(int nave_x, Asteroide *lista, int pontos, int vidas){
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

    tela[LINHA_NAVE][nave_x] = '^';

    n += sprintf(saida + n, "          ÓRBITA EM CAOS\n\n");
    n += sprintf(saida + n, "Pontuação: %-6d            Vidas: %d\n\n", pontos, vidas);

    for(int i = 0; i < LINHAS; i++){
        saida[n++] = '|';

        for(int j = 0; j < COLUNAS; j++){
            saida[n++] = tela[i][j];
        }
        n += sprintf(saida + n, "|\n");
    }
    n += sprintf(saida + n, "\nA = Esquerda | D = Direita | Q = Sair\n");

    saida[n] = '\0';
    fputs(saida, stdout);
}

int main(){
    int nave_x = 15, vidas = 3, pontos = 0, frame = 0, jogando = 1;
    Asteroide *lista = NULL;

    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    esconder_cursor();
    system("cls");

    while (jogando && vidas > 0){

        if (_kbhit()){
            char tecla = _getch();

            if((tecla == 'a' || tecla == 'A') && nave_x > 0){
                nave_x--;
            }
            if((tecla == 'd' || tecla == 'D') && nave_x < 30){
                nave_x++;
            }
            if(tecla == 'q' || tecla == 'Q'){
                jogando = 0;
            }
        }

        if (frame % 15 == 0){
            adicionar_asteroide(&lista);
        }

        atualizar_asteroides(&lista, &vidas, nave_x);

        voltar_cursor();

        desenhar_tela(nave_x, lista, pontos, vidas);

        frame++;
        pontos++;
        Sleep(50);

    }

    liberar_asteroides(lista);

    if(vidas <= 0){
        printf("\nGAME OVER! Pontuação final: %d\n", pontos);
    }else{
        printf("\nJogo encerrado. Pontuação final: %d\n", pontos);
    }

    return 0;
}