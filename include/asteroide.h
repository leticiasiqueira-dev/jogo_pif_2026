#ifndef ASTEROIDE_H
#define ASTEROIDE_H

typedef struct {
    int x;
    int y;
    int velocidade;
    int contador;
    struct Asteroide *next;
} Asteroide;

Asteroide *criar_asteroide(void);
void adicionar_asteroide(Asteroide **lista);
void atualizar_asteroides(Asteroide **lista, int *vidas, int nave_x);
void liberar_asteroides(Asteroide *lista);

#endif