#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

class Vig {
    public:
    string k; // 1
    Vig(string k) {
        for (int i = 0; i < k.size(); ++i) {
            if (k[i] >= 'A' && k[i] <= 'Z')
                this->k += k[i]; // 1
            else if (k[i] >= 'a' && k[i] <= 'z')
                this->k += k[i] + 'A' - 'a'; // 1
        }
    }
    string encryption(string t) {
        string output;
        for (int i = 0, j = 0; i < t.length(); ++i) {
            char c = t[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            output += (c + k[j] - 2 * 'A') % 26 + 'A'; //added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
            j = (j + 1) % k.length();
        }
        return output;
    }
    string decryption(string t) {
        string output;
        for (int i = 0, j = 0; i < t.length(); ++i) {
            char c = t[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            output += (c - k[j] + 26) % 26 + 'A';//added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
            j = (j + 1) % k.length();
        }
        return output;
    }
};

// Encuentre la llave con que se encripto el mensaje. 
// INPUT: cadena original (ori) y la cadena encriptada  (encrypt)
// Usuario: Min:4 caracteres   Max: 6 caracteres 
//  Crear tres hilos de control que encuentren la llave con que se encripto el mensaje
//  Hilo 1 : cadenas de 4 caracteres
//  Hilo 2 : cadenas de 5 caracteres
//  Hilo 3 : cadenas de 6 caracteres

//char llave[6];
//void encontrarLlave(char *ori, char *oriE, char *llave);

// # de Combinaciones para 4 caracteres ->       456,976  // Asumiendo solo mayusculas
// # de Combinaciones para 5 caracteres ->    11,881,376  // Asumiendo solo mayusculas
// # de Combinaciones para 6 caracteres ->   308,915,776  // Asumiendo solo mayusculas + numeros[0-9]

struct Parameters{
    Parameters(string a, string b , int c): original_input(a), encrypted_input(b), size(c){}
    string original_input;
    string encrypted_input;
    int size;
};

void *check_combinations(void *ptr);
void nextKey(int size, char *key, int currPos);

int main() {
    Vig v("MUNDO");
    string ori ="Thisistutorialspoint";
    string encrypt = v.encryption(ori);
    string decrypt = v.decryption(encrypt);
   
    cout << "Original Message: " << ori << endl;
    cout << "Encrypted Message: " << encrypt << endl;
    cout << "Decrypted Message: " << decrypt << endl;
    pthread_t thread1, thread2, thread3;
    Parameters size_4(ori, encrypt, 4);
    Parameters size_5(ori, encrypt, 8);
    //Parameters size_6(ori, encrypt, 6);
    int iret1 = pthread_create( &thread1, NULL, check_combinations, (void*) &size_4);
    int iret2 = pthread_create( &thread2, NULL, check_combinations, (void*) &size_5);
    //int iret3 = pthread_create( &thread3, NULL, check_combinations, (void*) &size_6);

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); 
    //pthread_join( thread3, NULL);

    return 0;
}

bool TestKey(string ori, string oriE, string temp_key)
{
    Vig tem(temp_key);
    string enc = tem.encryption(ori);
    return enc.compare(oriE) == 0;
}

void *check_combinations(void *ptr)
{
    Parameters *params;
    params = (Parameters*) ptr;
    string ori = params->original_input;
    string oriE = params->encrypted_input;
    int size = params->size;
    char possible_key[size];
    possible_key[0] = '\0';
    char initial_key[size];
    for(int i = 0; i < size; i++)
            initial_key[i] = 'A';
    int k = 0;
    bool start = false;
    int counter = 0;
    //cout << string(initial_key) << '\n';
    while(k == 0)
    {
        nextKey(size, possible_key, 0);
        if(string(possible_key).substr(0,size).compare(string(initial_key)) == 0 && start == true)
            k = 2;
        else
            k = TestKey(ori, oriE, string(possible_key));
        start = true; 
        counter++;  
    }
    if( k == 1)
        cout << "Key found: " << string(possible_key) << " . Iteration # " << counter << '\n';
    else
        cout << "Key not found on key size: " << size << '\n';
}

void nextKey(int size, char *key, int currPos){
   if(currPos >= size || key[0] == '\0'){
        for(int i = 0; i < size; i++)
            key[i] = 'A';
        return;
   }
   key[currPos]++;
   if(key[currPos] > 'Z'){
      key[currPos] = 'A';
      nextKey(size, key, ++currPos);
   }
}
