#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    int x=5;
    int id;
    char comando[30];
    while (1) {
        cout << "::>";
        cin.getline(comando,80);
        id = fork();
        if (id == 0) {
            execlp(comando,comando,NULL);
        }
    }
    return 0;
}