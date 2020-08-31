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
        execl("/bin/ls","/bin/ls", NULL);
    } 
    return 0;
}