# Projeto 3 Roteiro - Grupo 
=================
Allana Idalgo 145166  
Lucas Calzolari 146987  
Ricardo Zaideman 151238  
Vítor Eichemberger 149053  

## Software
----------
Vamos implementar uma versão do algoritmo de Monte Carlo tree search para jogar "jogo da velha" NxN, onde o jogador que preeencher 3 casas adjacentes perde.

## Periférico
---------
O periférico será uma GPU capaz de simular múltiplos jogos simultaneamente. Para uma dada precisão a GPU acelerará a função de decisão sobre a melhor jogada a partir de um estado do jogo.

## Estratégia
---------
A estratégia será realizar jogos entre duas AIs com determinadas precisões em 4 arquiteturas diferentes.  

* Singlecore sem periférico
* Multicore sem periférico
* Singlecore com periférico
* Multicore com periférico  

Avalizando como cada uma destas se comportam com relação ao tempo de execução ou precisão do algoritmo.

