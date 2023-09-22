#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>

using namespace std;

void quickSort(int arr[], int left, int right);

int partitionFinal(int arr[], int left, int right);

void swap(int *a, int *b);

void printArray(int arr[], int size);

#endif //QUICKSORT_H