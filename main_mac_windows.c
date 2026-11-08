#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif
#include <stdlib.h>
#include <time.h>
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

#ifdef _WIN32
void configurar_terminal(void) { SetConsoleOutputCP(CP_UTF8); }
void restaurar_terminal(void) { }
void voltar_cursor(void) {
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void esconder_cursor(void) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
int tecla_disponivel(void) { return _kbhit(); }
int ler_tecla(void) { return _getch(); }
void esperar_frame(void) { Sleep(50); }
void limpar_tela(void) { system("cls"); }
#else
static struct termios terminal_original;
static int terminal_configurado = 0;
void restaurar_terminal(void) {
    if (terminal_configurado) tcsetattr(STDIN_FILENO, TCSANOW, &terminal_original);
    printf("\033[?25h\n");
    fflush(stdout);
}
void configurar_terminal(void) {
    if (tcgetattr(STDIN_FILENO, &terminal_original) == 0) {
        struct termios terminal = terminal_original;
        terminal.c_lflag &= ~(ICANON | ECHO);
        terminal.c_cc[VMIN] = 0;
        terminal.c_cc[VTIME] = 0;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == 0)
            terminal_configurado = 1;
    }
    atexit(restaurar_terminal);
}
void voltar_cursor(void) { printf("\033[H"); }
void esconder_cursor(void) { printf("\033[?25l"); }
int tecla_disponivel(void) {
    fd_set conjunto;
    struct timeval espera = {0, 0};
    FD_ZERO(&conjunto);
    FD_SET(STDIN_FILENO, &conjunto);
    return select(STDIN_FILENO + 1, &conjunto, NULL, NULL, &espera) > 0;
}
int ler_tecla(void) {
    unsigned char tecla;
    return read(STDIN_FILENO, &tecla, 1) == 1 ? tecla : -1;
}
void esperar_frame(void) {
    struct timeval intervalo = {0, 50000};
    select(0, NULL, NULL, NULL, &intervalo);
}
void limpar_tela(void) { printf("\033[2J\033[H"); }
#endif

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

int main(void){
    int nave_x = 15, vidas = 3, pontos = 0, frame = 0, jogando = 1;
    Asteroide *lista = NULL;

    configurar_terminal();
    srand(time(NULL));
    esconder_cursor();
    limpar_tela();

    while (jogando && vidas > 0){

        if (tecla_disponivel()){
            int tecla = ler_tecla();

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
        esperar_frame();

    }

    liberar_asteroides(lista);
    restaurar_terminal();

    if(vidas <= 0){
        printf("\nGAME OVER! Pontuação final: %d\n", pontos);
    }else{
        printf("\nJogo encerrado. Pontuação final: %d\n", pontos);
    }

    return 0;
}
