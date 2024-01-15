#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#define dim 2
#define np 3

int main(int argc, char** argv) {
     int ierr = MPI_Init(NULL, NULL);//Initializa MPI environment
    
     // Get the number of processes
     //int world_size;
     //MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
     // Get the rank of the process
	int A[dim][dim], B[dim][dim], res[dim][dim];
	int aux_m[dim], auxunidim[dim], buffer[dim];
	int i,j;
	int aux = 1; //PARA CONSTRUIR A Y B
	int res_aux[dim];
	int pid, size;
	MPI_Status estado;  
	
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//ESTE ES UN CÓDIGO LIENZO, SE DEBEN USAR LOS SIGUIENTES COMANDOS
	//USAR SÓLO LOS CASOS 0 Y Np-1, en DEFAULT USAR RECEPCIÓN-ENVÍO
	
	printf("Comenzando a llenar las matrices A y B...\n\n");
	/*SI SE DESEA REALIZAR ESTE PROCESO SIN REPETICIONES
	BASTA CON COLOCAR ESTE CÓDIGO EN ALGÚN PID DEL switch
	SUGIERO QUE SEA AL PRINCIPIO DE PID=0*/
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			A[i][j]=aux;
			aux++;
		}
	}
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			B[i][j]=aux;
			aux++;
		}
	}
	
	/*printf("\nMostrando A...\n");
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("\nMostrando B...\n");
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}*/
	
	 MPI_Barrier(MPI_COMM_WORLD);
	
	switch (pid){
	case 0:
		
		printf("Soy el proceso #%d.\n", pid+1);
		
		printf("\nEnviando la matriz B a TODOS los procesos...\n");
		MPI_Bcast(B, dim*dim, MPI_INT, 0, MPI_COMM_WORLD);
		printf("Listo.\n");

		printf("\nEnviando datos de la matriz A al segundo proceso...\n");
		
		
		/*
		MPI_Scatter(Qué envío, tam pedazo, tipo,
			recipiente, #datos, tipo,
			emisor, comunicador); 
		*/
		
		MPI_Scatter(A, dim, MPI_INT,		//dim porque se manda de a 1 fila
			aux_m, dim, MPI_INT,
			pid , MPI_COMM_WORLD); 
		
		printf("Listo.\n\nA continuación se multiplicarán las matrices...\n");

		int resaux;
		for(i=0; i<dim; i++){
			resaux=0;	
			for(j=0; j<dim; j++){
				resaux = resaux + A[0][j]*B[j][i];
			}
			auxunidim[i]=resaux;
		}
		
		printf("\nMi parte del trabajo quedaría como...\n");
		for(i=0; i<dim; i++){
			printf("%d\t", auxunidim[i]);
		}
		
		//MPI_Bcast(auxunidim, dim, MPI_INT, pid, MPI_COMM_WORLD);
		 MPI_Send(auxunidim,//Referencia al vector
	         dim,		//Tamaño del vector
	         MPI_INT,	//Tipo de dato
	         np-1,		//Proceso del destino
	         pid,		//Etiqueta
	         MPI_COMM_WORLD	//Comunicador por donde se manda
	         );
		
		printf("\n");
       		printf("\nProceso #%d terminado.\n", pid+1);
	break;
	
	case (np-1): //último proceso
		sleep(2); //Por seguridad
		printf("\nSoy el proceso #%d coleccionaré datos...\n\n", pid+1);


		/*MPI_Gather(auxunidim, dim, MPI_INT,
			res, dim, MPI_INT, 1, MPI_COMM_WORLD);
		ESTO NO FUNCIONA */
	

		for(i=0; i<dim; i++){
			MPI_Recv(auxunidim,
        			dim,
        			MPI_INT,
        			i,
        			i,
        			MPI_COMM_WORLD,
        			&estado
			        );
			//MPI_Bcast(auxunidim, dim, MPI_INT, i, MPI_COMM_WORLD);
			
			for(j=0; j<dim; j++){
				res[i][j]=auxunidim[j];
				auxunidim[j]=0;
				//printf("%d\t", res_aux[j]);
				//res[i][j]=res_aux[j];
				//res_aux[j]=0;
			}
			//res_aux=NULL;
		}

		
		printf("\nImprimiendo resultados...\n");
		for(i=0; i<dim; i++){
			for(j=0; j<dim; j++){
				printf("%d\t", res[i][j]);
			}
			printf("\n");
		}
		
       		printf("\nProceso #%d terminado.\n", pid+1);
	break;
	
	default:
		sleep(1);
		printf("\nSoy el proceso #%d.\n", pid+1);
		
		MPI_Scatter(A, dim, MPI_INT,		//Se vuelve a colocar para recibir
			aux_m, dim, MPI_INT,
			0 , MPI_COMM_WORLD);
			
		printf("Mi aux_m es:\n");
		for(i=0; i<dim; i++){
			printf("%d\t", aux_m[i]);
		}
		printf("\n");
		
		MPI_Bcast(B, dim*dim, MPI_INT, 0, MPI_COMM_WORLD); //Igualmente se tiene que volver a poner
		/*printf("\nMostrando B...\n");
		for(i=0; i<dim; i++){
			for(j=0; j<dim; j++){
				printf("%d\t", B[i][j]);
			}
			printf("\n");
		}*/
		
		int resaux2;
		for(i=0; i<dim; i++){
			resaux2=0;	
			for(j=0; j<dim; j++){
				resaux2 = resaux2 + aux_m[j]*B[j][i];
			}
			auxunidim[i]=resaux2;
			resaux2=0;
		}
		
		printf("\nMi parte del trabajo quedaría como...\n");
		for(i=0; i<dim; i++){
			printf("%d\t", auxunidim[i]);	//ESTO SE IMPRIME AL ÚLTIMO Y NO SÉ POR QUÉ
		}
		
		//MPI_Bcast(auxunidim, dim, MPI_INT, pid, MPI_COMM_WORLD);
		 MPI_Send(auxunidim,//Referencia al vector
	         dim,		//Tamaño del vector
	         MPI_INT,	//Tipo de dato
	         np-1,		//Proceso del destino
	         pid,		//Etiqueta
	         MPI_COMM_WORLD	//Comunicador por donde se manda
	         );
		
		printf("\n");
       		printf("\nProceso #%d terminado.\n", pid+1);
	}
	
	printf("\n\n\nFin...");
	MPI_Finalize();
}	
