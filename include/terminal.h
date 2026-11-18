#ifndef TERMINAL_H
#define TERMINAL_H

void configurar_terminal(void);
void restaurar_terminal(void);
void voltar_cursor(void);
void esconder_cursor(void);
int  tecla_disponivel(void);
int  ler_tecla(void);
void esperar_frame(void);
void limpar_tela(void);

#endif