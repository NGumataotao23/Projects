/*LAB11 NATHANGUUMATAOTAO 
 *CSC60 SPR2025 LAB11 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void threadFun(char * msg);

int main(int argc, char *argv[]){

	pthread_t thread1;
	int iret1;
	int *tRet;

	iret1 = pthread_create(&thread1, NULL, &threadFun,(void*) argv[1]);
	
	pthread_join(thread1, &tRet);

	printf("Thread Returned: <%d>\n",*tRet);
	exit(0);
}
void threadFun(char * msg){
	
	int *len = malloc(sizeof(msg));
	printf("In Thread with arg <%s>\n", msg);
	*len = strlen(msg);
	return len;
}
