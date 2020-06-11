//
// Created by julian on 28/5/20.
//
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

int cc=0;
// Lista
template <typename T>
struct Lista
{
    T data;
    struct Lista *next;
    // agregar elementos a la lista
    void push(struct Lista<T>** head_ref, T new_data)
    {
        struct Lista* new_node = new Lista;

        new_node->data = new_data;

        new_node->next = (*head_ref);

        (*head_ref) = new_node;
    } 

    // retorna la cola de la lista
    struct Lista *getTail(struct Lista *cur)        
    {
        while (cur != NULL && cur->next != NULL)    
            cur = cur->next;        
        return cur;     //devuelve el ultimo nodo 
    }
          
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
        return NULL;

    }

    // retorna el elemento pivote
    struct Lista *partition(struct Lista *head, struct Lista *end,          // 3º: Lo que hace es ubicar el pivot en su lugar definitivo, con los mayores que el a su derecha y los menores a su izq
                           struct Lista **newHead, struct Lista **newEnd)
    {
        struct Lista *pivot = end;  
        struct Lista *prev = NULL, *cur = head, *tail = pivot;  

        while (cur != pivot)    //mientras el nodo actual no sea el pivot
        {
            if (cur->data.getTiempo() < pivot->data.getTiempo())        //si el tiempo del actual es menor al tiempo del pivot
            {
				cc++;
                if ((*newHead) == NULL)
                    (*newHead) = cur;       

                prev = cur;     
                cur = cur->next;    //recorre la lista un lugar
            }
            else // Si el nodo actual es mas grande que el pivot
            {
                cc++;
                // Mueve el nodo actual al siguiente a la cola, y cambia la cola
                if (prev){
                    
                    prev->next = cur->next; }   
                struct Lista *tmp = cur->next;  
                cur->next = NULL;       
                tail->next = cur;       
                tail = cur;     
                cur = tmp;      
            }
            
        } //al terminar el while tenemos: [menores al pivot]->[pivot]->[mayores al pivot]    
        //LUEGO DE CADA PASADA DE LA LISTA
        // Si el pivot es el menor elemento en la Lista,
        // pivot es la cabeza
        if ((*newHead) == NULL)     
            (*newHead) = pivot;     

        // newEnd pasa a ser el ultimo nodo
        (*newEnd) = tail;       

        return pivot;   // Devuelve el pivot ubicado en su lugar definitivo
    }

    // metodo recursivo de ordenamiento Quicksort
    struct Lista *quickSortRecur(struct Lista *head, struct Lista *end) // 2º: aca viene el puntero a la cabeza, y el puntero al ultimo
    {
        if (!head || head == end){       //esto devuelve la cabeza si es el unico elemento de la lista   
            
            return head;}
        
        Lista *newHead = NULL, *newEnd = NULL;

        struct Lista *pivot = partition(head, end, &newHead, &newEnd); // Devuelve el pivot ubicado en su lugar definitivo

        // 4º: Si el pivot es el menor elemento - no hace falta llamar la recursiva a 
        // la parte izquierda.
        if (newHead != pivot) //si pivot no es el menor
        {
            struct Lista *tmp = newHead;       
            while (tmp->next != pivot)  //Esto lo hace para despues ordenar la lista de menores: El siguiente al tmp es el pivot?
                tmp = tmp->next;
            tmp->next = NULL;   //el ultimo elemento de la lista de menores lo hace apuntar a NULL

            // Llamada Recursiva para la lista antes del pivot
            newHead = quickSortRecur(newHead, tmp); //ACA manda la lista de menores y la recupera ordenada

            tmp = getTail(newHead); //uso un temporal para la cola de la lista ordenada de menores
            tmp->next = pivot;  //y a la cola le setea el next al pivot
            //Estos 2 pasos son para concatenar la lista menor al pivot con el pivot
        }

        // Llamada Recursiva para la lista de mayores al pivot
        pivot->next = quickSortRecur(pivot->next, newEnd);  

        return newHead; //Al fin de esto me devuelve la lista bien ordenada
    }

    // metodo envoltorio del metodo recursivo
    void quickSort(struct Lista **headRef)      //  1º: aca viene la lista de eventos desordenada
    {
        (*headRef) = quickSortRecur(*headRef, getTail(*headRef));   //va a devolver la cabeza de la lista ordenada 
        return;
    }
    void getComp(){
        cout<< "Comp: "<< cc;
    }
};


#endif //PARCIAL2_LISTA_H
