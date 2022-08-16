#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

// Populate array with random values 
void popArray(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 101;
    }
}

// Swaps two elements
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// Split into subarrays, setting element at last index as pivot
int split (int arr[], int low, int high) {

	int pivot = arr[high];
	int i = (low - 1); 

    // Compare each element to pivot (everything smaller than 
	// pivot to LHS, larger than pivot to RHS)
	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++; 
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

// Implement quicksort using recursion 
void quickSort(int arr[], int low, int high) {

	if (low < high) {
		int pi = split(arr, low, high);

		// Recursive call on LHS
		quickSort(arr, low, pi - 1);

		// Recursive call on RHS
		quickSort(arr, pi + 1, high);
	}
}

// Print array 
void printArray(int arr[], int size) {

	int i;

	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}


int main() {

	ofstream fileOut;
	int size = 1000000;
	int arr[size];
	int n = sizeof(arr) / sizeof(arr[0]);

	fileOut.open("quickSort-sequential (size: 1,000,000).txt");
    fileOut << endl << "QUICK SORT ALGORITHM (SEQUENTIAL IMPLEMENTATION): " << endl << endl;

	popArray(arr, size);

	// Start clock
	int duration = clock();

	quickSort(arr, 0, n - 1);

	// Stop clock
	duration = clock() - duration;


	/*
        You can uncomment the below section to verify the program
        operates as expected.
    */

	cout << "Sorted array: \n";
	printArray(arr, n);

	int i;
	fileOut << endl << "Sorted array: \n" << endl;
	for (i = 0; i < size; i++) {
		fileOut << arr[i] << " ";
		if (i != 0 && i % 50 == 0) {
			fileOut << "..." << endl;
		}
	}
	fileOut << endl;


	cout << endl << "Time taken by function: "
         << (float)duration / CLOCKS_PER_SEC  << " seconds" << endl;

	fileOut << endl << "Time taken by function: "
         << (float)duration / CLOCKS_PER_SEC << " seconds" << endl;

	return 0;
}
