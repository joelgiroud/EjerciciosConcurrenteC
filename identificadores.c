/* Programa: Hola mundo */

#include <curses.h>
#include <stdio.h>

int main()
{
	int tid=23;
	
	tid=fork();
	//tid=0 es el hijo
	//tid=3 se refiere al padre
	if(tid==0){
		printf("Soy el hijo, mi tid es %d, mi pid es %d, mi ppid es %d.\n", tid, getpid(), getppid());
	}
	else{
		printf("Soy el padre, mi tid es %d, mi pid es %d, mi ppid es %d.\n", tid, getpid(), getppid());
	}

sleep(20);	
    return 0;
}
