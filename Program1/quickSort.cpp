#include <iostream>

using namespace std;

class QuickSort
{
    public:
        void quickSort(int arr[], int left, int right);
        int partition(int arr[], int left, int right);
        void swap(int *a, int *b);
        void printArray(int arr[], int size);
};