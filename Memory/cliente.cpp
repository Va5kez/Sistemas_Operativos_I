#include  <iostream>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include  <string.h>
#include <unistd.h>
using namespace std;
#define N 128


int main() {
    int       shm_id;
    key_t     mem_key;
    char     *shm_ptr;
    
    mem_key = ftok(".", 'a');
    shm_id = shmget(mem_key, N, 0666);
    if (shm_id < 0) {
         cout << "ERROR" <<endl;
         exit(1);
    }
    
    shm_ptr = (char * ) shmat(shm_id, NULL, 0);  /* attach */
    char cadena[50];
    while (1) {
        usleep(1000000); // Microsegundos
        cout << "Comando: " << shm_ptr << '\n';
        //cin.getline(cadena,50);  // Enter para continua
    }
}