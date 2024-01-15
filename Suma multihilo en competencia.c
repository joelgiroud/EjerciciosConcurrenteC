#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> //Compilar -o con -pthread
#define NUM_THREADS 2
#define TAM 1000

int x[TAM];
int total=0;
int ind=0;
pthread_mutex_t m1;	//declara un candado-mutex tipo pthread_mutex_t
pthread_mutex_t m2;	//

void *PrintHello(void *threadid){
	long taskid;
	int inicio, fin;
	int i, ilocal;
	int parcial = 0;
	int contador = 0;
	
	taskid = (long) threadid;	//identificador del hilo
	
	/*
		printf("Thread $ld: \n", taskid);
		inicio = (taskid)*(TAM/NUM_THREADS);
		fin = (taskid+1)*(TAM/NUM_THREADS);
	*/
	
	while (ind<TAM){
		pthread_mutex_lock(&m1);
		ilocal=ind;
		ind++;
		pthread_mutex_unlock(&m1);
		
		//if(ilocal<TAM){
		//	contador++;
			parcial = parcial + x[ilocal];
		//}
	}

	printf("Soy el hilo %ld y mi ilocal es: %d\n", taskid, ilocal);
	
	if(ilocal>=TAM){
		parcial = parcial - x[ilocal];
	}
	
	pthread_mutex_lock(&m2);
	total = total + parcial;	//REGIÓN CRÍTICA
	pthread_mutex_unlock(&m2);
	
	//printf("Soy el hilo %ld sumé %d casillas\n\n", taskid, contador);
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	long taskids[NUM_THREADS];
	int t,i;
	
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	
	for(i=0; i<TAM+NUM_THREADS; i++){
		x[i]=1;
	}
	
	for(t=0; t<NUM_THREADS; t++){
		taskids[t] = t;
		pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
		
	}
	
	//sleep(1);
	
	for(t=0; t<NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}
	
	printf("Soy el hilo principal. El resultado final es %d.\n", total);
	
	//pthread_exit(NULL);
	
}





