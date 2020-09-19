#include <iostream>
#include <pthread.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>


void *generate_random_nums(void *);
void *get_ref_num(void *);
void *print_page_fail(void *);

std::queue<int> rand_n;
int memory[20];
int count_fails = 0;

int main()
{
    pthread_t gen_num, reference , print_fails;
    int create;
    create = pthread_create(&gen_num, NULL, &generate_random_nums, NULL);
    if(create !=0)
    {
        std::cout << "Fallo en la creacion del hilo de control para la generacion de numeros aleatorios." << std::endl; 
        exit(EXIT_FAILURE);
    }
    create = pthread_create(&reference, NULL, &get_ref_num, NULL);
    if(create !=0)
    {
        std::cout << "Fallo en la creacion del hilo de control para obtener la referencia de pagina." << std::endl; 
        exit(EXIT_FAILURE);
    }
    create = pthread_create(&print_fails, NULL, &print_page_fail, NULL);
    if(create !=0)
    {
        std::cout << "Fallo en la creacion del hilo de control para la impresion de fallos." << std::endl; 
        exit(EXIT_FAILURE);
    }

    pthread_join(gen_num, NULL);
    pthread_join(reference, NULL);
    pthread_join(print_fails, NULL);

    return 0;
}

void *generate_random_nums(void *)
{
    while(1)
    {
        srand (time(NULL));
        for(int i = 0; i < 100; i++)
            rand_n.push(rand() % 100);
        std::cout << "Primer numero " << rand_n.front() << std::endl;
        std::cout << "Ultimo numero " << rand_n.back() << std::endl;
        sleep(300);
        std::cout << "Van 100 mas" << std::endl;
    }
}

void *get_ref_num(void *)
{
    int pos = 0;
    bool array_full = false;
    while(1)
    {
        sleep(3);
        int temp = rand_n.front();
        rand_n.pop();
        bool found = false;
        for(int i = 0; i < 20; i++)
        {
            if(temp == memory[i])
                found = true;
        }
        if(!found)
        {
            count_fails++;
            if(pos == 20)
                array_full = true;

            if(!array_full)
            {
                memory[pos] = temp;
                pos++;
            }
            else
            {
                int max_val = 0;
                int new_pos;
                for(int i = 0; i < 20; i++)
                {
                    if(memory[i] > max_val)
                    {
                        new_pos = i;
                        max_val = memory[i];
                    }
                }
                memory[new_pos] = temp;
            }
        }
        for(int i = 0; i < 20; i++)
            std::cout << memory[i] << " ";
        std::cout << '\n';
    }
}

void *print_page_fail(void *)
{
    while(1)
    {
        sleep(10);
        std::cout << "Numero de fallos de pagina: " << count_fails << std::endl; 
    }
}