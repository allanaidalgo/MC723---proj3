#define size 10

// typedef enum possibleResults possibleResults;
enum boardState { B = 0, O, X };

typedef struct gamestate {
    enum boardState values[size][size];
	int turn;
	enum boardState result;
} gameState;

typedef struct node {
	gameState * state;
	int win, loses, draws;
}node;

gameState* gameSetup();
enum boardState whosTurn(gameState * game);
gameState** allPossibleStates(gameState ** arraypos, gameState *currentState);
gameState * randomState(gameState * next, gameState * pre);
gameState * playRandomGame(gameState *game,gameState *buffer);
gameState * playerPlay(gameState *game);
gameState ** alocateArray(int n);
void printState(gameState * p);
int iWin(gameState * game, enum boardState me);
int npossibleStates(gameState* game);
node * sampleNode(node* n, int s, enum boardState me);
void lala();
