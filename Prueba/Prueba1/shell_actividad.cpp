#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// Actividad de programación fork()  y exec()
// Programe el shell de manera se puedan agregar una o más opciones: ls -l -a
// Por ejemplo
// ls -l -a
// ps -e -f
// kill -9 process_id
// ls -l -a -s

// Ademas, debe imprimir "comando no encontrado" si el comando ingresado no existe. 
//La función execl retorna un valor de erro para indicar que el comando no fue encontrado. 

// Modifique el siguiente programa y agregue las especificaciones que se piden. 
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
        // Creando el proceso hijo
        id = fork();
        if(id == 0)
        {
            int code_error = execvp(main_command, command_list);
            if(code_error == -1)
            {
                cout << "Comando " << main_command << " no encontrado" << endl;
            }
            cin.clear();
        }
    }
    return 0;
}