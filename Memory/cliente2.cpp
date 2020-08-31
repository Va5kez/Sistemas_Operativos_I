#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
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
         cout << "Error while trying to get shmid \n" <<endl;
         exit(1);
    }
    shm_ptr = (char *) shmat(shm_id, NULL, 0);  /* attach */
    char *main_command;
    char *command_list[30];
    char *p;
    while (1) {
        p = strtok(shm_ptr, " ");
        main_command = p;
        //cout << "Exec Command: " << main_command << '\n';
        int i = 0;
        while(p!=NULL)
        {
            command_list[i] = p;
            p = strtok(NULL, " ");
            i++;
        } 
        command_list[i] = NULL;
        // Creating child process
        int id = fork();
        if(i > 1)
        {
            int id = fork();
            if( id == 0)
            {
                cout << "Exec Command: " << main_command << '\n';
                int status_code = execvp(main_command, command_list);
                if(status_code == -1)
                {
                    cout << "Comando " << main_command << " no encontrado" << endl;
                }
            }
            /*else if(command_list[0] != NULL)
            {
                int status_code = execlp(command_list[0], command_list[0], NULL);
                if(status_code == -1)
                {
                    cout << "Comando " << main_command << " no encontrado" << endl;
                }
            }*/      
        }
        usleep(2000000);
    }
    return 0;
}