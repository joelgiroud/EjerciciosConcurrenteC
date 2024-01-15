/* Programa: Hola mundo */

//#include <conio.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
#define N 3

int main()
{
    printf( "Abanico de procesos...\n\n" );
	int tid, i;
	
	for(i=0; i<N; i++){
		tid=fork();
		if(tid==0){
			break;
		}
	}
	printf("El valor de i es: %d.\n", i);
	sleep(30);
	
    return 0;
}
