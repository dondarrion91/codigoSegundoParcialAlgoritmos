#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_


#define DEBUG false
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <string>

template <typename T>
class NodoBinomial;

//CLASE BINOMIALHEAP

template <typename T>
class BinomialHeap
{
    public:
        struct Exception
	    {
		    Exception(std::string msg ):msg(msg){}
		    std::string what(){return msg;}
		    std::string msg;
	    };
            friend class NodoBinomial<T>;

            BinomialHeap();
            BinomialHeap(const BinomialHeap& otro);
            BinomialHeap(BinomialHeap&& otro);
            BinomialHeap& operator=(const BinomialHeap& otro);
            ~BinomialHeap();

            void insertar(T valor);   //Crea un nodo heap con valor v y uniones con la cabeza
            T getMin();     //Buca el nodo con el menor valor (entre los hnos) y lo retorna
            T extractMin(); //Borra el nodo con el menor valor 
            void BorrarValor(T valor);  //Borra el nodo con el valor que le mande-> disminuye su valor hasta que sea menor al Min y ExtractMin
            void disminuirValor(T valor, T valornuevo); //Busca el nodo con el valor que le di y lo cambia por valornuevo
            int size(); 
            bool esVacia();
            void clear(); //Borra toda la lista
    protected:
            NodoBinomial<T>* buscarValor(T v);   //Devuelve un puntero al nodo con valor v
            static NodoBinomial<T>* unionHeap(NodoBinomial<T>* A, NodoBinomial<T>* B);  //Une el Heap A con el Heap B: por lo que entiendo los une añadiendolos al final de lalista de hijos
            static NodoBinomial<T>* mergeHeap(NodoBinomial<T>* A, NodoBinomial<T>* B);  //Masomenos lo mismo que el anterior-> no entiendo diferencia
            static int orden(NodoBinomial<T>* Heap);    //Numero de hijos de un nodo
    private:
            NodoBinomial<T>* cabeza;        //puntero a la cabeza de la lista de heap donde cada nodo es direccion de un heap
};

//CLASE NODOBINOMIAL

template <typename T>
class NodoBinomial
{
    public:
            friend class BinomialHeap<T>;
            NodoBinomial(T v, NodoBinomial<T>* padre= nullptr);
            ~NodoBinomial();

            void addHijo(NodoBinomial<T>* hijo);
            NodoBinomial<T>* buscar(T v);
            int size(int& i);
            void addTo(BinomialHeap<T>* otro);  //añade los nodos de this a otro
    private:
            T valor;
            NodoBinomial<T> *hermano, *hijo, *padre;
            int orden;
};

//METODOS CLASE NODOBINOMIAL

template <typename T>
NodoBinomial<T>::NodoBinomial(T v, NodoBinomial<T>* p)      //CONSTRUCTOR
{
    valor = v;
    padre = p;
    hermano = hijo = nullptr;
    orden = 0;
}
template <typename T>
NodoBinomial<T>::~NodoBinomial()    //DESTRUCTOR
{
    delete hijo;
    delete hermano;
}

/*template <typename T>
int NodoBinomial<T>::size(int &i)
{
    ++i;
    if(hermano)
        hermano->size(i);   //que sume i segun la cant de hnos
    if(hijo)
        hijo->size(i);  //que sume i segun la cant de hijos
    return i;    //i = hnos + hijos
}*/

template <typename T>
void NodoBinomial<T>::addHijo(NodoBinomial<T>* nodoHijo)    //le añade un hijo al padre this
{
    if(nodoHijo)    //si existe nodoHijo
    {
        nodoHijo->hermano = nullptr;    //setea su hno en null
        if(hijo)    //si ya existe hijo
        {
            NodoBinomial<T>* temp = hijo;       
            while(temp->hermano)        //mientras el hijo tenga hnos
            {
                temp = temp->hermano;   //recorro hasta el ultimo hno
            }
            temp->hermano = nodoHijo;       //y agrego el nuevo hijo como hno
        } else {
            hijo = nodoHijo;    //si no habia hijos, este es el unico
        }
        ++orden;    //suma 1 en cantidad de hijos
        nodoHijo->padre = this; //le digo que su padre es this
    }
}

