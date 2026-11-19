#include <stdio.h>
#include "config.h"
#include "placar.h"

int carregar_scores(int scores[], int max){
    FILE *f = fopen(ARQUIVO_SCORES, "r");
    int n = 0;

    if(f==NULL){
        return 0;
    }

    while (n<max && fscanf(f, "%d", &scores[n]) == 1){
        n++;
    }
    fclose(f);
    return n;
}

void salvar_scores(int scores[], int n){
    FILE *f = fopen(ARQUIVO_SCORES, "w");

    if (f==NULL){
        printf("Aviso: não foi possível gravar %s\n", ARQUIVO_SCORES);
        return;
    }
    for(int i = 0; i<n; i++){
        fprintf(f, "%d\n", scores[i]);
    }
    fclose(f);
}

int registrar_score(int nova, int scores[], int *n){
    *n = carregar_scores(scores, MAX_SCORES);

    int pos = *n;
    while(pos>0 && scores[pos - 1]<nova){
        pos--;
    }
    if (pos >= MAX_SCORES){
        return -1;
    }
    if(*n < MAX_SCORES){
        (*n)++;
    }
    for (int i = *n - 1; i>pos; i--){
        scores[i] = scores[i - 1];
    }
    scores[pos] = nova;

    salvar_scores(scores, *n);
    return pos;
}

void mostrar_ranking(int scores[], int n, int pos_nova){
    printf("\n========== TOP %d ==========\n", MAX_SCORES);

    for (int i = 0; i < n; i++){
        printf("%d. %-6d%s\n", i + 1, scores[i], (i == pos_nova) ? " <-- Pontuação atual" : "");
    }

    if (pos_nova < 0){
        printf("\nSua pontuação não entrou no top %d.\n", MAX_SCORES);
    } else if (pos_nova == 0){
        printf("\nNOVO RECORDE!\n");
    }
}
