#ifndef PLACAR_H
#define PLACAR_H

int  carregar_scores(int scores[], int max);
void salvar_scores(int scores[], int n);
int  registrar_score(int nova, int scores[], int *n);
void mostrar_ranking(int scores[], int n, int pos_nova);

#endif