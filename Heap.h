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
void heapify(vector<T> &arr, int n, int i)
{
    int largest = i; //el mas grande va a ser i
    int l = 2*i + 1; //izquierdo
    int r = 2*i + 2; //derecho

    // Si el hijo izquierdo es mas grande que la raiz
    if (l < n && arr[l].getTiempo() > arr[largest].getTiempo())     //si el tiempo l es mas grande que el de largest
        {largest = l;
        }

    // Si el hijo derecho es mas grande que largest
    if (r < n && arr[r].getTiempo() > arr[largest].getTiempo())     //si el tiempo r es mas grande que el de largest
       { largest = r;
        }
    // Si el mas grande no es i
    if (largest != i)
    {
        swap(arr[i], arr[largest]); //cambia de lugar

        // recursividad
        heapify(arr, n, largest);
    }
    cch=cch+3;
}

// main usa este
template<typename T>
void heapSort(vector<T> &arr, int n)
{
    // construye heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

	//extrae de uno a uno los elementos del heap
    for (int i=n-1; i>0; i--)   //desde el ultimo elemento al primero
    {
        // Mueve el actual al final
        swap(arr[0], arr[i]);

        // aplicla heap al reducido
        heapify(arr, i, 0);
    }
}

//imprime
template<typename T>
void printArray(vector<T> &arr, int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i].getTiempo() << " ";
    cout << "\n";
}
void getComp(){
        cout<< "Comp: "<< cch; //comparaciones
    }

#endif //PARCIAL2_HEAP_H