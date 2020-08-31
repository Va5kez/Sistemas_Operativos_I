#include  <iostream>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include  <string.h>
using namespace std;
#define N 128


int main() {
    int       shm_id;
    key_t     mem_key;
    char     *shm_ptr;
    
    mem_key = ftok(".", 'a');
    shm_id = shmget(mem_key, N, IPC_CREAT | 0666);
    if (shm_id < 0) {
         cout << "ERROR" <<endl;
         exit(1);
    }
    
    shm_ptr = (char *) shmat(shm_id, NULL, 0);  /* attach */
    char cadena[50];
    while (1) {
        cout <<"Comando: ";
        cin.getline(cadena,50);
        strcpy(shm_ptr,cadena);
    }
}