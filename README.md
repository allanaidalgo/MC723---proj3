MC723A - IC - UNICAMP, *29/06/2017*

# Projeto 3 - Multicore e Aceleração em Hardware

**Grupo**
* Allana Idalgo **145166**
* Lucas Calzolari **146987**
* Ricardo Zaideman **151238**
* Vítor Eichemberger **149053**

## Software

Vamos implementar uma versão do algoritmo de Monte Carlo tree search para jogar "jogo da velha" NxN, onde o jogador que preeencher 3 casas adjacentes perde.

## Periférico

O periférico será uma GPU capaz de simular múltiplos jogos simultaneamente. Para uma dada precisão a GPU acelerará a função de decisão sobre a melhor jogada a partir de um estado do jogo.

## Estratégia

A estratégia será realizar jogos entre duas AIs com determinadas precisões em 4 arquiteturas diferentes.  

* Singlecore sem periférico
* Multicore sem periférico
* Singlecore com periférico
* Multicore com periférico  

Analizando como cada uma destas se comportam com relação ao tempo de execução ou precisão do algoritmo.

## Ferramentas
* ArchC
* MIPS TLM - Simulador de MIPS (em ArchC)

## Metodologia e Desenvolvimento

### Código

Primeiramente implementamos junto ao MIPS-TLM os algorítimos, também adaptando o código do simulador conforme necessário.

#### Algorítimo MonteCarlo

#### O Periférico Básico

Usamos o periférico feito no exercício anterior para atuar como lock global, nos permitindo simular uma CPU multicore

#### GPU

A implementação da GPU se deu através da criação de um módulo de hardware extra (um periférico) no simulador.

### Testes

Após o desenvolvimento do projeto, primeiramente em termos de código, partimos para a criação e execução dos testes.

As configurações usadas foram:

| Configuração | Número de Cores (CPU) | Uso do Periférico |
|--------------|-----------------------|-------------------|
| **C1**       | 1                     | Não               |
| **C2**       |                       | Não               |
| **C3**       | 1                     | Sim               |
| **C4**       |                       | Sim               |

## Resultados

Com a execução dos casos teste acima, tivemos os segintes resultados:

## Análise e Conclusão

Baseado nos dados, pontos importantes a serem ressaltados são
* lorem
* ipsum

Por fim, concluímos que

## Referências
**[1]** Referência...
