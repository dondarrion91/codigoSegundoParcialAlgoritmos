
#include <iostream>
#include <vector>

using namespace std;
#ifndef PARCIAL2_HEAP_H
#define PARCIAL2_HEAP_H
int cch=0;
template<typename T>
void heapify(vector<T> &arr, int n, int i)  //viene 1º ([1][4][8][5][3][2], 6, 2)
{
    int largest = i; //     Largest=2
    int l = 2*i + 1; //     left = 2*i + 1 => l=5 l=3
    int r = 2*i + 2; //     right = 2*i + 2 => r=6 l=4

    // If left child is larger than root
    if (l < n && arr[l].getTiempo() > arr[largest].getTiempo())     //si (5<6 y [2]>[8])-> en la primera no entra porque 8>2  en la segunda vuelta entra
    {largest = l; //En la segunda largest pasa de 1 a 3.

    }

    // If right child is larger than largest so far
    if (r < n && arr[r].getTiempo() > arr[largest].getTiempo())     //si (6<6 y ) no entra en la primera porque 8>3
    { largest = r;
    }

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
    cch=cch+3;
}

// main function to do heap sort
template<typename T>
void heapSort(vector<T> &arr, int n) // vine ([1][4][8][5][3][2], 6)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)        //i= 6/2 - 1 = 2 => va a hacer: 2,1,0
        heapify(arr, n, i); //mando 1º ([1][4][8][5][3][2][6], 6, 2) y devuelve:  PRIMERA VUELTA ES 8 DPS 4

    // One by one extract an element from heap
    for (int i=n-1; i>0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);//manda  0 al n para que  compara el arreglo en la pos 0 ,1 y 2
    }
}
void getComp(){
    cout<< "Comp: "<< cch;
}

#endif //PARCIAL2_HEAP_H