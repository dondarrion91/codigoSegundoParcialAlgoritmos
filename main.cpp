#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>


using namespace std;



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
        evento =  Evento();
    };

    // Metodos
    void setEvento(int tiempo,string nombreReloj){
        srand((unsigned) time(0));
        if(this->getReloj() == "periodico"){
            evento.setTiempo(tiempo);
            evento.setTipo("periodico");
            evento.setNombreEvento(nombreReloj);
        }else if(this->getReloj() == "aleatorio"){
            evento.setTiempo(rand() % tiempo);
            evento.setTipo("aleatorio");
            evento.setNombreEvento(nombreReloj);
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

// Lista
struct Node
{
    Reloj data;
    struct Node *next;
};

// Planificador con lista y QuickSort
class PlanificadorConLista{
private:
    struct Node *relojes;
public:
    PlanificadorConLista(){ relojes = NULL; };


    // metodos

    // agregar elementos a la lista
    void push(struct Node** head_ref, Reloj new_data)
    {
        /* allocate node */
        struct Node* new_node = new Node;

        /* put in the data */
        new_node->data = new_data;

        /* link the old list off the new node */
        new_node->next = (*head_ref);

        /* move the head to point to the new node */
        (*head_ref) = new_node;
    }

    // imprimir lista
    void printList(struct Node *node)
    {
        while (node != NULL)
        {
            time_t t = time(0) + node->data.getEvento().getTiempo();
            tm* now = localtime(&t);
            cout << now->tm_mday << "-" << now->tm_mon << "-" << now->tm_year+1900 << " " << now->tm_hour << ":" <<  now->tm_min << ":" << now->tm_sec << " " <<  node->data.getNombre() << endl;
            node = node->next;
        }
        printf("\n");
    }

    // retorna la cola de la lista
    struct Node *getTail(struct Node *cur)
    {
        while (cur != NULL && cur->next != NULL)
            cur = cur->next;
        return cur;
    }


    // retorna el elemento pivote
    struct Node *partition(struct Node *head, struct Node *end,
                           struct Node **newHead, struct Node **newEnd)
    {
        struct Node *pivot = end;
        struct Node *prev = NULL, *cur = head, *tail = pivot;

        // During partition, both the head and end of the list might change
        // which is updated in the newHead and newEnd variables
        while (cur != pivot)
        {
            if (cur->data.getEvento().getTiempo() < pivot->data.getEvento().getTiempo())
            {
                // First node that has a value less than the pivot - becomes
                // the new head
                if ((*newHead) == NULL)
                    (*newHead) = cur;

                prev = cur;
                cur = cur->next;
            }
            else // If cur node is greater than pivot
            {
                // Move cur node to next of tail, and change tail
                if (prev)
                    prev->next = cur->next;
                struct Node *tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            }
        }

        // If the pivot data is the smallest element in the current list,
        // pivot becomes the head
        if ((*newHead) == NULL)
            (*newHead) = pivot;

        // Update newEnd to the current last node
        (*newEnd) = tail;

        // Return the pivot node
        return pivot;
    }

    // metodo recursivo de ordenamiento Quicksort
    struct Node *quickSortRecur(struct Node *head, struct Node *end)
    {
        // base condition
        if (!head || head == end)
            return head;

        Node *newHead = NULL, *newEnd = NULL;

        // Partition the list, newHead and newEnd will be updated
        // by the partition function
        struct Node *pivot = partition(head, end, &newHead, &newEnd);

        // If pivot is the smallest element - no need to recur for
        // the left part.
        if (newHead != pivot)
        {
            // Set the node before the pivot node as NULL
            struct Node *tmp = newHead;
            while (tmp->next != pivot)
                tmp = tmp->next;
            tmp->next = NULL;

            // Recur for the list before pivot
            newHead = quickSortRecur(newHead, tmp);

            // Change next of last node of the left half to pivot
            tmp = getTail(newHead);
            tmp->next = pivot;
        }

        // Recur for the list after the pivot element
        pivot->next = quickSortRecur(pivot->next, newEnd);

        return newHead;
    }

    // metodo envoltorio del emtodo recursivo
    void quickSort(struct Node **headRef)
    {
        (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
        return;
    }

    void agregarReloj(vector<string> words){
        // Crea un reloj
        Reloj reloj = Reloj();
        reloj.setNumero(stoi(words[0]));
        reloj.setNombre(words[1]);
        reloj.setReloj(words[2]);
        reloj.setTiempoRepe(stoi(words[3]));

        // Crea un evento en el reloj
        reloj.setEvento(reloj.getTiempo(),reloj.getNombre());

        //Agrega el Reloj a la lista
        push(&relojes,reloj);
    }

    void getProximoEvento(tm* now,struct Node *node){

    }

    void run(vector<vector<string>> wordsRelojes){

        // agrega un reloj y crea un evento
        for(int i=0;i<100;i++){
            agregarReloj(wordsRelojes[i]);
        }

        // ordena los eventos
        quickSort(&relojes);

        // imprime los eventos
        Node* nuevaLista = relojes;

        int i = 0;
        while(i< 99){

            time_t t = time(0) + nuevaLista->data.getEvento().getTiempo();
            tm* now = localtime(&t);
            cout << now->tm_mday << "-" << now->tm_mon << "-" << now->tm_year+1900 << " " << now->tm_hour << ":" <<  now->tm_min << ":" << now->tm_sec << " " <<  nuevaLista->data.getEvento().getNombreEvento() << endl;
            nuevaLista = nuevaLista->next;
            i++;
        }

        /*time_t t = time(0) + node->data.getEvento().getTiempo();
        tm* now = localtime(&t);
        cout << now->tm_mday << "-" << now->tm_mon << "-" << now->tm_year+1900 << " " << now->tm_hour << ":" <<  now->tm_min << ":" << now->tm_sec << " " <<  node->data.getNombre() << endl;
*/


    }

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
    vector<string> words; // vector con cada parametro del reloj
    vector<vector<string>> wordsRelojes;  // vector de vectores con el contenido de words

    // Lista con quicksort
    PlanificadorConLista planificadorLista = PlanificadorConLista();

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

    planificadorLista.run(wordsRelojes);



    fe.close();
    return 0;
}
