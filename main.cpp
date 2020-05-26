#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10000
using namespace std;
 class Evento
{
private:
    string tipoEvento;
    int tiempoEvento;

public:
    void setTipo(string evento){
        this->tipoEvento=evento;
    };



};

 class Reloj
{
private:
        int numero;
        string nombre;
        string tipo;
        int tiempo;
        Evento evento;


public:
        void setNumero(int Numero){numero=Numero;};
        void setNombre(string Nombre){nombre=Nombre;};
        void setTipo(string tipoo){tipo=tipoo;};
        void setTiempo(int tiempoo){tiempo=tiempoo;};
        void setEvento (Evento evento1){evento=evento1;};

        int getNumero(){return numero;};
        string getNombre(){return nombre;};
        string getTipo(){return tipo;};
        int getTiempo(){return tiempo;};

        //void segundosPeriodicos(){segundos=tiempo;};
        //void segundosAleatorios(){segundos=rand()%tiempo;};
        //void delay(int segundos)
        //{
          //  int milli_seconds = 1000 * segundos;
            //clock_t start_time = clock();

            // looping till required time is not achieved
            //while (clock() < start_time + milli_seconds)
                ;

        //}
        //int getsegundos(){
         //   return segundos;
       // }

};
// clase Planificador
class Planificador{
private:
    Reloj reloj;
    int numeroRelojes;
public:
    void agregarReloj(Reloj relojaux);
    Evento getProximoEvento();
    void run();
};



int main() {

    char tiempo[20];
    string linea;


    ifstream lectura("laconchadetumadre.txt");
    if (lectura.is_open()) {
        while (getline(lectura, linea)) // IMPRIME EL ARCHIVO LINEA POR LINEA
        {
            Reloj *reloj = new Reloj();//Por cada linea se crea un reloj.
            cout << linea << "\n";
            int j = linea.length();
            for (int i = 0; (i < j); i++) {
                //MANEJO DE NUMERO DE RELOJ
                if(linea.at(0))
                {
                    reloj->setNumero(linea.at(0)-'0');//EL restar '0' es porque es por el pasaje de char en asii con respecto a un int.
                }
                //NOMBRE DE RELOJ
                if(linea.at(i)=='r')//Suponiendo que todos los nombre van a ser del tipo reloj_N°
                {
                    reloj->setNombre(linea.substr(2,7));
                    cout<<"El numero del reloj: "<<reloj->getNumero()<<" cuyo nombre es: "<<reloj->getNombre()<<endl;
                }

                    //MANEJO DE TIPO
                    if(linea.at(i) == 'p') {

                        reloj->setTipo("periodico");
                        cout << "Encontre un reloj de tipo  " << reloj->getTipo() << "\n";

                    } else if (linea.at(i) == 'a' && linea.at(i + 1) == 'l') {

                        reloj->setTipo("aleatorio");
                        cout << "Encontre un reloj" << "  " << reloj->getTipo() << "\n";
                    }

                    //MANEJO DE TIEMPO.

                  if(i==j-1)
                  {
                      if(linea.at(j-2)!=' ')
                      {
                        reloj->setTiempo(stoi(linea.substr(i-1,i)) );//Stoi es una funcion que cambia de tipo string a int.
                      } else
                      {
                          reloj->setTiempo(linea.at(j-1)- '0');
                      }
                      cout<<"El tiempo es: "<< reloj->getTiempo()<<endl;
                  }

                //CREACION DE EVENTO















                    /* if(reloj->getTipo()=="periodico")
                     {
                        if(reloj->getTiempo()==reloj->getsegundos())
                        {

                            reloj->segundosPeriodicos();//Seteo segundos periodicos
                            reloj->delay(reloj->getsegundos());
                            Reloj<Evento<string>> *evento= new Reloj<Evento<string>>();


                        }
                     }
                     if(reloj->getTipo()=="aleatorio")
                     {
                         reloj->segundosAleatorios();//Seteo segundos aleatorios
                         reloj->delay(reloj->getsegundos());
                         Reloj<Evento<string>> *evento= new Reloj<Evento<string>>();

                     }*/

                }
            }
        }

    lectura.close();
    }

