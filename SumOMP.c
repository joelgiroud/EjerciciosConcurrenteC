#include <omp.h>
#include <omp.h>
#include <stdio.h>
#define TAM 100
#define THREADS 2

int main(){

	int A[TAM];
	int j;
	int total=0;
	
	for(j=0;j<TAM;j++){
	        A[j]=1;
	}

	#pragma omp parallel num_threads(THREADS)
	{
	int inicio, final;
	int i;
	int tid;
	int sumaparcial=0;
	int num_hilos;
	num_hilos = omp_get_num_procs();
	tid = omp_get_thread_num();
	
	//printf("Soy el hilo %d\n",tid);
	inicio = (TAM/num_hilos)*tid;
	final = (TAM/num_hilos)*(tid+1);
	
	
	for (i=inicio;i<final;i++){
	        //printf("Soy el hilo %d y la i que me toco del for es %d/n",tid,i);
	        sumaparcial = sumaparcial + A[i];
	        }
	
	#pragma omp critical
	total = total + sumaparcial;
	
	printf("Soy el hilo %d mi suma parcial es %d\n",tid,sumaparcial);
	
	
}//fin del programa parallel

printf("La suma total es %d\n",total);

return 0;
}
