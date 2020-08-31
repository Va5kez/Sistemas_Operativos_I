#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    int x=5;
    if (fork() == 0) {
        cout << "Proceso hijo" << endl;
        cout << x << endl;
    } else {
        cout << "Proceso padre" << endl;
        cout << x << endl;
    }

    return 0;
}