#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;


void *imprimir_mensaje( void *ptr );

int main()
{
     pthread_t thread1, thread2;
     char mensaje1[20] = "Hilo 1";
     char mensaje2[20] = "Hilo 2";
     int  iret1, iret2;

     iret1 = pthread_create( &thread1, NULL, imprimir_mensaje, (void*) mensaje1);
     iret2 = pthread_create( &thread2, NULL, imprimir_mensaje, (void*) mensaje2);


     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     printf("Hilo 1 retorna: %d\n",iret1);
     printf("Hilo 2 retorna: %d\n",iret2);
     //exit(0);
}

void *imprimir_mensaje( void *ptr )
{
     char *message;
     message = (char *) ptr;
     cout << "Mensaje: " <<message << endl;
}