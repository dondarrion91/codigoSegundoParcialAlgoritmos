<<<<<<< HEAD
=======
//
// Created by julian on 3/6/20.
//
>>>>>>> Javier

#include <iostream>
#include <vector>

using namespace std;
#ifndef PARCIAL2_HEAP_H
#define PARCIAL2_HEAP_H
<<<<<<< HEAD
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
=======
<<<<<<< HEAD
int cch=0;
template<typename T>
void heapify(vector<T> &arr, int n, int i)  //viene 1º ([1][4][8][5][3][2], 6, 2)   //([1][4][8][5][3][2], 6, 1)    //([1][5][8][4][3][2], 6, 3)    ////([1][5][8][4][3][2], 6, 0)
{
    // Crea el nodo raiz
    int largest = i; //     Largest=2               //Largest=1 //largest=3                             //largest=0
    int l = 2*i + 1; //     left = 2*i + 1 => l=5   //left=3    //l=7                                   //l=1
    int r = 2*i + 2; //     right = 2*i + 2 => r=6  //right=4   //r=8-> no va a entrar en ningun lado   //r=2

    // If left child is larger than root
    if (l < n && arr[l].getTiempo() > arr[largest].getTiempo())     //si (5<6 y [2]>[8])-> no entra // (3<6 y [5]>[4])->si entra  //      //(1<6 y [5]>[1])->si
        {largest = l;   //      //largest=3     //     //largest=1
        }

    // If right child is larger than largest so far
    if (r < n && arr[r].getTiempo() > arr[largest].getTiempo())     //si (6<6 y %? >[8] )->no entra //(4<6 y [3]>[5])->no entra //      //(2<6 y [8]>[5])->si
       { largest = r;   //      //      //      //largest=2
        }
    // If largest is not root
    if (largest != i)   //largest=2->no entra   //largest=3 != i=1 -> entra     //      //2!=0->si
    {
        swap(arr[i], arr[largest]); //      //queda: [1][5][8][4][3][2]     //      //queda: [8][5][1][4][3][2]

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);   //      //mando ([1][5][8][4][3][2], 6, 3)
    }
    cch=cch+3;
}       //segun lo entiendo al terminar esto los ordeno de mayor a menor [8][5][4][3][2][1]

// main function to do heap sort
template<typename T>
void heapSort(vector<T> &arr, int n) // vine ([1][4][8][5][3][2], 6)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)        //i= 6/2 - 1 = 2 => va a hacer: 2,1,0
        heapify(arr, n, i); //mando 1º ([1][4][8][5][3][2], 6, 2) y devuelve: [8][5][4][3][2][1]

    // One by one extract an element from heap
    for (int i=n-1; i>0; i--)   //desde el ultimo elemento al primero
    {
        // Move current root to end
        swap(arr[0], arr[i]);   //swapea el primero con el actual:  [1][5][4][3][2][8]  // [2][5][4][3][1][8]

        // call max heapify on the reduced heap
        heapify(arr, i, 0);     //mando ([1][5][4][3][2][8], 5, 0) y devuelve lo mismo  //([2][5][4][3][1][8], 4, 0)
=======

template<typename T>
void heapify(vector<T> &arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l].getTiempo() > arr[largest].getTiempo())
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].getTiempo() > arr[largest].getTiempo())
        largest = r;
>>>>>>> Javier

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
<<<<<<< HEAD
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
    cch=cch+3;
=======

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
>>>>>>> Javier
}

// main function to do heap sort
template<typename T>
<<<<<<< HEAD
void heapSort(vector<T> &arr, int n) // vine ([1][4][8][5][3][2], 6)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)        //i= 6/2 - 1 = 2 => va a hacer: 2,1,0
        heapify(arr, n, i); //mando 1º ([1][4][8][5][3][2][6], 6, 2) y devuelve:  PRIMERA VUELTA ES 8 DPS 4
=======
void heapSort(vector<T> &arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
>>>>>>> Javier

    // One by one extract an element from heap
    for (int i=n-1; i>0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
<<<<<<< HEAD
        heapify(arr, i, 0);//manda  0 al n para que  compara el arreglo en la pos 0 ,1 y 2
    }
}
void getComp(){
    cout<< "Comp: "<< cch;
}

#endif //PARCIAL2_HEAP_H
=======
        heapify(arr, i, 0);
>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d
    }
}

/* A utility function to print array of size n */
template<typename T>
void printArray(vector<T> &arr, int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i].getTiempo() << " ";
    cout << "\n";
}
<<<<<<< HEAD
void getComp(){
        cout<< "Comp: "<< cch;
    }
=======
>>>>>>> 8f9dc2faf66360ee71369ab10bbc473a969e9c5d

#endif //PARCIAL2_HEAP_H
>>>>>>> Javier
