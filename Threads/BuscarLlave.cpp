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

// Encuentre la llave con que se encripto el mensaje. 
// INPUT: cadena original (ori) y la cadena encriptada  (encrypt)
// Usuario: Min:4 caracteres   Max: 6 caracteres 
//  Crear tres hilos de control que encuentren la llave con que se encripto el mensaje
//  Hilo 1 : cadenas de 4 caracteres
//  Hilo 2_ : cadenas de 5 caracteres
//  Hilo 3 : cadenas de 6 caracteres
char llave[6];
struct Prueba {
    string mensaje;
    string mensajeE;
    string llave;
};

Prueba prueba;
Vig v("MUNDO");

void *buscarLlave4(void *);
void *buscarLlave5(void *);
void *buscarLlave6(void *);
int main() {
    prueba.mensaje ="Thisistutorialspoint";
    pthread_t thread1, thread2, thread3;
    prueba.mensajeE = v.encryption(prueba.mensaje); 
    cout << "Mensaje: " << prueba.mensaje << endl;
    cout << "Mensaje encriptado: " << prueba.mensajeE << endl;
    int  iret1, iret2;
    iret1 = pthread_create( &thread1, NULL, buscarLlave4, (void*) NULL);
    iret2 = pthread_create( &thread2, NULL, buscarLlave5, (void*) NULL);
 //   iret2 = pthread_create( &thread3, NULL, buscarLlave4,(void*) NULL);   
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
 //   pthread_join( thread2, NULL); 
 //   pthread_join( thread3, NULL);
   cout << "La llave es: "<< prueba.llave <<endl;
   
}

void *buscarLlave4(void *) {
    string llave = "";
    string mE = "";
    for (int i=65; i<=90;i++) {
        llave += (char)i;
        for (int j=65; j<=90;j++) {
            llave += (char)j;
            for (int k=65; k<=90;k++) {
                llave += (char)k;
                for (int m=65; m<=90;m++) {
                    llave += (char)m;
                    Vig v(llave);
                    mE = v.encryption(prueba.mensaje);
                    if (prueba.mensajeE ==mE) {
                        prueba.llave = llave;
                        return NULL;
                    }
                    llave = llave.substr(0, llave.length() - 1);
                }
                llave = llave.substr(0, llave.length() - 1);
            }
            llave = llave.substr(0, llave.length() - 1);
        }
        llave = llave.substr(0, llave.length() - 1);
    }
}

void *buscarLlave5(void *) {
    string llave = "";
    string mE = "";
    for (int i=65; i<=90;i++) {
        llave += (char)i;
        for (int j=65; j<=90;j++) {
            llave += (char)j;
            for (int k=65; k<=90;k++) {
                llave += (char)k;
                for (int m=65; m<=90;m++) {
                    llave += (char)m;
                    for (int n=65; n<=90;n++) {
                        llave += (char)n;
                        Vig v(llave);
                        mE = v.encryption(prueba.mensaje);
                        if (prueba.mensajeE ==mE) {
                            prueba.llave = llave;
                            return NULL;
                        }
                        llave = llave.substr(0, llave.length() - 1);
                    }
                    llave = llave.substr(0, llave.length() - 1);
                }
                llave = llave.substr(0, llave.length() - 1);
            }
            llave = llave.substr(0, llave.length() - 1);
        }
        llave = llave.substr(0, llave.length() - 1);
    }
}