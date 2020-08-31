/*
  Prueba hilos de control
  Encuentre la llave con que se encripto el mensaje. 
  INPUT: cadena original (mensaje) y la cadena encriptada  (mensajeE)
  Usuario: Min:4 caracteres   Max: 7 caracteres 
  Crear tres hilos de control que encuentren la llave con que se encripto el mensaje
  Hilo 1 : Evalua cadenas de 4 caracteres
  Hilo 2 : Evalua cadenas de 5 caracteres donde la primera letra de la clave estan en el rango de  A..L
  Hilo 3 : Evalua cadenas de 5 caracteres donde la primera letra de la clave estan en el rango de  M..Z
  Hilo 4 : Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  A..F
  Hilo 5 : Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  G..L
  Hilo 6 : Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  M..R
  Hilo 7 : Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  S..Z
  Hilo 8 : Construye y evalua un 1,000,000 de pruebas aleatorias de claves de 7 caracteres 
		--NO necesariamente distintas -- Pueda que no se encuentre la clave. 
  Haga pruebas con las siguientes llaves: MUND, MUNDO, MUNDOS, MUNDANO

*/
#include <iostream>
#include <string>
using namespace std;
class Vig {
   public:
      string k;
   Vig(string k) {
      for (int i = 0; i < k.size(); ++i) {
         if (k[i] >= 'A' && k[i] <= 'Z')
            this->k += k[i];
         else if (k[i] >= 'a' && k[i] <= 'z')
            this->k += k[i] + 'A' - 'a';
      }
   }
   void setKey(string k) {
      for (int i = 0; i < k.size(); ++i) {
         if (k[i] >= 'A' && k[i] <= 'Z')
            this->k += k[i];
         else if (k[i] >= 'a' && k[i] <= 'z')
            this->k += k[i] + 'A' - 'a';
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


/*char llave[6];
struct Prueba {
    string mensaje;
    string mensajeE;
    string llave;
};

Prueba prueba;
Vig v("MUNDOS");*/

struct Parameters{
    Parameters(string a, string b , int c, int d): original_input(a), encrypted_input(b), size(c), id_th(d){}
    string original_input;
    string encrypted_input;
    int size;
    int id_th;
};

void *check_combinations(void *ptr);
void nextKey(int size, char *key, int currPos, int th_id);

int main() {
    Vig v("MUNDO");
    string ori ="Thisistutorialspoint";
    string encrypt = v.encryption(ori);
    string decrypt = v.decryption(encrypt);
   
    cout << "Original Message: " << ori << endl;
    cout << "Encrypted Message: " << encrypt << endl;
    cout << "Decrypted Message: " << decrypt << endl;
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;
    Parameters size_4(ori, encrypt, 4, 1);   // Evalua cadenas de 4 caracteres
    Parameters size_5(ori, encrypt, 5, 2);   // Evalua cadenas de 5 caracteres donde la primera letra de la clave estan en el rango de  A..L
    Parameters size_5_2(ori, encrypt, 5, 3); // Evalua cadenas de 5 caracteres donde la primera letra de la clave estan en el rango de  M..Z
    Parameters size_6(ori, encrypt, 6, 4);   // Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  A..F
    Parameters size_6_2(ori, encrypt, 6, 5); // Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  G..L
    Parameters size_6_3(ori, encrypt, 6, 6); // Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  M..R
    Parameters size_6_4(ori, encrypt, 6, 7); // Evalua cadenas de 6 caracteres donde la primera letra de la clave estan en el rango de  S..Z
    int iret1 = pthread_create( &thread1, NULL, check_combinations, (void*) &size_4);
    int iret2 = pthread_create( &thread2, NULL, check_combinations, (void*) &size_5);
    int iret3 = pthread_create( &thread3, NULL, check_combinations, (void*) &size_5_2);
    int iret4 = pthread_create( &thread4, NULL, check_combinations, (void*) &size_6);
    int iret5 = pthread_create( &thread5, NULL, check_combinations, (void*) &size_6_2);
    int iret6 = pthread_create( &thread6, NULL, check_combinations, (void*) &size_6_3);
    int iret7 = pthread_create( &thread7, NULL, check_combinations, (void*) &size_6_4);

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); 
    pthread_join( thread3, NULL);
    pthread_join( thread4, NULL);
    pthread_join( thread5, NULL);
    pthread_join( thread6, NULL);
    pthread_join( thread7, NULL);

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
    int id = params->id_th;
    char possible_key[size];
    possible_key[0] = '\0';
    char initial_key[size];
   if(id == 1 || id == 2 || id == 4)
   {
      for(int i = 0; i < size; i++)
         initial_key[i] = 'A';
   }
   else
   {
      if(id == 3 || id == 6)
         initial_key[0] = 'M';
      else if(id == 5)
         initial_key[0] = 'G';
      else if(id == 7)
         initial_key[0] = 'S';
      for(int i = 1; i < size; i++)
         initial_key[i] = 'A';
   }
    int k = 0;
    bool start = false;
    int counter = 0;
    while(k == 0)
    {
        nextKey(size, possible_key, 0, id);
        if(string(possible_key).substr(0,size).compare(string(initial_key)) == 0 && start == true)
            k = 2;
        else
            k = TestKey(ori, oriE, string(possible_key));
        start = true; 
        counter++;  
    }
    if( k == 1)
        cout << "Key found: " << string(possible_key) << " . Iteration # " << counter << '\n';
}

void nextKey(int size, char *key, int currPos, int th_id){
   if(currPos >= size || key[0] == '\0'){
        for(int i = 0; i < size; i++)
        {
           key[i] = 'A';
        }    
        return;
   }
   key[currPos]++;
   if(th_id = 1)
   {
      if(key[currPos] > 'Z'){
         key[currPos] = 'A';
         nextKey(size, key, ++currPos, th_id);
      }
   }
   else
   {
      if(th_id == 2)
      {
         cout << currPos << '\n';
         if(currPos == 0 && key[currPos] > 'L'){
            key[currPos] = 'A';
            nextKey(size, key, ++currPos, th_id);
         }
         else
         {
            if(key[currPos] > 'Z'){
               key[currPos] = 'A';
               nextKey(size, key, ++currPos, th_id);
            }
         }
      }
      else if(th_id == 3)
      {
         if(currPos == 0 && key[currPos] > 'Z'){
            key[currPos] = 'M';
            nextKey(size, key, ++currPos, th_id);
         }
         else
         {
            if(key[currPos] > 'Z'){
               key[currPos] = 'A';
               nextKey(size, key, ++currPos, th_id);
            }
         }
      }
      else if(th_id == 4)
      {
         if(currPos == 0 && key[currPos] > 'F'){
            key[currPos] = 'A';
            nextKey(size, key, ++currPos, th_id);
         }
         else
         {
            if(key[currPos] > 'Z'){
               key[currPos] = 'A';
               nextKey(size, key, ++currPos, th_id);
            }
         }
      }
      else if(th_id == 5)
      {
         if(currPos == 0 && key[currPos] > 'L'){
            key[currPos] = 'G';
            nextKey(size, key, ++currPos, th_id);
         }
         else
         {
            if(key[currPos] > 'Z'){
               key[currPos] = 'A';
               nextKey(size, key, ++currPos, th_id);
            }
         }
      }
      else if(th_id == 6)
      {
         if(currPos == 0 && key[currPos] > 'R'){
            key[currPos] = 'M';
            nextKey(size, key, ++currPos, th_id);
         }
         else
         {
            if(key[currPos] > 'Z'){
               key[currPos] = 'A';
               nextKey(size, key, ++currPos, th_id);
            }
         }
      }
      else if(th_id == 7)
      {
         if(currPos == 0 && key[currPos] > 'Z'){
            key[currPos] = 'S';
            nextKey(size, key, ++currPos, th_id);
         }
         else
         {
            if(key[currPos] > 'Z'){
               key[currPos] = 'A';
               nextKey(size, key, ++currPos, th_id);
            }
         }
      }
   }
}
