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

## Metodologia e Desenvolvimento

## Resultados

## Análise e Conclusão

## Referências
