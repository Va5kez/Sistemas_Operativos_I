#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// Ejercicio #1 
// Programe el shell de manera se puedan agregar una opcion: ls -l

int main()
{
    char linea[50];
    char *main_command;
    char *command_list[30];
    char *p;
    int id;
    while (1) {
        cout << "::>";
        cin.getline(linea,80);
        // strtok(string to split, delimiter)
        p = strtok(linea," ");
        main_command = p;
        int i = 0;
        while(p!=NULL)
        {
            command_list[i] = p;
            p = strtok(NULL, " ");
            i++;
        }
        command_list[i] = NULL;
        // Creating child process
        id = fork();
        if(id == 0)
        {
            execvp(main_command, command_list);
            cin.clear();
        }
    }
    return 0;
}