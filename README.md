# [Nome do jogo]

Projeto da disciplina **Programação Imperativa e Funcional — 2026.2**, da CESAR School.

> Modelo em preenchimento: substituam os campos entre colchetes. As aplicações dos conceitos indicadas abaixo são propostas e devem ser atualizadas conforme a implementação.

## 1. Sobre o jogo

Um jogo de ação e sobrevivência no terminal em que o jogador controla uma nave espacial que perdeu completamente a comunicação com sua nave-mãe e ficou perdida no espaço. Para sobreviver, precisa desviar de ataques e chuvas de meteoros, destruir monstros e naves inimigas e enfrentar ondas de dificuldade crescente.

O jogo envolve movimentação, colisões e decisões rápidas que desafiam os reflexos e o raciocínio estratégico do jogador.

## 2. Objetivo

Sobreviver aos perigos da galáxia e avançar pelas ondas de inimigos.

- **Condição de vitória:** [Definir se há uma última onda ou se a sobrevivência é contínua.]
- **Condição de derrota:** [Definir quando a partida termina.]

## 3. Regras e mecânicas

### Movimentação

- Direções permitidas: [Definir.]
- Limites da área de movimentação: [Definir.]

### Ataques

- Como a nave dispara: [Definir.]
- Frequência ou limite dos disparos: [Definir.]
- Elementos que podem ser destruídos: [Definir.]

### Inimigos e meteoros

| Elemento | Movimento e comportamento | Efeito ao atingir a nave |
| --- | --- | --- |
| Nave inimiga | [Definir.] | [Definir.] |
| Monstro espacial | [Definir.] | [Definir.] |
| Meteoro | [Definir.] | [Definir.] |

### Vidas e colisões

- Vidas ou energia inicial: [Definir.]
- Colisão entre nave e inimigo: [Definir.]
- Colisão entre nave e meteoro: [Definir.]
- Colisão entre tiro e inimigo: [Definir.]
- Colisão entre tiro e meteoro: [Definir.]
- O que acontece com elementos que saem da área de jogo: [Definir.]

### Pontuação

| Evento | Pontos |
| --- | --- |
| Destruir uma nave inimiga | [Definir.] |
| Destruir um monstro | [Definir.] |
| Concluir uma onda | [Definir, se aplicável.] |

### Ondas e dificuldade

- Condição para iniciar uma nova onda: [Definir.]
- Quantidade de ondas: [Definir.]
- O que muda a cada onda: [Velocidade, quantidade de inimigos ou outros fatores.]

## 4. Controles

| Ação | Tecla |
| --- | --- |
| Mover para a esquerda | [Definir.] |
| Mover para a direita | [Definir.] |
| Mover para cima/baixo, se houver | [Definir ou remover.] |
| Atirar | [Definir.] |
| Sair | [Definir.] |

## 5. Tecnologias e dependências

