#include <stdlib.h>
#include "config.h"
#include "tiro.h"

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