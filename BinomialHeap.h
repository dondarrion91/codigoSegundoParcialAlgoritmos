#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_
 
 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <string>
 
using namespace std;
 
int ccHB=0;
 
template <typename T>
class NodoBinomial;
 
//CLASE BINOMIALHEAP
 
template <typename T>
class BinomialHeap
{
public:
    friend class NodoBinomial<T>;
 
    BinomialHeap();
    ~BinomialHeap();
 
    void insertar(T valor);   
    T extractMin(); //Borra el nodo con el menor valor
    bool esVacia();
    void clear(); //Borra toda la lista
    void getCompHB();
protected:
    static NodoBinomial<T>* unionHeap(NodoBinomial<T>* A, NodoBinomial<T>* B);  
    static NodoBinomial<T>* Hermanar(NodoBinomial<T>* A, NodoBinomial<T>* B);  
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
private:
    T valor;
    NodoBinomial<T> *hermano, *hijo, *padre;
    int orden;
};
 
//METODOS CLASE NODOBINOMIAL
 
template <typename T>
NodoBinomial<T>::NodoBinomial(T v, NodoBinomial<T>* p)      //CONSTRUCTOR
{
    valor = v;  //evento
    padre = p;
    hermano = hijo = nullptr;
    orden = 0;  //cant de hijos
}
template <typename T>
NodoBinomial<T>::~NodoBinomial()    //DESTRUCTOR
{
    delete hijo;
    delete hermano;
}
 
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
    return (cabeza==nullptr); 
}
 
template <typename T>
void BinomialHeap<T>::insertar(T v)
{
    NodoBinomial<T> *p = nullptr; 
    NodoBinomial<T> *Nuevo = new NodoBinomial<T>(v, p);
    cabeza = unionHeap(Nuevo, cabeza);
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
 
        while(temp) //While que busca el menor de todos los arboles en cuanto a tiempo.
        {
            if(temp->valor.getTiempo() < min->valor.getTiempo())    //si tiempo del hermano < tiempo cabeza
            {
                ccHB++;
                min = temp; //ese valor lo guardo en min
                minPrev = prev; // y el anterior lo pongo en minPrev
            }
            prev = prev->hermano;
            temp = temp->hermano;   //tener en cuenta que siempre el orden de corrimiento es [prev]->[temp], donde prev es el actual y temp su hno
        }
 
        if(minPrev) //Saca el minimo y hace qye minPrev apunte al min->hermano
        {
            minPrev->hermano = min->hermano;
        } else {
            cabeza = min->hermano;
        }
        next = min->hijo;
        temp = next;//Guarda en temporal los hijos del nodo borrado(El minimo).
 
        while (temp)
        {
            temp->padre = min-> padre;  //Sete el padre de los temporales en null.Para que se transformen en raiz de su arbol.
            temp = temp->hermano;
        }
 
        min->hermano = nullptr;
        min->hijo = nullptr;
        min->padre = nullptr;
       
        ValorMin = min->valor;
        delete min; //ACA ELIMINE EL NODO MIN
 
        cabeza = unionHeap(cabeza, next);   //une los heaps anteriores con los hijos de min
        temp = min = minPrev = next = nullptr;
    } else{
        cout <<"Heap vacio!"<<endl;
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
        hijo = hijo->hermano;       //Recorre los hermanos
    }
    return i;   //devuelve la cantidad de hijos que tiene un Nodo
}
 
template <typename T>
NodoBinomial<T>* BinomialHeap<T>::unionHeap(NodoBinomial<T>* A, NodoBinomial<T>* B) //Junta dos heap hermanos del mismo orden en 1 solo
{
    NodoBinomial<T>* heapUnido = Hermanar(A, B);   //A=Nuevo, B=cabeza
    if(heapUnido)
    {
        NodoBinomial<T> *cur = heapUnido, *prev = nullptr, *next = nullptr;
        int ordenA, ordenB;
        while(cur && cur->hermano)  //mientras existan cur y su hno
        {
            next = cur->hermano;
            ordenA = cur->orden;
            ordenB = next->orden;
            if(ordenA == ordenB)  //si cur y su hno tienen misma cant de hijos
            {
                
                if(cur->valor.getTiempo() < next->valor.getTiempo())    //si cur es menor que su hermano
                {
                    ccHB++;
                    cur->hermano = next->hermano;   
                    cur->addHijo(next); //NEXT PASA A SER HIJO DE CUR
                    prev = cur; 
                    cur = cur->hermano; //recorre los hermanos
                }  
                else{   //si cur es mayor que su hermano
                    ccHB++;
                    
                    if(prev)
                        prev->hermano = next; //le dice a prev que se "saltee" a cur y apunte a next
                    else
                        heapUnido = next;   //la cabeza de heapunido ahora es next
                    next->addHijo(cur); //CUR PASA A SER HIJO DE NEXT
                    prev = next;
                    cur = next->hermano;
                }
            } else {    //si el orden de A != orden de B
                if(!prev)   //si no existe prev
                    heapUnido = cur;
                prev = cur;
                cur = next; //va recorriendolo
            }
        }
    }
    return heapUnido;   //Cuando ve 2 heap con el mismo orden, los une sobre el hermano de la derecha
}
 
template <typename T>
NodoBinomial<T>* BinomialHeap<T>::Hermanar(NodoBinomial<T>* A, NodoBinomial<T>* B) //cuando inserta un nodo, lo hermana con los anteriores      //cuando extrae un nodo padre ordena sus hijos
{
    NodoBinomial<T>* M = nullptr;   //A=NUEVO B=Heap viejo
 
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
 
            if(A->orden > B->orden) //si el nodo nuevo tiene mas hijos que la cabeza
            {
                M = B;      //M es la cabeza
                next = A;
            }
            else    //si tiene menos hijos
            {
                M = A;  //M es el nuevo nodo
                next = B;
            }
            cur = M;    //M(cur) es el de menor orden    next: el de mayor orden
 
            while(cur && next && cur != next)   
            {
                if(cur->orden <= next->orden)   //si cant hijos del heap actual <= cant hijos heap siguiente
                {
                    ccHB++;
                    if(cur->hermano)    //entra al if cuando extrae el minimo, para ordenar los heaps de sus hijos. Se repetira hasta que cur no tenga hermanos
                    {
                        temp = cur->hermano;    
                        cur->hermano = next;    
                        prev = cur; 
                        cur = next; 
                        next = temp; //Aca swapea los heaps segun el orden
                    }//Vemos que puso next en el lugar de cur, y cur quedo guardado en prev
                    else{   //cuando insertamos un nodo, este no tiene hermanos     //en la extraxion, al ir swapeando los heaps, cuando llega al ultimo hermano, cambia de pivot
                        cur->hermano = next;    //Entonces lo hermanamos con los heaps que teniamos
                        cur = next; //corta el while
                    }
                }
                else{   //cuando swapeamos un hijo con otro del minimo y nos queda el actual de mayor orden que el next
                    ccHB++;
                    if(prev)
                        prev->hermano = next;   
                    else
                        M = next;   
                    temp = next->hermano;
                    next->hermano = cur; 
                    prev = next;    
                    next = temp;    //Swapeamos de nuevo el actual con el next 
                }
            }
        }
    }
    return M;   //Mantiene el heap con mas hijos a la derecha
}
template <typename T>
void BinomialHeap<T>::getCompHB(){
    cout<< "Comp: "<< ccHB;
}
 
 
#endif