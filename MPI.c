#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
     //Initialize the MPI environment
     MPI_Init(NULL, NULL);
    
     // Get the number of processes
     //int world_size;
     //MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
     // Get the rank of the process
     int pid;
     int x=-123;
     int y=0;
     int size;
     MPI_Status estado;  


     MPI_Comm_rank(MPI_COMM_WORLD, &pid);
     MPI_Comm_size(MPI_COMM_WORLD,&size);

     if(pid==1)
     {   
     //   usleep(100);     
        x=100;
        printf("soy el proceso %d ANTEX y voy a enviar a x con valor de  %di\n",pid,x);
        MPI_Send(&x, 1, MPI_INT, 0, 7, MPI_COMM_WORLD);   
        printf("soy el proceso %d DESPUES y voy a enviar a x con valor de  %d somos un total de %d procesos \n",pid,x,size);
     }

     if(pid==2)
     {   
        x=200;
        printf("soy el proceso %d ANTEX y voy a enviar a x con valor de  %di\n",pid,x);
        MPI_Send(&x, 1, MPI_INT, 0, 14, MPI_COMM_WORLD);   
        printf("soy el proceso %d DESPUES y voy a enviar a x con valor de  %d somos un total de %d procesos \n",pid,x,size);
     }




     if(pid==0)
     {    
         printf("soy el proceso %d mi valor actual de x es ANTES de la recepcion  %d\n",pid,x);
         MPI_Recv(&x,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);   //estado es una variable de SALIDA al igual que la variable
         printf("soy el proceso %d mi valor actual de x es DESPUES1 de la recepcion es %d  somo en total %d procesos la etiqueta enviada es %d y te la envio el proceso %d\n",pid,x,size,estado.MPI_TAG,estado.MPI_SOURCE);
         MPI_Recv(&y,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);   //estado es una variable de SALIDA al igual que la variable
         printf("soy el proceso %d mi valor actual de x es DESPUES2 de la recepcion es %d  somo en total %d procesos la etiqueta enviada es %d y te la envio el proceso %d\n",pid,y,size,estado.MPI_TAG,estado.MPI_SOURCE);
    
      
      }

    MPI_Finalize();
}