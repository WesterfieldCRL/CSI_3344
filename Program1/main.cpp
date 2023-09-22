#include <iostream>
//#include "quickSort.h"

using namespace std;

enum class PartitionType
{
    FINAL,
    FIRST,
    RANDOM,
    MEDIAN
};

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int partition(int arr[], int left, int right, int pivot, int pivotIndex)
{
    int i = left;

    for (int j = left; j < right; j++)
    {
        if (arr[j] < arr[pivotIndex])
        {
            swap(arr[i], arr[j]);
            //printArray(arr, right + 1);
            i++;
        }
    }

    swap(arr[i], arr[right]);
    //printArray(arr, right + 1);

    return i;
}

/*int partition(int data[], int small_index, int big_index, int pivot, int pivot_index)
{
    do
    {
        while (data[big_index] <= pivot)
        {
            big_index++;
        }
        while (data[small_index] > pivot)
        {
            small_index--;
        }
        if (big_index < small_index)
        {
            swap(data[big_index], data[small_index]);
        }
    } while (small_index > big_index);
    swap(data[small_index], data[pivot_index]);
    return pivot_index;
}*/

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int left, int right, PartitionType partitionType)
{
    if (left < right)
    {
        if (partitionType == PartitionType::FINAL)
        {
            int pivot = partition(arr, left, right, arr[right], right);

            quickSort(arr, left, pivot - 1, partitionType);
            quickSort(arr, pivot + 1, right, partitionType);
        }
        else if (partitionType == PartitionType::FIRST)
        {
            int pivot = partition(arr, left, right, arr[left], left);
            //printArray(arr, right + 1);
            //cout << "Pivot index: " << pivot << endl;
            quickSort(arr, left, pivot - 1, partitionType);
            quickSort(arr, pivot + 1, right, partitionType);
        }
    }
}

int main()
{
    int arrFinal[] = { 10, 7, 8, 9, 1, 5 };
    int arrFirst[] = { 10, 7, 8, 9, 1, 5 };
    int arrRandom[] = { 10, 7, 8, 9, 1, 5 };
    int arrMedian[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(arrFinal) / sizeof(arrFinal[0]);

    cout << "Unsorted array: " << endl;
    printArray(arrFinal, n);

    cout << endl;

    cout << "sorting Final" << endl;
    quickSort(arrFinal, 0, n - 1, PartitionType::FINAL);
    cout << "sorting First" << endl;
    quickSort(arrFirst, 0, n - 1, PartitionType::FIRST);

    //quickSort(arrRandom, 0, n - 1, PartitionType::RANDOM);
    //quickSort(arrMedian, 0, n - 1, PartitionType::MEDIAN);

    cout << "Sorted array final: " << endl;

    printArray(arrFinal, n);

    cout << endl;  

    cout << "Sorted array first: " << endl;

    printArray(arrFirst, n);

    return 0;
}