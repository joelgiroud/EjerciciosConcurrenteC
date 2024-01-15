/* Programa: Hola mundo */

//#include <conio.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
#define NIVEL 5 //PROFUNDIDAD

int main()
{
    printf( "Arbol de procesos...\n\n" );
	//static int lvl = NIVEL;
	static int actual = 0;
	int tid;
	
	do{
		for(int i=0; i<2; i++){ //BINARIO = 2{
			tid=fork();
			if(tid==0){	//Es el padre
				break;
			}
			//printf("\n%d\n", tid); //Para fines experimentales
		}
		
		actual++;
		
		if(tid!=0){
			break;
		}
	}
	while(actual!=NIVEL-1); //Esto no considera la raíz
	sleep(25);
    return 0;
}

