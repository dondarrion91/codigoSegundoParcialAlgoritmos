//
// Created by julian on 3/6/20.
//

#include <iostream>
#include <vector>

using namespace std;
#ifndef PARCIAL2_HEAP_H
#define PARCIAL2_HEAP_H

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

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
template<typename T>
void heapSort(vector<T> &arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
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

#endif //PARCIAL2_HEAP_H
