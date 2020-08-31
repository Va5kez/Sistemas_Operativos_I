#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "structs.h"
#include <string.h>
#define N sizeof(Segmento)

std::string print_estado(Estados p_estado)
{
    switch (p_estado)
    {
    case Estados::Nuevo:
        return "Nuevo       ";
    case Estados::Listo:
        return "Listo       ";
    case Estados::En_espera:
        return "En Espera   ";
    case Estados::En_ejecucion:
        return "En Ejecucion";
    case Estados::Terminado:
        return "Terminado   ";
    default:
        return "Error";
    }
}

int main()
{
    key_t mem_key = ftok(".", 'a');
    int shm_id = shmget(mem_key, N, IPC_CREAT | 0666);
    if(shm_id < 0)
    {
        std::cout << "Error al tratar de obtener el Shared Memory" << std::endl;
        exit(1);
    }
    Segmento *s = (Segmento*) shmat(shm_id, NULL, 0);
    int array_size = s->nProcesos;
    Proceso cola_procesos[array_size];
    for(int i = 0; i < array_size; i++)
        cola_procesos[i] = s->buffer[i];

    // Ordenando la cola de procesos por Prioridad : 1->Mas alta , 10->Mas baja
    int i,j;
    Proceso key;  
    for (i = 1; i < array_size; i++) 
    {  
        key = cola_procesos[i];  
        j = i-1;  
        while (j >= 0 && cola_procesos[j].prioridad > key.prioridad) 
        {  
            cola_procesos[j+1] = cola_procesos[j];  
            j = j-1;  
        }  
        cola_procesos[j+1] = key;  
    }  

    while (1)
    {
        std::cout << "-------------Ejecutando lista de procesos-------------" << std::endl;

        for(int i = 0; i < array_size; i++)
        {
            int sleep_time = cola_procesos[i].cpuTime <= 60 ? cola_procesos[i].cpuTime*1000000 : 60*1000000; 
            usleep(sleep_time);
            std::cout << "ID: " << cola_procesos[i].id << " | ";
            std::cout << "Prioridad: " << cola_procesos[i].prioridad << " | ";
            std::cout << "Estado: " << print_estado(cola_procesos[i].estado) << " | ";
            std::cout << "CpuTime: " << cola_procesos[i].cpuTime << '\n';
        }
        std::cout << "------------------Ejecucion Terminada------------------" << std::endl;
        std::cin.get();
    }
    return 0;
}
