#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys.wait.h>
//#include <sys.shm.h>
//#include <sys.ipc.h>
//#include <curses.h>
#define TAM 100
#define N 2

int main(){
	int tid, i, status;
        int suma_aux=0;
        static int suma_t;
        static int suma_i;
        static int suma_d;

        printf("Suma concurrente de Arrays...\n\n");

        static int A[TAM]; //Creación de array
        int j;
        for(j=0; j<TAM; j++){
                A[j]=j+1;
        }

        for(i=0; i<N; i++){
                tid=fork();
                if(tid==0){
                        break;
                }
                if(i==0){
                        printf("\nSoy el hijo %d.\n", i);
                        suma_aux=0;
                        for(j=0; j<(TAM/2); j++){
                                suma_aux=suma_aux+A[j];
                        }
                        suma_i=suma_aux;
                        printf("Suma izq es %d.\n\n", suma_i);
                        //break;
                }
                if(i==1){
                        printf("\nSoy el hijo %d.\n", i);
                        suma_aux=0;
                        for(j=(TAM/2); j<TAM; j++){
                                suma_aux=suma_aux+A[j];
                        }
                        suma_d=suma_aux;
                        printf("Suma der es %d.\n\n", suma_d);
                        //break;
                }
                wait(&status);
                printf("La suma en el hijo 1 es: %d\n", suma_i);
                printf("La suma en el hijo 2 es: %d\n", suma_d);
                printf("La suma total del arreglo es: %d\n", suma_i+suma_d);
        }
        return 0;
}
