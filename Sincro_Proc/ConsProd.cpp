#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
const int N = 10;

struct Buffer {
int entrada=0;
int salida=0;
int n =0;
int datos[N];
};

Buffer buffer;
sem_t vacio;
sem_t lleno;
sem_t mutexE;
sem_t mutexS;

void *productor(void *);
void *consumidor(void *);
void *snapshot(void *);

int main() {
    const int nProd=5;
    const int nCons=3;
    pthread_t tid[nProd];
    pthread_t conTid[nCons];
    pthread_t snapshotTid;
   
    sem_init(&vacio,0,N);
    sem_init(&lleno,0,0);
    sem_init(&mutexE,0,1);
    sem_init(&mutexS,0,1);
   
    int error;
    for (int i=0; i<nProd;i++) {
        error = pthread_create(&(tid[i]), NULL, &productor, NULL);
        if (error != 0)
            cout << "Hilo productor no creado" << endl;
    }
    for (int i=0; i<nCons;i++) {
        error = pthread_create(&(conTid[i]), NULL, &consumidor, NULL);
        if (error != 0)
            cout << "Hilo consumidor no creado" << endl;
    }    
   
    error = pthread_create(&snapshotTid, NULL, &snapshot, NULL);
    if (error != 0)
        cout << "Hilo snapshop no creado" << endl;
   
    for (int i=0; i<nProd;i++) {
        pthread_join(tid[i], NULL);
    }
    for (int i=0; i<nCons;i++) {
        pthread_join(conTid[i], NULL);
    }      
   
    pthread_join(snapshotTid, NULL);    
    wait(NULL);
}

void *productor(void * ) {
    srand(time(NULL));
    int x;
    cout << "En productor" << endl;
    while (1) {
        x = rand()%100;
        sem_wait(&vacio);
        sem_wait(&mutexE);
        buffer.datos[buffer.entrada] = x;
        buffer.n++;
        buffer.entrada= (buffer.entrada+1)%N;
        sem_post(&mutexE);
        sem_post(&lleno);
        sleep(2);
    }
}
void *consumidor(void * ) {
     int x;
     cout << "En consumidor" << endl;
     while (1) {
      sem_wait(&lleno);
      sem_wait(&mutexS);
      x= buffer.datos[buffer.salida];    
      cout << "x= " << x << endl;
      buffer.n--;
      buffer.salida= (buffer.salida+1)%N;
      sem_post(&mutexS);
      sem_post(&vacio);
      sleep(2);
     }
}

void *snapshot(void * ) {
    cout << "En Snapshot" << endl;
    while (1) {
        sleep(7);
        sem_wait(&mutexE);
        sem_wait(&mutexS);
        cout << "[";
        for (int i=0; i<buffer.n; i++) {
            cout << buffer.datos[(buffer.salida+i)%N] << " ";
        }
        cout << "]"<< endl;
        sem_post(&mutexE);
        sem_post(&mutexS);    
    }
}