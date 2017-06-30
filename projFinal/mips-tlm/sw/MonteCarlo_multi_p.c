#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MonteCarlo.h"
#include "../gpu/gpuConstants.h"

int procCounter = 0;
volatile int *lock = LOCK_ADDRESS;
char *gpu[4] = {(char *) GPU_ADDRESS_1, (char *) GPU_ADDRESS_2, (char *) GPU_ADDRESS_3, (char *) GPU_ADDRESS_4};
char *gpu_meta[4] = {(char *) GPU_META_BASE_1, (char *) GPU_META_BASE_2, (char *) GPU_META_BASE_3, (char *) GPU_META_BASE_4};

void AcquireGlobalLock()
{
	while (*lock);
}

void ReleaseGlobalLock()
{
	*lock = 0;
}

int getCoreID(){
  AcquireGlobalLock();
	int id = procCounter++;
	ReleaseGlobalLock();
  return id;
}

void moveStates (gameState *game, char * offSet) {

	int * s = (int *)game;

	int stateSizePerInt = sizeof(gameState)/sizeof(int);

	if (sizeof(int) != 4) {
		printf("Reveja suas ideias\n");
		printf("Reveja suas ideias\n");
		printf("Reveja suas ideias\n");
	}

	int i;
	for (i = 0; i < stateSizePerInt; i++) {
		*((int *)(offSet+i)) = *(s+i);
	}
}

int nodeTotal(node *n) {
	return n->draws + n->loses + n->win;
}

node * alocateNode(gameState * game) {
	node * ret = (node*)calloc(1, sizeof(node));
	ret->state = game;
	return ret;
}

node ** createArray(gameState ** array, int s) {
	int n = s;
	node ** ret = (node**)calloc(n, sizeof(node*));
	int i;
	for (i = 0; i < n; i++) {
		ret[i] = (node*)alocateNode(array[i]);
		ret[i]->state = array[i];
	}
	return ret;
}

long rnd (int seed, int a);

node * sampleNode(node* n, int s, enum boardState me){
	gameState * aux = NULL;
	int i;
	for (i = 0; i < s; i++) {
		aux = playRandomGame((n->state), aux);
		int result = iWin(aux,me);
		if (result < 0)
			n->loses++;
		else if (!result)
			n->draws++;
		else
			n->win++;
	}
	return n;
}

void writeMeta(int gpu_id, int meta, int data){

	char * offset = gpu_meta[gpu_id]+meta;
	*((int *)offset) = data;
}

int readMeta(int gpu_id, int meta){
	char * offset = gpu_meta[gpu_id]+meta;
	return *((int *)offset);
}

int psamplecount = 0;
void pSampleNode(node* n, int s, enum boardState me){
	psamplecount++;
	moveStates(n->state,gpu[0]);
	writeMeta(0,1,me);
	writeMeta(0,2,0);
	writeMeta(0,3,0);
	writeMeta(0,4,0);

	writeMeta(0,0,0xAABBCCDD);

	n->win = readMeta(0,2);
	n->draws = readMeta(0,3);
	n->loses = readMeta(0,4);
}

node * decideNode(node ** array, enum boardState me, int c, int n) {
	float average = -1, totalwins, total;
	int nsurvivers = n;
	int mark = 0;
	int max = -1;
	// while (nsurvivers >= 1) {
		int aux = 0;
		totalwins = 0;
		total = 0;
		int i;
		for (i = 0; i < n; i++) {
			node * nd = array[i];
			if (!nodeTotal(nd) || ((nd->win - nd->loses) / nodeTotal(nd)) > average) {
				pSampleNode(array[i], 0xAABBCCDD, me);
				if(nd->win > max){
					mark = i;
					max = nd->win;
				}
				aux++;
				totalwins += (nd->win - nd->loses);
				total += nodeTotal(nd);
			}
		}
		average = total != 0 ? totalwins/total : 0;
		nsurvivers = aux;
	// }
	return array[mark];
}

node ** splitNode(node * n, int *s) {
    *s = npossibleStates(n->state);
	gameState ** games = alocateArray(*s);
	games = allPossibleStates(games,n->state);
	return createArray(games, *s);
}

node * first() {
	return alocateNode(gameSetup());
}

void printNode(node * n) {
	printState(n->state);
	// printf("Win %f Draw %f Lose %f Total %f\n", n->win / nodeTotal(n), n->draws / nodeTotal(n), n->loses / nodeTotal(n),nodeTotal(n));
}

void setNewRoot (node **chooseArray, int n ,node *newRoot, node **root) {

		free((*root)->state);
    free(*root);

    *root = newRoot;

		int i;
		for (i = 0; i < n; i++) {
        if (chooseArray[i] != newRoot) {
            free(chooseArray[i]->state);
            free(chooseArray[i]);
        }
    }
    free(chooseArray);
}

	// s = (int *)buffer;
	// for (i = stateSizePerInt; i < 2*stateSizePerInt; i++) {
	// 	printf("i: %d data: %d\n",i, *(s+i));
	// 	*((int *)(offSet+i)) = *(s+i);
	// }


	// int semaphore = 0;
	//
	// void tryResetCount(){
	// 	if(semaphore > 2){
	// 		semaphore = 0;
	// 	}
	// }
	//
	// int checkpoint = 0;
	// voi getCheckpoint(){
	// 	checkpoint++;
	// 	while(checkpoint != 2);
	// 	checkpoint = 0;
	// }

int main(int argc, char *argv[]) {
	int procNumber = getCoreID();
	// int procNumber = 0;
	if (procNumber != 0) {
		return 0;
	}
	if(procNumber == 0){
		// moveStates (gameSetup(),gpu);
		// writeMeta(gpu, 1, X);
		// writeMeta(gpu, 2, 1);
		// writeMeta(gpu, 3, 2);
		// writeMeta(gpu, 4, 3);
		// writeMeta(gpu,0,0xAABBCCDD);


		node * root = first();
	  int nPossibilities;
		node ** tochoose;
		node *answer;
		if (Player == X) {
			tochoose = splitNode(root, &nPossibilities);
			answer = decideNode(tochoose,Player,200, nPossibilities);
	       setNewRoot(tochoose, nPossibilities, answer, &root);
			printNode(root);
		}
		while (root->state->result == B) {
			tochoose = splitNode(root, &nPossibilities);
			answer = decideNode(tochoose,Ai,300, nPossibilities);
		 //
	   	setNewRoot(tochoose, npossibleStates(root->state), answer, &root);
		 //
			printNode(answer);
			if (root->state->result == B) {
				tochoose = splitNode(root, &nPossibilities);
				answer = decideNode(tochoose,Player,200, nPossibilities);
				setNewRoot(tochoose, npossibleStates(root->state), answer, &root);
				printNode(root);

	   }
	 }
	}
	printf("PSAMPLES CALLED: %d\n", psamplecount);
	return 0;

}

long rnd (int seed, int a) {
    long ret = ((seed+a)*104393 * 101437);
    return ret;
}
