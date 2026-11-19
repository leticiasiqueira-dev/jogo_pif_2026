#include <stdlib.h>
#include "config.h"
#include "asteroide.h"

Asteroide *criar_asteroide(void){
    Asteroide *a = malloc(sizeof(Asteroide));

    if (a == NULL){
        return NULL;
    }

    a->x = rand() % COLUNAS;
    a->y = 0;
    a->velocidade = 1 + rand() % VELOCIDADE_MAX_ASTEROIDE;
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

        int dx = abs(atual->x - nave_x);

        if((atual->y == LINHA_NAVE && dx == 0) || (atual->y == LINHA_NAVE + 1 && dx <= NAVE_META)){
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
