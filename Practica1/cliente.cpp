#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "structs.h"
#define N sizeof(Segmento)

int main()
{
    key_t mem_key = ftok(".", 'a');
    int shm_id = shmget(mem_key, N, IPC_CREAT | 0666);
    if(shm_id < 0)
    {
        std::cout << "ERROR" << std::endl;
        exit(1);
    }
    Segmento *s = (Segmento*) shmat(shm_id, NULL, 0);
    s->nProcesos = 0;
    s->entrada = 0;
    Proceso proc1 = {2220, 1, Estados::Listo, 10};
    Proceso proc2 = {2221, 4, Estados::Nuevo, 15};
    Proceso proc3 = {2222, 6, Estados::Terminado, 20};
    Proceso proc4 = {2223, 2, Estados::En_espera, 25};
    Proceso proc5 = {2224, 3, Estados::En_ejecucion, 30};
    Proceso proc6 = {2225, 5, Estados::Listo, 10};
    s->buffer[s->entrada] = proc1;
    s->entrada++;
    s->buffer[s->entrada] = proc2;
    s->entrada++;
    s->buffer[s->entrada] = proc3;
    s->entrada++;
    s->buffer[s->entrada] = proc4;
    s->entrada++;
    s->buffer[s->entrada] = proc5;
    s->entrada++;
    s->buffer[s->entrada] = proc6;
    s->entrada++;
    s->nProcesos = s->entrada;
    while(1)
    {
        std::cout << "Enviando procesos al servidor" << std::endl;
        std::cin.get();
    }
    return 0;
}