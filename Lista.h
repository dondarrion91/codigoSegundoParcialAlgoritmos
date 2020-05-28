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
    }

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
    struct Lista *getTail(struct Lista *cur)
    {
        while (cur != NULL && cur->next != NULL)
            cur = cur->next;
        return cur;
    }

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

        Lista *newHead = NULL, *newEnd = NULL;

        // Partition the list, newHead and newEnd will be updated
        // by the partition function
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

#endif //PARCIAL2_LISTA_H