//METODOS DE BINOMIALHEAP

    //CONSTRUCTORES
template <typename T>
BinomialHeap<T>::BinomialHeap()
{
    cabeza = 0;
}

    //DESTRUCTOR
template <typename T>
BinomialHeap<T>::~BinomialHeap()
{
    clear();
}

template <typename T>
void BinomialHeap<T>::clear()
{
    delete cabeza;
    cabeza = nullptr;
}

template <typename T>
bool BinomialHeap<T>::esVacia()
{
    return (cabeza==nullptr); //forma fachera de retornar true si es vacia o false si no
}

template <typename T>
void BinomialHeap<T>::insertar(T v)
{
    NodoBinomial<T> *p = cabeza? cabeza->padre: nullptr;    //mamadera entendelo vos
    NodoBinomial<T> *unico = new NodoBinomial<T>(v, p);
    cabeza = unionHeap(unico, cabeza); //CREO que hace [unico]->[resto lista], como un concat
}

template <typename T>
T BinomialHeap<T>::extractMin() //recordar que encuentra el menor para sacarlo del heap
{
    NodoBinomial<T> *prev=nullptr,  *min=nullptr, *temp=nullptr, *next=nullptr;
    T ValorMin;
    if(cabeza)  //si existe la cabeza
    {
        NodoBinomial<T>* minPrev = nullptr; //creo un nodo previo al nodo min
        min = cabeza;   
        temp = cabeza->hermano;
        prev = cabeza;

        while(temp) //mientras exista temp
        {
            if(temp->valor.getTiempo() < min->valor.getTiempo())    //si hermano < min
            {
                min = temp; //ese valor lo guardo en min
                minPrev = prev; // y el anterior lo pongo en minPrev
            }
            prev = prev->hermano;
            temp = temp->hermano;   //tener en cuenta que siempre el orden de corrimiento es [prev]->[temp], donde prev es el actual y temp su hno
        }

        if(minPrev) //si existe minPrev
        {
            minPrev->hermano = min->hermano;    //setea su hno como el de min
        } else {    //si no existe minPrev->el minimo es la cabeza
            cabeza = min->hermano;  // y setea al hno como la nueva cabeza
        }
//como va a eliminar el nodo min, todos sus hijos pasan a ser hijos de su padre
        next = min->hijo;   
        temp = next;
        while (temp)    
        {
            temp->padre = min-> padre;  //CREO que le dice a todos los hijos de min que su padre es el padre de min (su abuelo?)
            temp = temp->hermano;
        }

        min->hermano = nullptr;
        min->hijo = nullptr;
        min->padre = nullptr;
        ValorMin = min->valor;
        delete min; //ACA ELIMINE EL NODO MIN

        cabeza = unionHeap(cabeza, next);   //une los hijos de min con los hnos de min
        temp = min = minPrev = next = nullptr; 
    } else{
            throw BinomialHeap<T>::Exception("Heap vacio!");
    }
    return ValorMin;    // Y ACA EXTRAJE SU VALOR
    
}

template <typename T>
int BinomialHeap<T>::orden(NodoBinomial<T>* heap)
{
    if(!heap)   //si no existe heap
    {
        return -1;
    }

    int i = 0;
    NodoBinomial<T>* hijo = heap->hijo;
    while(hijo)
    {
        ++i;
        hijo = hijo->hermano;
    }
    return i;   //devuelve la cantidad de hijos que tiene un Nodo
}

