#ifndef _STRUCTS_H_
#define _STRUCTS_H_

enum Estados
{
    Nuevo,
    Listo,
    En_espera,
    En_ejecucion,
    Terminado
};

struct Proceso
{
    /*Proceso(int p_id, int p_prioridad, Estados p_estado, int p_cpuTime) : 
            id(p_id), prioridad(p_prioridad), estado(p_estado), cpuTime(p_cpuTime){}
    ~Proceso(){}*/
    int id;
    int prioridad;  // Min:1    Max:10
    Estados estado; 
    int cpuTime;    // Min:1    Max:100
};

struct Segmento
{
    // C++ >= 11 es valido = 0, en C no
    int entrada = 0;
    int salida = 0;
    int nProcesos = 0;
    Proceso buffer[10];
};

#endif