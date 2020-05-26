#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>


#define MAX 10000
using namespace std;
class Evento{
private:
    string tipoEvento;
    int tiempoEvento;
public:

    //constructor predeterminado
    Evento(){
        this->tiempoEvento = 0;
        this->tipoEvento = "";
    };

    // setters
    void setTipo(string evento){
        this->tipoEvento = evento;
    };
    void setTiempo(int tiempo){
        this->tiempoEvento = tiempo;
    };

    // getters
    string getTipo(){
        return this->tipoEvento;
    };
    int getTiempoe(){
        return this->tiempoEvento;
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
    Reloj(){
        evento =  Evento();
    };

    void setNumero(int Numero){numero=Numero;};
    void setNombre(string Nombre){nombre=Nombre;};
    void setTipo(string tipoo){tipo=tipoo;};
    void setTiempo(int tiempoo){tiempo=tiempoo;};

    void setEvento(int tiempo){
        if(this->getTipo() == "periodico"){
            evento.setTiempo(tiempo);
            evento.setTipo("periodico");
        }else if(this->getTipo() == "aleatorio"){
            evento.setTiempo(rand() % tiempo);
            evento.setTipo("aleatorio");
        }
    }

    int getNumero(){return numero;};
    string getNombre(){return nombre;};
    string getTipo(){return tipo;};
    int getTiempo(){return tiempo;};
    Evento getEvento(){
        return this->evento;
    }

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

    string cadena;
    ifstream lectura("laconchadetumadre.txt");
    int contador = 0;
    vector<string> words;
    vector<Reloj> relojes;

    while (!lectura.eof()) {
        contador++;
        lectura >> cadena;

        words.push_back(cadena);

        if (contador == 4) {

            Reloj reloj = Reloj();


            reloj.setNumero(stoi(words[0]));
            reloj.setNombre(words[1]);
            reloj.setTipo(words[2]);
            reloj.setTiempo(stoi(words[3]));


            relojes.push_back(reloj);

            contador = 0;
            words.clear();
        }
    }
    for(int i=0;i<10;i++){
        cout<< relojes[i].getNumero()<<"   "<<relojes[i].getNombre()<<" "<<relojes[i].getTipo()<<" "<<relojes[i].getTiempo()<<endl;


        relojes[i].setEvento(relojes[i].getTiempo());
        cout << relojes[i].getEvento().getTiempoe()  << " " <<  relojes[i].getEvento().getTipo() << endl;
    }
    lectura.close();



}