template <typename T>
NodoBinomial<T>* BinomialHeap<T>::unionHeap(NodoBinomial<T>* A, NodoBinomial<T>* B)
{
    NodoBinomial<T>* heapUnido = mergeHeap(A, B);
    if(heapUnido)
    {
        NodoBinomial<T> *cur = heapUnido, *prev = nullptr, *next = nullptr;
        int ordenA, ordenB;
        while(cur && cur->hermano)  //mientras existan cur y su hno-> SUPONGO QUE ESTO ES PARA ORDENAR EL ARBOL
        {
            next = cur->hermano;   
            ordenA = cur->orden;
            ordenB = next->orden;
            if(ordenA == ordenB && ordenA != orden(next->hermano))  //si cur y su hno tienen misma cant de hijos, y cur no tiene la misma que el hno de su hno: [cur][igual que este hno][DIF QUE ESTE HNO]
            {
                //NEXT PASA A SER HIJO DE CUR
                if(cur->valor.getTiempo() < next->valor.getTiempo())    //si cur es menor que su hermano
                {
                    cur->hermano = next->hermano;   //setea como hno su otro hno->explicado arriba
                    cur->addHijo(next); //y el que era su hermano pasa a ser su hijo
                    prev = cur; //setea el previo
                    cur = cur->hermano; //y corre el actual
                }   //OSEA, al finalizar este if lo que hizo fue poner cur en el lugar de su hno y tener de hijo a su hno, todo muy santiagueño
                else{
                    //CUR PASA A SER HIJO DE NEXT
                    if(prev)
                        prev->hermano = next; //le dice a prev que se "saltee" a cur y apunte a next  
                    else
                        heapUnido = next;   //la cabeza de heapunido ahora es next
                    next->addHijo(cur);
                    prev = next;
                    cur = next->hermano;
                }
            } else {
            //NO ENTENDI, pero en el original decia que "agarra el hijo de next"    
                if(!prev)   //si no existe prev
                    heapUnido = cur;
                prev = cur;
                cur = next; //va recorriendolo
            }
        }
    }
    return heapUnido;
}

template <typename T>
NodoBinomial<T>* BinomialHeap<T>::mergeHeap(NodoBinomial<T>* A, NodoBinomial<T>* B)
{
    NodoBinomial<T>* M = nullptr;
    
    if(A || B){
        if(A && !B)    //si existe A pero no B
        {
            M = A;
        } 
        else if(!A && B)  // si no existe A pero si B
        {
            M = B;
        } 
        else  //si existen los dos 
        {    
            NodoBinomial<T>* temp = nullptr, *next = nullptr, *prev = nullptr, *cur = nullptr;

            if(A->orden > B->orden)
            {
                M = B;
                next = A;
            }
            else
            {
                M = A;
                next = B;
            }
            cur = M;

            while(cur && next && cur != next)   //recorre M hasta que cur=next -> cuando llega a la otra lista
            {
                if(cur->orden <= next->orden)   //si cant hijos 1º lista <= cant hijos 2º lista 
                {
                    if(cur->hermano)    //si cur tiene hno  [cur][hno][]...[next][]..
                    {
                        temp = cur->hermano;    //[temp=hno]
                        cur->hermano = next;    //[cur][next][].....
                        prev = cur; //[prev=cur]
                        cur = next; //[next][next]...
                        next = temp;//[next][hno].....
                    }//Vemos que puso next en el lugar de cur, y cur quedo guardado en prev
                    else{
                        cur->hermano = next;    //...[cur][next]...
                        cur = next; //corta el while
                    }
                }
                else{   //si 1º tiene mas hijos que 2º
                    if(prev)    
                        prev->hermano = next;   //[prev][next]
                   else   
                        M = next;   // M: [next][nexthno]....
                    temp = next->hermano;   //[temp=nexthno]
                    next->hermano = cur;    //[next][cur]
                    prev = next;    //[prev=next]
                    next = temp;    //[nexthno][cur]
                }
            }//Vemos que puso nexthno en el lugar de next, y cur como su hno-> Ademas guardo next en prev
        }
    }
    return M;   //LA VERDAD NO ENTENDI NI JOTA PERO ES PARA MANTENER LA CARACTERISTICA DE ORDEN DEL ARBOL
}

#endif


