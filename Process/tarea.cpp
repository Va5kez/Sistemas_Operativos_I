#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// Ejercicio #1 
// Programe el shell de manera se puedan agregar una opcion: ls -l

int main()
{
    int x=5;
    int id;
    char linea[50];
    char comando[30];
    char opcion[30];
    char *p,*q;
    while (1) {
        cout << "::>";
        cin.getline(linea,80);
        p = strtok(linea," ");
        q = strtok(NULL," ");
        
        id = fork();
        if (id == 0) {
            if (p != NULL)
                execlp(p,p,q,NULL);
            else 
                execlp(p,p,NULL);
        }
    }
    return 0;
}