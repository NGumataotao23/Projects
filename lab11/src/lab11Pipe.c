/*NATHANGUMATAOTAO
 * CSC60 SPR2025 Lab11*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {

    int p[1];
    char buffer[100];
    char * msg = argv[1];
    if(pipe(p) == -1){
	perror("pipe");
	exit(1);
	}


    printf("Parent[%d]: running...\n", getpid());

    int pid = fork();
    if (pid < 0) {
	perror("fork failed!");
	exit(-1);

    } else if (pid == 0) {
	printf("Child[%d]: running...\n", getpid());
	read(p[0],buffer,100);
	printf("Child: Received Messege:%s\n",buffer);
	exit(EXIT_SUCCESS);
    }
	
    printf("Parent[%d]: waiting...\n", getpid());
	write(p[1],msg,buffer);
    int stat;
    int ret = wait(&stat);

    printf("Parent[%d]: done.\n", getpid());
    exit(EXIT_SUCCESS);
}

