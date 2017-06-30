#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
enum boardState Ai,Player;

gameState* initialState() {
	gameState * state = (gameState*)calloc(1, sizeof(gameState));
	return state;
}

gameState* gameSetup() {

	srand((int)time(NULL));
	if (rand() % 2)
		Ai = X;
	else
		Ai = O;

	if (Ai == X)
		Player = O;
	else
		Player = X;
	return initialState();
}

enum boardState whosTurn(gameState * game) {
	if (game->turn % 2)
		return X;
	else return O;
}

gameState * createCopy(gameState *p) {
	int i, j;
	gameState * state = (gameState*)calloc(1, sizeof(gameState));
	for (i = 0; i<size; i++) {
		for (j = 0; j<size; j++) {
			state->values[i][j] = p->values[i][j];
		}
	}
	state->turn = p->turn;
	state->result = p->result;
	return state;
}

void copyStates(gameState *state, gameState *p) {
	int i, j;

	for (i = 0; i<size; i++) {
		for (j = 0; j<size; j++) {
			state->values[i][j] = p->values[i][j];
		}
	}
	state->turn = p->turn;
	state->result = p->result;
}

enum boardState gameEnded(gameState * g, int x, int y) {
	int i, j;
    for (i = x - 1; i <= x + 1; i++) {
		for (j = y - 1; j <= y + 1; j++) {

            if (i > 0 && j > 0 && i < size && j < size) {
                if (i > 0 && i + 1 < size && g->values[i][j] == O && g->values[i + 1][j] == O && g->values[i - 1][j] == O)
                    return X;
                if (j > 0 && j + 1 < size && g->values[i][j] == O && g->values[i][j + 1] == O && g->values[i][j - 1] == O)
                    return X;
                if (i > 0 && i + 1 < size && j > 0 && j + 1 < size && g->values[i][j] == O && g->values[i + 1][j + 1] == O && g->values[i - 1][j - 1] == O)
                    return X;
                if (i > 0 && i + 1 < size && j > 0 && j + 1 < size && g->values[i][j] == O && g->values[i + 1][j - 1] == O && g->values[i - 1][j + 1] == O)
                    return X;
                if (i > 0 && i + 1 < size && g->values[i][j] == X && g->values[i + 1][j] == X && g->values[i - 1][j] == X)
                    return O;
                if (j > 0 && j + 1 < size && g->values[i][j] == X && g->values[i][j + 1] == X && g->values[i][j - 1] == X)
                    return O;
                if (i > 0 && i + 1 < size && j > 0 && j + 1 < size && g->values[i][j] == X && g->values[i + 1][j + 1] == X && g->values[i - 1][j - 1] == X)
                    return O;
                if (i > 0 && i + 1 < size && j > 0 && j + 1 < size && g->values[i][j] == X && g->values[i + 1][j - 1] == X && g->values[i - 1][j + 1] == X)
                    return O;
            }
		}
	}

	return B;
}

gameState** allPossibleStates(gameState ** arraypos, gameState *currentState) {
	int i, j, k = 0;
	int n = size*size - currentState->turn;
	for (i = 0; i < n; i++)
		copyStates(arraypos[i], currentState);
	for (i = 0; i<size; i++) {
		for (j = 0; j<size; j++) {
			if (k >= n)
				return arraypos;
			if (currentState->values[i][j] != B)
				continue;
			else {
				if (!(currentState->turn % 2))
					arraypos[k]->values[i][j] = X;
				else
					arraypos[k]->values[i][j] = O;
				arraypos[k]->result = gameEnded(arraypos[k], i, j);
				arraypos[k]->turn++;
				k++;
			}
		}
	}
	return arraypos;
}

gameState * randomState(gameState * next, gameState * pre) {
	int i, j, k, pos, n;
	k = 0;
	n = size*size - pre->turn;
	pos = rand() % n;
	if (next != pre)
		copyStates(next, pre);
	for (i = 0; i<size; i++) {
		for (j = 0; j<size; j++) {
			if (next->values[i][j] != B)
				continue;
			else if (k == pos) {
				if (!(next->turn % 2))
					next->values[i][j] = X;
				else
					next->values[i][j] = O;
				next->result = gameEnded(next, i, j);
				next->turn++;
				return next;
			}
			k++;
		}
	}
	return pre;

}

void printState(gameState * p) {
	int i, j;
	if(whosTurn(p) == Ai)
		printf("Turno %d vez de %s\n", p->turn-1,"Ai");
	else
		printf("Turno %d vez de %s\n", p->turn-1, "Player");
	for (i = 0; i<size; i++) {
		for (j = 0; j<size; j++) {
			enum boardState s = p->values[i][j];
			if (s == X)
				printf("X");
			else if (s == O)
				printf("O");
			else
				printf(" ");
		}
		printf("\n");
	}

	if (p->result == B)
		printf("Sem vencedores\n");
	else if (p->result == X) {
		printf("Com X como vencedor\n");
		//system("pause");
	}
	else {
		printf("Com O como vencedor\n");
		//system("pause");
	}

}

void printPossibleStates(gameState **g, int lenght) {
	int i;
	for (i = 0; i< lenght; i++) {
		printf("Estado possivel nro %d para ", i);
		printState(g[i]);
	}
}

gameState * playRandomGame(gameState *game,gameState *buffer) {
	if (game->result != B)
		return game;
	if(!buffer)
		buffer = (gameState*)calloc(1, sizeof(gameState));
	if (randomState(buffer, game)->result == B)
		while (randomState(buffer, buffer)->result == B);

	return buffer;
}

gameState * playerPlay(gameState *game) {
	enum boardState me = Player;
	int i, j;
	printf("Sua vez\n");
	scanf("%d %d", &i, &j);
	if (game->values[i][j] != B || i < 0 || i >= size || j < 0 || j >= size) {
		printf("Entrada invalida!\n");
		playerPlay(game);
	}
	else {
		game->values[i][j] = me;
		game->turn++;
		game->result = gameEnded(game, i, j);
	}
	printState(game);
	return game;

}

gameState ** alocateArray(int n) {
	gameState ** ret = (gameState**)calloc(n, sizeof(gameState*));
	int i;
	for (i = 0; i < n; i++)
		ret[i] = (gameState*)calloc(1, sizeof(gameState));
	return ret;
}

int iWin(gameState * game, enum boardState me) {
	int sum = 0;
	if (game->result == me)
		sum++;
	else if (game->result != B)
		sum--;
	return sum;
}

int npossibleStates(gameState* game) {
	return size*size - game->turn;
}
