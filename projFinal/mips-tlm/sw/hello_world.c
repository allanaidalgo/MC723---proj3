
#include<stdio.h>
#include<string.h>

int procCounter = 0;
volatile int *lock = (int *) (512*1024*1024);

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

int metdadeDeCima=0;

int v1[4] = {1,2,3,4};
int v2[4] = {5,6,7,8};
int finalizado = 0;
int main( int ac, char *av[]) {
	char *s = "abcd";
	strcpy((char *)lock,s);
	return 0;
  int isCima = 0;
	int procNumber;
	int i;

	procNumber = getCoreID();


  if(procNumber == 0){
    v2[0] += v1[0];
    v2[1] += v1[1];
    while(!finalizado);
    int i = 0;
    for(i=0;i<4;i++){
      printf("%d\n",v2[i]);
    }
  }else if(procNumber == 1){
    v2[3] += v1[3];
    v2[2] += v1[2];
    finalizado = 1;
  }

	return 0;
}
