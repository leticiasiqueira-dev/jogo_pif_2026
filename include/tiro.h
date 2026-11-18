#ifndef TIRO_H
#define TIRO_H

#include "asteroide.h"   // verificar_colisoes usa Asteroide

typedef struct Tiro {
    int x;
    int y;
    struct Tiro *next;
} Tiro;

Tiro *criar_tiro(int x, int y);
void adicionar_tiro(Tiro **lista, int x, int y);
void atualizar_tiros(Tiro **lista);
void verificar_colisoes(Tiro **tiros, Asteroide **asteroides, int *pontos);
void liberar_tiros(Tiro *lista);

#endif