- **Linguagem:** C.
- **Interface:** terminal / linha de comando.
- **Biblioteca de jogos:** [Confirmar a biblioteca escolhida.]
- **Biblioteca indicada pela disciplina:** [CLI-LIB](https://github.com/tgfb/cli-lib/), com recursos de tela, teclado e temporização.
- **Compilador e ferramentas:** [Preencher após validar o ambiente.]
- **Sistemas operacionais testados:** [Preencher somente os efetivamente testados.]

## 6. Como compilar e executar

### Preparação

1. Obter o projeto: [Inserir link do repositório e instruções.]
2. Instalar as dependências: [Descrever os passos testados.]
3. Preparar a biblioteca utilizada: [Descrever os passos necessários.]

### Compilação

[Inserir o comando de compilação validado pelo grupo ou explicar como usar o Makefile/script.]

### Execução

[Inserir o comando para iniciar o jogo e informar a pasta em que deve ser executado.]

## 7. Conceitos obrigatórios da disciplina

| Conceito | Aplicação planejada | Local na implementação |
| --- | --- | --- |
| Structs | Representação da nave, inimigos, meteoros e tiros | [Arquivo e estrutura.] |
| Ponteiros | Manipulação de estruturas e elementos das listas | [Arquivo e função.] |
| Alocação dinâmica | Criação e liberação de elementos durante a partida | [Arquivo e função.] |
| Listas encadeadas | Controle de tiros ou inimigos ativos | [Arquivo e funções de inserção/remoção.] |
| Matrizes | Representação da área do jogo | [Arquivo e matriz.] |
| Leitura e escrita em arquivo | Persistência das melhores pontuações | [Arquivo e funções.] |

## 8. Ranking e persistência

- Dados armazenados: [Nome, pontuação e outros campos definidos pelo grupo.]
- Arquivo utilizado e localização: [Preencher.]
- Momento em que a pontuação é salva: [Definir.]
- Como consultar as melhores pontuações: [Preencher.]
- Comportamento quando ainda não existe arquivo de ranking: [Definir.]

## 9. Organização do projeto

Preencher conforme os arquivos forem criados.

| Arquivo ou pasta | Responsabilidade |
| --- | --- |
| [Nome/caminho.] | [Descrever.] |
| [Nome/caminho.] | [Descrever.] |
| [Nome/caminho.] | [Descrever.] |

## 10. Estado do desenvolvimento

- [x] Repositório criado e acesso dos três integrantes confirmado.
- [ ] Nome e regras básicas definidos.
- [ ] Ambiente de desenvolvimento validado pelos três integrantes.
- [ ] Biblioteca de jogos funcionando.
- [ ] Nave com movimentação e limites.
- [ ] Meteoros com movimento automático.
- [ ] Colisões e controle de vidas.
- [ ] Tiros e inimigos.
- [ ] Pontuação e progressão das ondas.
- [ ] Matriz utilizada no jogo.
- [ ] Listas encadeadas e alocação/liberação de memória.
- [ ] Ranking com leitura e escrita em arquivo.
- [ ] Telas de início e fim de partida.
- [ ] Instruções de compilação e execução verificadas.
- [ ] Testes manuais concluídos.
- [ ] Vídeo demonstrativo publicado e link inserido.

## 11. Verificação do jogo

Registrar os resultados depois de testar.

| Cenário | Resultado esperado | Situação |
| --- | --- | --- |
| Mover a nave até as bordas | Nave permanece dentro da área permitida | [Pendente/aprovado.] |
| Não pressionar teclas | Meteoros e inimigos continuam se movendo | [Pendente/aprovado.] |
| Colidir com um obstáculo | Dano aplicado conforme as regras | [Pendente/aprovado.] |
| Atingir um inimigo com um tiro | Colisão e pontuação seguem as regras | [Pendente/aprovado.] |
| Esgotar as vidas | Partida termina corretamente | [Pendente/aprovado.] |
| Concluir uma onda | Progressão segue a condição definida | [Pendente/aprovado.] |
| Fechar e reabrir o jogo | Ranking salvo continua disponível | [Pendente/aprovado.] |
| Executar sem arquivo de ranking | Jogo trata a ausência do arquivo | [Pendente/aprovado.] |

## 12. Vídeo demonstrativo

[Inserir o link do vídeo com o jogo em execução.]

## 13. Integrantes

| Integrante | GitHub | Contribuições |
| --- | --- | --- |
| [Nome.] | [Link do perfil.] | [Preencher com as contribuições realizadas.] |
| [Nome.] | [Link do perfil.] | [Preencher com as contribuições realizadas.] |
| [Nome.] | [Link do perfil.] | [Preencher com as contribuições realizadas.] |

## 14. Referências e créditos

- Enunciado do projeto de Programação Imperativa e Funcional — 2026.2.
- [CLI-LIB](https://github.com/tgfb/cli-lib/), caso utilizada.
- [Adicionar documentação e outras referências consultadas.]