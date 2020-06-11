#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>


using namespace std;

#include "Lista.h"
#include "Heap.h"
#include "BinomialHeap.h"
ofstream salida;
// clase Evento
class Evento{
private:
    string nombreEvento;
    int numeroEvento;
    string tipoEvento;
    int tiempoEvento;
public:

    //constructor predeterminado
    Evento(){
        this->nombreEvento = "";
        this->numeroEvento = 0;
        this->tiempoEvento = 0;
        this->tipoEvento = "";
    };

    // setters

    void setNombreEvento(string nombre){
        this->nombreEvento = nombre;
    };
    void setNumeroEvento(){
        this->numeroEvento++;
    };
    void setTipo(string evento){
        this->tipoEvento = evento;
    };
    void setTiempo(int tiempo){
        this->tiempoEvento = tiempo;
    };

    // getters
    string getNombreEvento(){
        return this->nombreEvento;
    };

    int getNumeroEvento(){
        return this->numeroEvento;
    };

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
        evento = Evento();
    };

    // Metodos
    Evento setEvento(int tiempo,string nombreReloj){
        this->evento.setTiempo(tiempo);
        this->evento.setNombreEvento(nombreReloj);
        this->evento.setNumeroEvento();
        return evento;
    }

    void finalizarEvento(){
        this->evento = Evento();
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





// Planificador con lista y QuickSort
class PlanificadorConLista{
private:
    struct Lista<Reloj> *relojes;
    struct Lista<Evento> *eventos;
public:
    PlanificadorConLista(vector<vector<string>> wordsRelojes){
        relojes = NULL;
        eventos = NULL;
        // agrega todos los relojes
        for(string::size_type i=0;i<wordsRelojes.size();i++){
            agregarReloj(wordsRelojes[i]);
        }
    };


    // metodos

    void agregarReloj(vector<string> words){
        // Crea un reloj
        Reloj reloj = Reloj();
        reloj.setNumero(stoi(words[0]));
        reloj.setNombre(words[1]);
        reloj.setReloj(words[2]);
        reloj.setTiempoRepe(stoi(words[3]));


        //Agrega el Reloj a la lista
        relojes->push(&relojes,reloj);


    }

    Evento getProximoEvento(int i){
        return eventos->GetNth(eventos,i)->data;
    }
    int getprox50(int k){
		//int fin;
		for(int x=0;x<50;x++){
		        Evento proximoEvento = getProximoEvento(k);
				time_t t = time(0) + proximoEvento.getTiempo();
				tm* now = localtime(&t);
				cout<< k << "	"
				<< now->tm_mday
				<< "-"
				<< now->tm_mon
                << "-"
                << now->tm_year+1900
                << " "
                << now->tm_hour
                << ":"
                <<  now->tm_min
                << ":"
                << now->tm_sec
                << " "
                << proximoEvento.getNombreEvento()
                << " Evento "
                << proximoEvento.getNumeroEvento()
                << endl;

            salida.open("Salida QS.txt",ios::app);
                if(salida.fail()){
                        cout <<"No se pudo abrir el archivo"<<endl;
                        exit(1);
                    }
                    salida  << k << "	"
							<< now->tm_mday
							<< "-"
							<< now->tm_mon
							<< "-"
							<< now->tm_year+1900
							<< " "
							<< now->tm_hour
							<< ":"
							<<  now->tm_min
							<< ":"
							<< now->tm_sec
							<< " "
							<< proximoEvento.getNombreEvento()
							<< " Evento "
							<< proximoEvento.getNumeroEvento()
							<< endl;
                    salida.close();

            k++;
		}
return k;
	}

    void run(){
		    salida.open("Salida QS.txt",ios::out);
               if(salida.fail()){
                       cout <<"No se pudo abrir el archivo"<<endl;
                       exit(1);
                   }
               salida<<"";
               salida.close();


        for(int i=0;i<relojes->size(relojes);i++){
            Reloj relojActual = relojes->GetNth(relojes,i)->data;
            int u=relojActual.getTiempo(),v=1+rand()%relojActual.getTiempo();
            srand (time(NULL));
            for(int j=0;j<20;j++){

                if(relojActual.getReloj() == "periodico"){
                    relojActual.setEvento(u,relojActual.getNombre());
                }else if(relojActual.getReloj() == "aleatorio"){
                    relojActual.setEvento(v,relojActual.getNombre());
                }

                u += relojActual.getTiempo();
                v += 1+rand()%relojActual.getTiempo();

                eventos->push(&eventos,relojActual.getEvento());


            }
        }

        int fin = 1,k=0;

        // ordena los eventos
        eventos->quickSort(&eventos);	

        while(fin == 1){
			while (k<500){
            Evento proximoEvento = getProximoEvento(k);
            time_t t = time(0) + proximoEvento.getTiempo();
            tm* now = localtime(&t);
            cout << k << "	"
                << now->tm_mday
                << "-"
                << now->tm_mon
                << "-"
                << now->tm_year+1900
                << " "
                << now->tm_hour
                << ":"
                <<  now->tm_min
                << ":"
                << now->tm_sec
                << " "
                << proximoEvento.getNombreEvento()
                << " Evento "
                << proximoEvento.getNumeroEvento()
                << endl;


            salida.open("Salida QS.txt",ios::app);
                if(salida.fail()){
                        cout <<"No se pudo abrir el archivo"<<endl;
                        exit(1);
                    }
                    salida	<< k << "	"
							<< now->tm_mday
							<< "-"
							<< now->tm_mon
							<< "-"
							<< now->tm_year+1900
							<< " "
							<< now->tm_hour
							<< ":"
							<<  now->tm_min
							<< ":"
							<< now->tm_sec
							<< " "
							<< proximoEvento.getNombreEvento()
							<< " Evento "
							<< proximoEvento.getNumeroEvento()
							<< endl;
                    salida.close();


            k++;
            }

            // si se ejecutan 500 eventos pregunta al usuario si quiere agregar 50 eventos
            cout << "Quieres generar 50 eventos? , presiona 1 , si no quieres presiona 0: ";cin >> fin;
                if(fin==1){
			k=getprox50(k);}                         
        }
        eventos->getComp();


    }

};

class PlanificadorConHeap{
private:
    vector<Evento> eventos;
    vector<Reloj> relojes;
public:
    PlanificadorConHeap(vector<vector<string>> wordsRelojes){
        for(string::size_type i=0;i< wordsRelojes.size();i++){
            agregarReloj(wordsRelojes[i]);
        }
    };

    void agregarReloj(vector<string> words){
        // Crea un reloj
        Reloj reloj = Reloj();
        reloj.setNumero(stoi(words[0]));
        reloj.setNombre(words[1]);
        reloj.setReloj(words[2]);
        reloj.setTiempoRepe(stoi(words[3]));


        //Agrega el Reloj al vector
        relojes.push_back(reloj);
    }
    int getprox50(int k){
		//int fin;
		for(int x=0;x<50;x++){
				time_t t = time(0) + eventos[k].getTiempo();
				tm* now = localtime(&t);
				cout<< k << "	"
				<< now->tm_mday
				<< "-"
				<< now->tm_mon
                << "-"
                << now->tm_year+1900
                << " "
                << now->tm_hour
                << ":"
                <<  now->tm_min
                << ":"
                << now->tm_sec
                << " "
                << eventos[k].getNombreEvento()
                << " Evento "
                << eventos[k].getNumeroEvento()
                << endl;

            salida.open("Salida Heap.txt",ios::app);
                if(salida.fail()){
                        cout <<"No se pudo abrir el archivo"<<endl;
                        exit(1);
                    }
                    salida  << k << "	"
							<< now->tm_mday
							<< "-"
							<< now->tm_mon
							<< "-"
							<< now->tm_year+1900
							<< " "
							<< now->tm_hour
							<< ":"
							<<  now->tm_min
							<< ":"
							<< now->tm_sec
							<< " "
							<< eventos[k].getNombreEvento()
							<< " Evento "
							<< eventos[k].getNumeroEvento()
							<< endl;
                    salida.close();

            k++;
		}
return k;
	}

    void run(){
		    salida.open("Salida Heap.txt",ios::out);
               if(salida.fail()){
                       cout <<"No se pudo abrir el archivo"<<endl;
                       exit(1);
                   }
               salida<<"";
               salida.close();

        for(string::size_type i=0;i<relojes.size();i++) {
            int u = relojes[i].getTiempo(),
                    v = 1 + rand() % relojes[i].getTiempo();
            for (int j = 0; j < 20; j++) {
                if (relojes[i].getReloj() == "periodico") {
                    relojes[i].setEvento(u, relojes[i].getNombre());
                } else if (relojes[i].getReloj() == "aleatorio") {
                    relojes[i].setEvento(v, relojes[i].getNombre());
                }

                u += relojes[i].getTiempo();
                v += 1 + rand() % relojes[i].getTiempo();

                eventos.push_back(relojes[i].getEvento());
            }


        }
		
        int n = eventos.size();
        heapSort(eventos, n);	

        int fin = 1,k=0;
        while(fin == 1){
			while (k<500){
            time_t t = time(0) + eventos[k].getTiempo();
            tm* now = localtime(&t);
            cout << k << "	"
                << now->tm_mday
                << "-"
                << now->tm_mon
                << "-"
                << now->tm_year+1900
                << " "
                << now->tm_hour
                << ":"
                <<  now->tm_min
                << ":"
                << now->tm_sec
                << " "
                << eventos[k].getNombreEvento()
                << " Evento "
                << eventos[k].getNumeroEvento()
                << endl;


            salida.open("Salida Heap.txt",ios::app);
                if(salida.fail()){
                        cout <<"No se pudo abrir el archivo"<<endl;
                        exit(1);
                    }
                    salida	<< k << "	"
							<< now->tm_mday
							<< "-"
							<< now->tm_mon
							<< "-"
							<< now->tm_year+1900
							<< " "
							<< now->tm_hour
							<< ":"
							<<  now->tm_min
							<< ":"
							<< now->tm_sec
							<< " "
							<< eventos[k].getNombreEvento()
							<< " Evento "
							<< eventos[k].getNumeroEvento()
							<< endl;
                    salida.close();


            k++;
            }

            // si se ejecutan 500 eventos pregunta al usuario si quiere agregar 50 eventos
            cout << "Quieres generar 50 eventos? , presiona 1 , si no quieres presiona 0: ";cin >> fin;
                if(fin==1){
			k=getprox50(k);}
			
       }
       getComp();
}
};

class PlanificadorConHB{
private:
    struct Lista<Reloj> *relojes;
    vector<Evento> eventosV;

   	BinomialHeap<Evento> heap;

public:
    PlanificadorConHB(vector<vector<string>> wordsRelojes){
        relojes = NULL;
        // agrega todos los relojes
        for(string::size_type i=0;i<wordsRelojes.size();i++){
            agregarReloj(wordsRelojes[i]);
        }
    };


    // metodos

    void agregarReloj(vector<string> words){
        // Crea un reloj
        Reloj reloj = Reloj();
        reloj.setNumero(stoi(words[0]));
        reloj.setNombre(words[1]);
        reloj.setReloj(words[2]);
        reloj.setTiempoRepe(stoi(words[3]));


        //Agrega el Reloj a la lista
        relojes->push(&relojes,reloj);


    }

    int getprox50(int k){
		for(int x=0;x<50;x++){
				time_t t = time(0) + eventosV[k].getTiempo();
				tm* now = localtime(&t);
				cout<< k << "	"
				<< now->tm_mday
				<< "-"
				<< now->tm_mon
                << "-"
                << now->tm_year+1900
                << " "
                << now->tm_hour
                << ":"
                <<  now->tm_min
                << ":"
                << now->tm_sec
                << " "
                << eventosV[k].getNombreEvento()
                << " Evento "
                << eventosV[k].getNumeroEvento()
                << endl;

            salida.open("Salida QS.txt",ios::app);
                if(salida.fail()){
                        cout <<"No se pudo abrir el archivo"<<endl;
                        exit(1);
                    }
                    salida  << k << "	"
							<< now->tm_mday
							<< "-"
							<< now->tm_mon
							<< "-"
							<< now->tm_year+1900
							<< " "
							<< now->tm_hour
							<< ":"
							<<  now->tm_min
							<< ":"
							<< now->tm_sec
							<< " "
							<< eventosV[k].getNombreEvento()
							<< " Evento "
							<< eventosV[k].getNumeroEvento()
							<< endl;
                    salida.close();

            k++;
		}
return k;
	}

    void run(){
		    salida.open("Salida HB.txt",ios::out);
               if(salida.fail()){
                       cout <<"No se pudo abrir el archivo"<<endl;
                       exit(1);
                   }
               salida<<"";
               salida.close();


        for(int i=0;i<relojes->size(relojes);i++){
            Reloj relojActual = relojes->GetNth(relojes,i)->data;
            int u=relojActual.getTiempo(),v=1+rand()%relojActual.getTiempo();
            srand (time(NULL));
            for(int j=0;j<20;j++){

                if(relojActual.getReloj() == "periodico"){
                    relojActual.setEvento(u,relojActual.getNombre());
                }else if(relojActual.getReloj() == "aleatorio"){
                    relojActual.setEvento(v,relojActual.getNombre());
                }

                u += relojActual.getTiempo();
                v += 1+rand()%relojActual.getTiempo();

                heap.insertar(relojActual.getEvento());


            }
        }

        int fin = 1,k=0;

        // ordena los eventos
        while(!heap.esVacia()){
        eventosV.push_back(heap.extractMin());
        }


        while(fin == 1){
			while (k<500){
            time_t t = time(0) + eventosV[k].getTiempo();
            tm* now = localtime(&t);
            cout << k << "	"
                << now->tm_mday
                << "-"
                << now->tm_mon
                << "-"
                << now->tm_year+1900
                << " "
                << now->tm_hour
                << ":"
                <<  now->tm_min
                << ":"
                << now->tm_sec
                << " "
                << eventosV[k].getNombreEvento()
                << " Evento "
                << eventosV[k].getNumeroEvento()
                << endl;


            salida.open("Salida HB.txt",ios::app);
                if(salida.fail()){
                        cout <<"No se pudo abrir el archivo"<<endl;
                        exit(1);
                    }
                    salida	<< k << "	"
							<< now->tm_mday
							<< "-"
							<< now->tm_mon
							<< "-"
							<< now->tm_year+1900
							<< " "
							<< now->tm_hour
							<< ":"
							<<  now->tm_min
							<< ":"
							<< now->tm_sec
							<< " "
							<< eventosV[k].getNombreEvento()
							<< " Evento "
							<< eventosV[k].getNumeroEvento()
							<< endl;
                    salida.close();


            k++;
            }

            // si se ejecutan 500 eventos pregunta al usuario si quiere agregar 50 eventos
            cout << "Quieres generar 50 eventos? , presiona 1 , si no quieres presiona 0: ";cin >> fin;
                if(fin==1){
			k=getprox50(k);}

                
        }
        heap.getCompHB();


    }

};



int main() {
	
    string cadena;
               

    ifstream fe("nombre.txt");
    int contador=0;
    vector<string> words; // vector con cada parametro del reloj
    vector<vector<string>> wordsRelojes;  // vector de vectores con el contenido de words

    while (!fe.eof()) {
            contador ++;
            fe >> cadena;

            words.push_back(cadena);

            if(contador == 4){
                wordsRelojes.push_back(words);
                contador = 0;
                words.clear();
            }
    }

    char opcion;
    cout << "Elije tu algoritmo de ordenamiento: " << endl;
    cout << "Presiona 1 para Quicksort: " << endl;
    cout << "Presiona 2 para Heapsort: " << endl;
        cout << "Presiona 3 para HB: " << endl;

    cout << "Presiona cualquier otra tecla para salir: ";cin >> opcion;

    if(opcion == '1'){
        // Lista con quicksort
        PlanificadorConLista planificadorLista = PlanificadorConLista(wordsRelojes);
        planificadorLista.run();
    }else if(opcion == '2'){

        PlanificadorConHeap planificadorConHeap = PlanificadorConHeap(wordsRelojes);
        planificadorConHeap.run();

    }else if(opcion == '3'){
        PlanificadorConHB planificadorHB = PlanificadorConHB(wordsRelojes);
        planificadorHB.run();				
	}

    fe.close();
    return 0;
}
