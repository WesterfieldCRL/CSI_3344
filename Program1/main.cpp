/*
Author: Wesley Anastasi
Class: CSI 3344
Due Date: September 22, 2023
*/

/*
This program implements a quicksort algorithm to sort an array of integers.
It uses a partition function to sort the array, and then recursively calls
itself to sort the two halves of the array. It also uses a counter to count
the number of comparisons made during the sorting process.

This program compares the number of comparisons made when using different
pivot selection methods. The pivot selection methods are:
    - final element
    - first element
    - random element
    - median of three (first, middle, and last elements)

*/

#include <iostream>
#include <random>
#include <fstream>

using namespace std;


enum PartitionType
{
    FINAL,
    FIRST,
    RANDOM,
    MEDIAN
};

/**
 * printArray
 * 
 * prints the array
 * 
 * Parameters:
 *   arr - array to be printed
 *   size - size of the array
 * 
 * Return value: none
 */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

/**
 * partition
 * 
 * partitions the array based on the pivot
 * 
 * Parameters:
 *   arr - array to be partitioned
 *   left - left index of the array
 *   right - right index of the array
 *   pivotIndex - index of the pivot
 * 
 * Return value: index of the pivot
 */
int partition(int arr[], int left, int right, int pivotIndex)
{
    while (right > left)
    {
        while (arr[left] <= arr[pivotIndex])
        {
            left++;
        }
        while (arr[right] > arr[pivotIndex])
        {
            right--;
        }
        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
    }
    swap(arr[right], arr[pivotIndex]);
    return right;
}

/**
 * quickSort
 * 
 * sorts the array by recursively calling itself
 * and partitioning the array
 * 
 * Parameters:
 *   arr - array to be sorted
 *   left - left index of the array
 *   right - right index of the array
 *   partitionType - type of partition to use
 *   comparisons - number of comparisons made
 * 
 * Return value: none
 */
void quickSort(int arr[], int left, int right, PartitionType partitionType, long long &comparisons)
{
    if (left < right)
    {
        comparisons += right - left - 1;
        if (partitionType == PartitionType::FINAL)
        {
            int pivot = partition(arr, left, right, right);
            quickSort(arr, left, pivot - 1, partitionType, comparisons);
            quickSort(arr, pivot + 1, right, partitionType, comparisons);
        }
        else if (partitionType == PartitionType::FIRST)
        {
            int pivot = partition(arr, left, right, left);
            quickSort(arr, left, pivot - 1, partitionType, comparisons);
            quickSort(arr, pivot + 1, right, partitionType, comparisons);
        }
        else if (partitionType == PartitionType::RANDOM)
        {
            int pivot = partition(arr, left, right, rand() % (right - left + 1) + left);
            quickSort(arr, left, pivot - 1, partitionType, comparisons);
            quickSort(arr, pivot + 1, right, partitionType, comparisons);
        }
        else if (partitionType == PartitionType::MEDIAN)
        {
            int median;
            if (arr[left] > arr[right])
            {
                if (arr[left] > arr[(left + right) / 2])
                {
                    if (arr[(left + right) / 2] > arr[right])
                    {
                        median = (left + right) / 2;
                    }
                    else
                    {
                        median = right;
                    }
                }
                else
                {
                    median = left;
                }
            }
            else
            {
                if (arr[right] > arr[(left + right) / 2])
                {
                    if (arr[(left + right) / 2] > arr[left])
                    {
                        median = (left + right) / 2;
                    }
                    else
                    {
                        median = left;
                    }
                }
                else
                {
                    median = right;
                }
            }
            int pivot = partition(arr, left, right, median);
            quickSort(arr, left, pivot - 1, partitionType, comparisons);
            quickSort(arr, pivot + 1, right, partitionType, comparisons);
        }
    }
}

/**
 * main
 * 
 * runs quicksort on an array of integers
 * gottten from a file via command line arguments
 * and prints the number of comparisons made
 * 
 * Parameters:
 *   argc - number of arguments
 *   argv - array of arguments
 * 
 * Return value: 0
 */
int main(int argc, char* argv[])
{
    srand(0);
    ifstream input;
    input.open(argv[1]);

    int n = 10000;
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        input >> arr[i];
    }

    long long comparisons = 0;

    quickSort(arr, 0, n - 1, PartitionType::FINAL, comparisons);

    cout << comparisons << endl;

    return 0;
}