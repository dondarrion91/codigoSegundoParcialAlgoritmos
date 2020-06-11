//
// Created by julian on 3/6/20.
//

#include <iostream>
#include <vector>

using namespace std;
#ifndef PARCIAL2_HEAP_H
#define PARCIAL2_HEAP_H
int cch=0;
template<typename T>
void heapify(vector<T> &arr, int n, int i)  //2º: Recordar que en Heap el padre debe ser el mayor
{
    int largest = i; //el mas grande va a ser i //padre
    int l = 2*i + 1; //hijo izquierdo
    int r = 2*i + 2; //hijo derecho

    // Si el hijo izquierdo es mas grande que el padre
    if (l < n && arr[l].getTiempo() > arr[largest].getTiempo())     //si el tiempo l es mas grande que el de largest
        {largest = l;
        }

    // Si el hijo derecho es mas grande que largest
    if (r < n && arr[r].getTiempo() > arr[largest].getTiempo())     //si el tiempo r es mas grande que el de largest
       { largest = r;
        }
    // Si el mas grande no es i
    if (largest != i)   //Si alguno de los hijos es mas grande que el padre
    {
        swap(arr[i], arr[largest]); //cambia de lugar: pone el mas grande como padre

        // recursividad
        heapify(arr, n, largest);   //llama la recursiva para ordenar el nuevo triangulo luego de la rotacion
    }
    cch=cch+3;  //las comparaciones fuera de los if pq hay casos en los que no entra a ninguno pero compara igual
}

// main usa este
template<typename T>
void heapSort(vector<T> &arr, int n)    // 1º: desde el main llamamos esta funcion con el vector desordenado y su tamaño
{
    // construye heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i); //ordena el triangulo entre el padre (i) y sus hijos realizando las rotaciones correspondientes

	//extrae de uno a uno los elementos del heap
    for (int i=n-1; i>0; i--)   //desde el ultimo elemento al primero
    {
        // Mueve el actual al final
        swap(arr[0], arr[i]);   //pone el mayor elemento al final->su lugar definitivo

        // reordena el arbol, sin contar los ultimos que ya estan en su lugar
        heapify(arr, i, 0);
    }
}

void getComp(){
        cout<< "Comp: "<< cch; //comparaciones
    }

#endif //PARCIAL2_HEAP_H