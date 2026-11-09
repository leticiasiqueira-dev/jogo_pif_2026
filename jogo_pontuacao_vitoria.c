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
#define PONTOS_POR_ASTEROIDE 100
#define META_VITORIA 1000

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

typedef struct Tiro {
    int x;
    int y;
    struct Tiro *next;
} Tiro;

Tiro *criar_tiro(int x, int y) {
    Tiro *novo = malloc(sizeof(Tiro));
    if (novo == NULL) return NULL;
    novo->x = x;
    novo->y = y;
    novo->next = NULL;
    return novo;
}

void adicionar_tiro(Tiro **lista, int x, int y) {
    Tiro *novo = criar_tiro(x, y);
    if (novo == NULL) return;
    novo->next = *lista;
    *lista = novo;
}

void atualizar_tiros(Tiro **lista) {
    Tiro **atual = lista;
    while (*atual != NULL) {
        (*atual)->y--; // Um passo para cima por tick
        if ((*atual)->y < 0) {
            Tiro *remover = *atual;
            *atual = remover->next;
            free(remover);
        } else {
            atual = &(*atual)->next;
        }
    }
}

void verificar_colisoes(Tiro **tiros, Asteroide **asteroides, int *pontos) {
    Tiro **t = tiros;
    while (*t != NULL) {
        Asteroide **a = asteroides;
        int acertou = 0;
        while (*a != NULL) {
            if ((*t)->x == (*a)->x && (*t)->y == (*a)->y) {
                Tiro *tiro_atingiu = *t;
                Asteroide *asteroide_atingido = *a;
                *t = tiro_atingiu->next;
                *a = asteroide_atingido->next;
                free(tiro_atingiu);
                free(asteroide_atingido);
                *pontos += PONTOS_POR_ASTEROIDE;
                acertou = 1;
                break;
            }
            a = &(*a)->next;
        }
        if (!acertou) t = &(*t)->next;
    }
}

void liberar_tiros(Tiro *lista) {
    while (lista != NULL) {
        Tiro *proximo = lista->next;
        free(lista);
        lista = proximo;
    }
}

#ifdef _WIN32
void configurar_terminal(void) {
    SetConsoleOutputCP(CP_UTF8);

    HANDLE terminal = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo;

    if (GetConsoleMode(terminal, &modo)) {
        SetConsoleMode(terminal, modo | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}
void restaurar_terminal(void) { }
void voltar_cursor(void) {
    printf("\033[H\033[J");
    fflush(stdout);
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

    return 0;
}
