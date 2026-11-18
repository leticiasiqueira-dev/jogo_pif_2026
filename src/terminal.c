#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

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
