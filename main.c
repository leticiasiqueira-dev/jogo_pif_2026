#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void desenhar_tela(int posicao_nave){
    printf("          ÓRBITA EM CAOS\n\n");

    printf("Pontuação: 0            Vidas: 3\n\n");

    printf("|                               |\n");
    printf("|              *                |\n");
    printf("|       O                       |\n");
    printf("|                               |\n");
    printf("|                   *           |\n");
    printf("|                               |\n");
    printf("|");
   

    for(int i = 0; i < 31; i++){
        if(i == posicao_nave){
            printf("^");
        }
        else{
            printf(" ");
        }
    }
    printf("|\n");

    printf("|                               |\n");
    printf("|                               |\n");

}

int main(){
    int posicao_nave = 15;
    char tecla;

    do{
        system("cls");

        desenhar_tela(posicao_nave);

        printf("\nA = Esquerda | D = Direita | Q = Sair");

        tecla = _getch();

        if((tecla == 'a' || tecla == 'A') && posicao_nave > 0){
            posicao_nave--;
        }
        if((tecla == 'd' || tecla == 'D') && posicao_nave < 30){
            posicao_nave++;
        }
    }while (tecla != 'q' || tecla != 'Q');

    printf("\nJogo encerrado. Ate a proxima!\n");

    return 0;
}