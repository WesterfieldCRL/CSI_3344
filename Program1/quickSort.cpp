#include <iostream>
#include "quickSort.h"

using namespace std;

void quickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int pivot = partitionFinal(arr, left, right);

        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}

int partitionFinal(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++)
    {
        if (arr[j] < pivot)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[right]);

    printArray(arr, right + 1);

    return i;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}
