#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;

// Ejercicio #1 
// Programe el shell de manera se puedan agregar una opcion: ls -l

int main()
{
    /*int x=5;*/
    int id;
    char linea[80];
    char comando[30];
    /*char opcion[30];
    char *p,*q;*/
    while(1){
        cout << "::>";
        cin.getline(linea,80);
            
        const char s[4] = " "; 
        char* tok; 

        // Use of strtok 
        // get first token 
        tok = strtok(linea, s); 
        vector<char*> opciones;
        // Checks for delimeter 
        while (tok != 0) { 
            cout <<tok<<endl; 
            opciones.push_back(tok);
            // Use of strtok 
            // go through other tokens 
            tok =strtok(0, s);
        } 
        int cant = opciones.size()+1;
        cout<< cant<< " print 2"<<endl;
        char* argumentos[cant];
        for(int c=0;c<opciones.size();c++) {
            argumentos[c] = opciones.at(c);
        }
        cout<<opciones.size() << " print 3" <<endl;
        argumentos[opciones.size()]=NULL;
        int a = fork();
        if(a == 0)
        {
            if (opciones.size()>1){
                cout<< "Momento antes de la tragedia"<<endl;
                execvp(argumentos[0],argumentos);
            }
            else if(argumentos[0]!=NULL)
                execlp(argumentos[0],argumentos[0], NULL);
        }
    }
    return 0;
}