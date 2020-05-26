#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;


// clase Evento
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

    //destructor
    ~Evento();

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
    int getTiempo(){
        return this->tiempoEvento;
    };
};


// clase Reloj
class Reloj{
private:
    int numReloj;
    string nombreReloj;
    string tipoReloj;
    int tiempo;
    Evento evento;
public:
    // constructor
    Reloj(){
        evento =  Evento();
    };

    // Metodos
    void setEvento(int tiempo){
        if(this->getReloj() == "periodico"){
            evento.setTiempo(tiempo);
            evento.setTipo("periodico");
        }else if(this->getReloj() == "aleatorio"){
            evento.setTiempo(rand() % tiempo);
            evento.setTipo("aleatorio");
        }
    }

    // setters
    void setNumero(int numero){
        this->numReloj = numero;
    };

    void setNombre(string nombre){
        this->nombreReloj = nombre;
    };

    void setReloj(string tipo){
        this->tipoReloj = tipo;
    };

    void setTiempoRepe(int tiempo){
        this->tiempo = tiempo;
    }

    // getters

    int getNumero(){
        return this->numReloj;
    };

    string getNombre(){
       return this->nombreReloj;
    };

    string getReloj(){
        return this->tipoReloj;
    };

    int getTiempo(){
        return this->tiempo;
    }

    Evento getEvento(){
        return this->evento;
    }

};

// clase Planificador
class Planificador{
private:
    Reloj reloj;
    int numeroRelojes;
public:
    void agregarReloj();
    Evento getProximoEvento();
    void run();
};

int main() {
    string cadena;
    /*int aleatorio;
    string tipo;
    ofstream fs("nombre.txt");

    for(int i=0;i<100;i++){
        aleatorio = rand() % 100;
        if(aleatorio % 2 == 0){
            tipo = "aleatorio";
        }else{
            tipo = "periodico";
        }

        fs << to_string(i+1) + " Reloj_" + to_string(i+1) + " " + tipo + " " + to_string(aleatorio) << endl;
    }*/

    ifstream fe("nombre.txt");
    int contador=0;
    vector<string> words;
    vector<Reloj> relojes;

    while (!fe.eof()) {
            contador ++;
            fe >> cadena;

            words.push_back(cadena);

            if(contador == 4){

                Reloj reloj = Reloj();

                reloj.setNumero(stoi(words[0]));
                reloj.setNombre(words[1]);
                reloj.setReloj(words[2]);
                reloj.setTiempoRepe(stoi(words[3]));

                relojes.push_back(reloj);

                contador = 0;
                words.clear();
            }
    }

    for(int i=0;i<100;i++){
        cout << relojes[i].evento << endl;
    }

    fe.close();
    return 0;
}
