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
    std::string res;
    switch (p_estado)
    {
    case Estados::Nuevo:
        return "Nuevo";
    case Estados::Listo:
        return "Listo";
    case Estados::En_espera:
        return "En Espera";
    case Estados::En_ejecucion:
        return "En Ejecucion";
    case Estados::Terminado:
        return "Terminado";
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
        std::cout << "ERROR" << std::endl;
        exit(1);
    }
    Segmento *s = (Segmento*) shmat(shm_id, NULL, 0);
    int array_size = s->nProcesos;
    Proceso lista_procesos[array_size];
    for(int i = 0; i < array_size; i++)
        lista_procesos[i] = s->buffer[i];

    // Ordenando la lista de procesos por Prioridad.
    int i,j;
    Proceso key;  
    for (i = 1; i < array_size; i++) 
    {  
        key = lista_procesos[i];  
        j = i-1;  
        while (j >= 0 && lista_procesos[j].prioridad > key.prioridad) 
        {  
            lista_procesos[j+1] = lista_procesos[j];  
            j = j-1;  
        }  
        lista_procesos[j+1] = key;  
    }  

    std::cout << "-------------Ejecutando lista de procesos-------------" << std::endl;

    std::string t_estado;
    for(int i = 0; i < array_size; i++)
    {
        int sleep_time = lista_procesos[i].cpuTime <= 60 ? lista_procesos[i].cpuTime*1000000 : 60*1000000; 
        usleep(sleep_time);
        std::cout << "ID: " << lista_procesos[i].id << " | ";
        std::cout << "Prioridad: " << lista_procesos[i].prioridad << " | ";
        std::cout << "Estado: " << print_estado(lista_procesos[i].estado) << " | ";
        std::cout << "CpuTime: " << lista_procesos[i].cpuTime << '\n';
    }
    return 0;
}
