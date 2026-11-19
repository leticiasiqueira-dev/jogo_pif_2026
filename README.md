<h1 align="center">🚀 Órbita em Caos</h1>

Jogo de ação espacial em C para o terminal, desenvolvido na disciplina de Programação Imperativa e Funcional da CESAR School (2026.2).

## Sobre o jogo

Pilote uma nave e sobreviva à passagem de asteroides. Eles surgem no topo da arena em colunas aleatórias e descem em velocidades diferentes. Mova a nave na horizontal para desviar deles e dispare para abrir caminho.

- A partida começa com **3 vidas**. Cada asteroide que atinge a nave tira uma vida.
- Cada asteroide destruído vale **100 pontos**.
- Você vence ao alcançar **1.000 pontos**, o equivalente a 10 asteroides destruídos.
- A partida termina em derrota quando as vidas acabam.

## Controles

| Tecla | Ação |
| --- | --- |
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `Espaço` | Atirar |
| `Q` | Encerrar a partida |

Na arena, `^` representa a nave, `O` representa um asteroide e `!` representa um disparo.

## Como compilar e executar

Use um terminal no Linux, no macOS ou no WSL (Subsistema do Windows para Linux). Você precisa de Git, Make e um compilador C. O Makefile usa o comando `gcc` por padrão. Os módulos da [CLI-LIB](https://github.com/tgfb/cli-lib/) já estão incluídos no repositório.

```bash
git clone https://github.com/leticiasiqueira-dev/jogo_pif_2026.git
cd jogo_pif_2026
make
./jogo
```

Se você já clonou o repositório, abra a pasta do projeto no terminal e rode `make run` para compilar e iniciar o jogo em um único passo.

## Ranking

No fim da partida, inclusive ao sair com `Q`, o jogo exibe as **cinco melhores pontuações**. O ranking guarda os valores em ordem decrescente no arquivo `scores.txt`. Quando uma pontuação entra no ranking, o jogo atualiza o arquivo. Se o arquivo estiver ausente, ele é criado ao registrar a primeira pontuação.

## Organização do código

| Arquivo ou pasta | Responsabilidade |
| --- | --- |
| [`src/main.c`](src/main.c) | Laço principal, controles, desenho da arena e condições de fim da partida |
| [`src/asteroide.c`](src/asteroide.c) | Criação e movimento dos asteroides e colisão com a nave |
| [`src/tiro.c`](src/tiro.c) | Criação e movimento dos disparos, colisão com asteroides e atualização da pontuação |
| [`src/placar.c`](src/placar.c) | Leitura, atualização, gravação e exibição do ranking |
| [`include/`](include/) | Cabeçalhos e configurações do jogo, como tamanho da arena e meta de pontos |
| [`Makefile`](Makefile) | Compilação e execução do jogo |

## Conceitos de C aplicados

| Conceito | Aplicação no jogo |
| --- | --- |
| Structs | `Asteroide` e `Tiro` agrupam os dados de cada elemento. |
| Ponteiros | Os ponteiros permitem percorrer e alterar as listas de asteroides e disparos. |
| Alocação dinâmica | Os nós são criados com `malloc` e liberados com `free` quando são removidos ou quando a partida termina. |
| Listas encadeadas | Mantêm os asteroides e os disparos ativos na arena. |
| Matrizes | A função `desenhar_tela` usa a matriz `arena[LINHAS][COLUNAS]`, com 9 linhas e 31 colunas. A cada atualização, ela posiciona os símbolos da nave, dos asteroides e dos tiros nas células `[y][x]` e percorre a matriz para desenhar a arena. |
| Leitura e escrita em arquivo | O placar lê as pontuações com `fscanf` e grava o ranking com `fprintf`. |
| Biblioteca de jogos | Os módulos `screen`, `keyboard` e `timer` da CLI-LIB cuidam da tela, do teclado e do intervalo entre atualizações. |

## Vídeo demonstrativo

<!-- Substitua a linha abaixo pelo link do vídeo com o jogo em execução. -->
Link do vídeo pendente.

## Equipe

- Letícia Almeida Abreu de Siqueira
- Letícia Dornas de Araújo
- Maria Monalysa da Silva