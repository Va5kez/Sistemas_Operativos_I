#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    int x=5;
    int id;
    id = fork();
    if (id == 0) {
        cout << "Proceso hijo" << endl;
        cout << x << endl;
    } else {
        cout << "Proceso padre" << endl;
        cout << x << endl;
        cout << id << endl;
    }

    return 0;
}