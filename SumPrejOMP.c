#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define TAM 8
//#define THREADS 2

void main(){

	int A[TAM] = {2, 7, 3, 1, 9, 4, 5, 3};	//Definimos A[]
	int B[TAM];
	int i, j, k;	//i puede ser local
	int sum_total=0;
	int total=0;	
	int etapa=1;

	B[0] = A[0];	//Inicializamos B[0]
	
	for(j=0;j<log2(TAM);j++){
	        omp_set_num_threads(TAM - pow(2, j));	//Cuántos hilos queremos trabajar?
	        #pragma omp parallel shared (A, B)
	        {
	        	int id = omp_get_thread_num();
	        	int aux;
	        	
	        	#pragma omp for schedule (static)
	        	for(i=pow(2,j); i<TAM; i++){
	        		B[i] = A[i] + A[i - (int) pow(2,j)];
	        	}
	        	
	        	#pragma omp for schedule (static)
	        	for(i=pow(2, j); i<TAM; i++){
	        		A[i] = B[i];
	        	}

	        	
			printf("Soy hilo %d...\n", id); //Original agrega , B[i], su suma
	        }
	        printf("Arreglo en etapa %d queda como...\n[", etapa);
	        for(k = 0; k<TAM; k++){
	        	A[k] = B[k];
	        	if(!(k==TAM-1)){
	        		printf("%d,\t", A[k]);
	        	}
	        	else{
	        		printf("%d", A[k]);
	        	}
	        }
	        printf("]\n");
	        etapa++;
	}


return;
}
