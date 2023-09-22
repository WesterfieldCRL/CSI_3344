#include <iostream>
#include <random>
#include <fstream>

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

int main(int argc, char* argv[])
{
    srand(0);
    ifstream input;
    input.open(argv[1]);

    int arr1[10] = { 3, 8, 2, 5, 1, 4, 7, 6, 10, 9 };
    int arr2[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    long long comparisons = 0;

    quickSort(arr1, 0, 9, PartitionType::FIRST, comparisons);

    cout << comparisons << endl;

    comparisons = 0;

    quickSort(arr2, 0, 9, PartitionType::FIRST, comparisons);

    cout << comparisons << endl;

    /*int n = 10000;
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        input >> arr[i];
    }

    long long comparisons = 0;

    quickSort(arr, 0, n - 1, PartitionType::RANDOM, comparisons);

    cout << comparisons << endl;*/

    return 0;
}