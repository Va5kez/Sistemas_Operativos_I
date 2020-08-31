#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

using namespace std;

struct Mensaje {
    char receptor[20];
    char asunto[50];
};

void *imprimir_mensaje( void *ptr );
void *imprimir_mensajeS( void *ptr );

int main()
{
     pthread_t thread1, thread2, thread3;
     char mensaje1[20] = "Hilo 1";
     char mensaje2[20] = "Hilo 2";
     Mensaje mensaje;
     strcpy(mensaje.receptor, "Juan");
     strcpy(mensaje.asunto, "SO I threads");
     int  iret1, iret2;

     iret1 = pthread_create( &thread1, NULL, imprimir_mensaje, (void*) mensaje1);
     iret2 = pthread_create( &thread2, NULL, imprimir_mensaje, (void*) mensaje2);
     iret2 = pthread_create( &thread3, NULL, imprimir_mensajeS, (void*) &mensaje);


     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 
     pthread_join( thread3, NULL); 

     printf("Hilo 1 retorna: %d\n",iret1);
     printf("Hilo 2 retorna: %d\n",iret2);
     
     exit(0);
}

void *imprimir_mensaje( void *ptr )
{
     char *message;
     message = (char * ) ptr;
     cout << "Mensaje: " <<message << endl;
}

void *imprimir_mensajeS( void *ptr )
{
     Mensaje *mensaje;
     mensaje = (Mensaje * ) ptr;
     cout << "Receptor: " <<mensaje->receptor << '\n';
     cout << "Asunto: " <<mensaje->asunto << '\n';
}