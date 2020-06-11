<<<<<<< HEAD
=======
//
// Created by julian on 28/5/20.
//
>>>>>>> Javier
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
#ifndef PARCIAL2_LISTA_H
#define PARCIAL2_LISTA_H

<<<<<<< HEAD
int cc=0;
=======
<<<<<<< HEAD
int cc=0;
=======
>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d
>>>>>>> Javier
// Lista
template <typename T>
struct Lista
{
    T data;
    struct Lista *next;
    // agregar elementos a la lista
    void push(struct Lista<T>** head_ref, T new_data)
    {
        /* allocate node */
        struct Lista* new_node = new Lista;

        /* put in the data */
        new_node->data = new_data;

        /* link the old list off the new node */
        new_node->next = (*head_ref);

        /* move the head to point to the new node */
        (*head_ref) = new_node;
<<<<<<< HEAD
    }
=======
<<<<<<< HEAD
    } 
=======
    }
>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d
>>>>>>> Javier

    // imprimir lista
    void printList(struct Lista *node)
    {
        while (node != NULL)
        {

            time_t t = time(0) + node->data.getTiempo();
            tm* now = localtime(&t);
            cout
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
                    << node->data.getNombreEvento()
                    << " Evento "
                    << node->data.getNumeroEvento()
                    << endl;

            node = node->next;
        }
        printf("\n");
    }

    // retorna la cola de la lista
<<<<<<< HEAD
    struct Lista *getTail(struct Lista *cur)        //viene la lista [1][4][8][5][3][2] donde cur=[1]
    {
        while (cur != NULL && cur->next != NULL)    //hasta el ultimo: [2], recorre la lista
            cur = cur->next;
        return cur;     //devuelve el ultimo [2]
    }

=======
<<<<<<< HEAD
    struct Lista *getTail(struct Lista *cur)        //viene la lista [1][4][8][5][3][2] donde cur=[1]
    {
        while (cur != NULL && cur->next != NULL)    //hasta el ultimo: [2], recorre la lista
            cur = cur->next;        
        return cur;     //devuelve el ultimo [2] 
    }
          
=======
    struct Lista *getTail(struct Lista *cur)
    {
        while (cur != NULL && cur->next != NULL)
            cur = cur->next;
        return cur;
    }

>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d
>>>>>>> Javier
    // retorna la cola de la lista
    int size(Lista<T> *head){
        int contador = 0;
        Lista<T>* cur = head;
        while (cur != NULL){
            contador++;
            cur = cur->next;
        }
        return contador;
    }

    Lista<T>* GetNth(Lista<T>* head, int index)
    {
        Lista<T>* current = head;

        int count = 0;
        while (current != NULL)
        {
            if (count == index)
                return current;
            count++;
            current = current->next;
        }

    }

    // retorna el elemento pivote
<<<<<<< HEAD
    struct Lista *partition(struct Lista *head, struct Lista *end,          //vienen: ([1], [2], NULL, NULL)
                            struct Lista **newHead, struct Lista **newEnd)
=======
<<<<<<< HEAD
    struct Lista *partition(struct Lista *head, struct Lista *end,          //vienen: ([1], [2], NULL, NULL)
                           struct Lista **newHead, struct Lista **newEnd)
