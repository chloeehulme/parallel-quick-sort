#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <omp.h>

#define TASK_SIZE 150
using namespace std;

// Populate array with random values in parallel
void popArray(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

// Swaps two elements
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Split into subarrays, setting element at last index as pivot
int split (int arr[], int low, int high) {

	int pivot = arr[high];
	int small = (low - 1); 

    // Compare each element to pivot (everything smaller than 
	// pivot to LHS, larger than pivot to RHS)
	for (int i = low; i < high; i++) {
		if (arr[i] <= pivot) {
			small++; 
			swap(&arr[small], &arr[i]);
		}
	}

	swap(&arr[small + 1], &arr[high]);
	return (small + 1);
}

// Sort array in parallel using recursion
void quickSort(int arr[], int low, int high) {

    if (low < high) {
        int pi = split(arr, low, high);

		// Create task on LHS and execute using recursion
		#pragma omp task shared(arr) if(high - low > TASK_SIZE)
		{
			quickSort(arr, low, pi - 1);
		}
		// Create task on RHS and execute using recursion
		#pragma omp task shared(arr) if(high - low > TASK_SIZE)
		{
			quickSort(arr, pi + 1, high);
		}
    } 
}

// Print array 
// void printArray(int arr[], int size) {

// 	int i;

// 	for (i = 0; i < size; i++)
// 		cout << arr[i] << " ";
// 	cout << endl;
// }


int main() {

	ofstream fileOut;
	int size = 1000000;
	int arr[size];
    int n = sizeof(arr) / sizeof(arr[0]);

	omp_set_dynamic(0);
	omp_set_num_threads(omp_get_num_procs());

	fileOut.open("quickSort-openMP (size: 1,000,000, imposing task size limit (150)).txt");
    fileOut << endl << "QUICK SORT ALGORITHM (openMP IMPLEMENTATION): " << endl << endl;

	popArray(arr, size);

	// Start clock
	double duration = omp_get_wtime();

    #pragma omp parallel 
	{
        #pragma omp single
	    quickSort(arr, 0, n - 1);
	}

	// Stop clock
	duration = omp_get_wtime() - duration;


	/*
        You can uncomment the below section to verify the program
        operates as expected.
    */

	// cout << "Sorted array: \n";
	// printArray(arr, n);

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
         << duration  << " seconds" << endl;

	fileOut << endl << "Time taken by function: "
         << duration << " seconds" << endl;

	return 0;
}