>>>>>>> Javier
    {
        struct Lista *pivot = end;  //pivot=[2]
        struct Lista *prev = NULL, *cur = head, *tail = pivot;  //prev=NULL, cur=[1], tail=[2]

        // During partition, both the head and end of the list might change
        // which is updated in the newHead and newEnd variables
        while (cur != pivot)    //[1]!=[2] ->entra al while //[4]!=[2]-> entra al while, en else
        {
            if (cur->data.getTiempo() < pivot->data.getTiempo())        //si [1]<[2]->entra al if con ->[1][4][8][5][3][2]       prev=NULL, cur=[1], pivot=[2], tail=[2]
            {
<<<<<<< HEAD
=======
                
>>>>>>> Javier
                // First node that has a value less than the pivot - becomes
                // the new head
                if ((*newHead) == NULL)
                    (*newHead) = cur;       //newHead=[1]

                prev = cur;     //prev=[1]
                cur = cur->next;    //cur=[4]
            }
            else // If cur node is greater than pivot-> aca no entra, es la 2º pasada   [1]->[4][8][5][3][2]      prev=[1], cur=[4], pivot[2], tail=[2]
            {
<<<<<<< HEAD
                // Move cur node to next of tail, and change tail
                if (prev){

=======
                
                // Move cur node to next of tail, and change tail
                if (prev){
                    
>>>>>>> Javier
                    prev->next = cur->next; }   // [1]->[8]
                struct Lista *tmp = cur->next;  //tmp=[8]
                cur->next = NULL;       //[4]->NULL
                tail->next = cur;       //[2]->[4]
                tail = cur;     //tail=[4]
                cur = tmp;      //cur=[8] -> la lista queda [1]->[8][5][3][2][4]
            }
            cc=cc+2;
<<<<<<< HEAD
=======
            
>>>>>>> Javier
        }   //al finalizar el while tenemos: [1][2][4][8][5][3]
        //LUEGO DE CADA PASADA DE LA LISTA
        // Si el pivot es el menor elemento en la Lista,
        // pivot es la cabeza
        if ((*newHead) == NULL)     //no entra pues newHead=[1]
<<<<<<< HEAD
            (*newHead) = pivot;
=======
            (*newHead) = pivot;     
>>>>>>> Javier

        // newEnd pasa a ser el ultimo nodo
        (*newEnd) = tail;       //  newEnd=[3]

        // Return the pivot node
        return pivot;   // return [2]
    }

    // metodo recursivo de ordenamiento Quicksort
    struct Lista *quickSortRecur(struct Lista *head, struct Lista *end) //aca viene el puntero a la cabeza: [1], y el puntero al ultimo: [2]
    {
        // base condition
        if (!head || head == end){       //esto devuelve la cabeza si es el unico elemento de la lista   //cuando viene el ([1], [1]) devuelve [1]
<<<<<<< HEAD
            cc++;
            return head;}

=======
            
            return head;}
        
=======
    struct Lista *partition(struct Lista *head, struct Lista *end,
                           struct Lista **newHead, struct Lista **newEnd)
    {
        struct Lista *pivot = end;
        struct Lista *prev = NULL, *cur = head, *tail = pivot;

        // During partition, both the head and end of the list might change
        // which is updated in the newHead and newEnd variables
        while (cur != pivot)
        {
            if (cur->data.getTiempo() < pivot->data.getTiempo())
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
                struct Lista *tmp = cur->next;
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
    struct Lista *quickSortRecur(struct Lista *head, struct Lista *end)
    {
        // base condition
        if (!head || head == end)
            return head;

>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d
>>>>>>> Javier
        Lista *newHead = NULL, *newEnd = NULL;

        // Partition the list, newHead and newEnd will be updated
        // by the partition function
<<<<<<< HEAD
        struct Lista *pivot = partition(head, end, &newHead, &newEnd); //mando a partition ([1], [2], NULL, NULL)-> me devuelve [2] y cambia los valores de: newHead=[1] y newEnd=[3]

        // Si el pivot es el menor elemento - no hace falta llamar la recursiva a
=======
<<<<<<< HEAD
        struct Lista *pivot = partition(head, end, &newHead, &newEnd); //mando a partition ([1], [2], NULL, NULL)-> me devuelve [2] y cambia los valores de: newHead=[1] y newEnd=[3]

        // Si el pivot es el menor elemento - no hace falta llamar la recursiva a 
>>>>>>> Javier
        // la parte izquierda.
        if (newHead != pivot) //si pivot no es el menor: [1]!=[2] Entra al if   //Recordemos la lista desp de partition:[1][2][4][8][5][3]
        {
            // Set the node before the pivot node as NULL
            struct Lista *tmp = newHead;       //tmp=[1]
            while (tmp->next != pivot)  //El siguiente al tmp es el pivot? en este caso si->no entra al while
                tmp = tmp->next;
            tmp->next = NULL;   //[1]->NULL     %?->[2][4][8][5][3]

            // Llamada Recursiva para la lista antes del pivot
            newHead = quickSortRecur(newHead, tmp); //aca mando ([1], [1]) y me vuelve [1] => newHead=[1]

            // Change next of last node of the left half to pivot
            tmp = getTail(newHead); //mando a getTail con [1] y me devuelve [1]
            tmp->next = pivot;  //[1]->[2][4][8][5][3]
            //Estos 2 pasos son para concatenar la lista menor al pivot con el pivot
        }

        // Llamada Recursiva para la lista despues del pivot
        pivot->next = quickSortRecur(pivot->next, newEnd);  //mando ([4], [3]) y me va a devolver el [3] como pivot y newHead, y el [5] como newEnd

        return newHead; //Al fin de esto me devuelve [1][2][3][4][5][8] bien ordenado
    }

    // metodo envoltorio del metodo recursivo
    void quickSort(struct Lista **headRef)      //aca viene la lista de eventos [1][4][8][5][3][2]
    {
        (*headRef) = quickSortRecur(*headRef, getTail(*headRef));   //va a devolver la cabeza de la lista ordenada / parametros: (lista eventos, ultimo valor)
        return;
    }
    void getComp(){
        cout<< "Comp: "<< cc;
    }
};


<<<<<<< HEAD
#endif //PARCIAL2_LISTA_H
=======
=======
        struct Lista *pivot = partition(head, end, &newHead, &newEnd);

        // If pivot is the smallest element - no need to recur for
        // the left part.
        if (newHead != pivot)
        {
            // Set the node before the pivot node as NULL
            struct Lista *tmp = newHead;
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
    void quickSort(struct Lista **headRef)
    {
        (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
        return;
    }
};

>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d
#endif //PARCIAL2_LISTA_H
>>>>>>> Javier
