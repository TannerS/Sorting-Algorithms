#include <iostream>
#include "Blyz.h"
#include <boost/chrono/chrono.hpp>
#include <iomanip>
#include <fstream>

#pragma region Global Vars

	int AVERAGE_COUNT = 10;
	int MAX_POWER = 16;
	int CONDITIONS = 4;

#pragma endregion

#pragma region Prototypes

	//function prototypes
	void debugArrayDisplay(int****, int, int);
	// allocate arrays for this program
	void allocateArrays(int****&);
	void displayResults(std::string, double**);
	void allocateTimers(double**&);
	void deallocateArrays(int****&);
	void deallocateTimers(double**&);
	void collectSortTimes(void(*)(int*, int, int), int****, double**);
	void generateArrays(int****);

#pragma endregion

int main()
{
	#pragma region Declare variables
		// arrays: arr[] = avg, arr[][] = conditions, arr[][][] = sorting methods, arr[][][][] = 2^1-2^16
		int**** insert_array;
		int**** merge_array;
		int**** quick_array;
		int**** quick_insert_array;
		int**** quick_random_array;

		// sorting times: arr[] = sorting method, arr[][] = 2^1-2^16
		double** insert_array_times;
		double** merge_array_times;
		double** quick_array_times;
		double** quick_insert_array_times;
		double** quick_random_array_times;

		// allocate arrays
		allocateTimers(insert_array_times);
		allocateTimers(merge_array_times);
		allocateTimers(quick_array_times);
		allocateTimers(quick_insert_array_times);
		allocateTimers(quick_random_array_times);
	#pragma endregion

	#pragma region Main
		// run all necessary functions for insertion sort
		// allocate space to hold numbers to be sorted
		allocateArrays(insert_array);
		// create function pointer
		void(*insert)(int*, int, int) = &Blyz::Sorter<int>::insertionSort;
		// fill array with random numbers
		generateArrays(insert_array);
		// sort and take times
		collectSortTimes(insert, insert_array, insert_array_times);
		// free memory 
		deallocateArrays(insert_array);

		// run all necessary functions for merge sort
		// allocate space to hold numbers to be sorted
		allocateArrays(merge_array);
		// create function pointer
		void(*merge)(int*, int, int) = &Blyz::Sorter<int>::mergeSort;
		// fill array with random numbers
		generateArrays(merge_array);
		// sort and take times
		collectSortTimes(merge, merge_array, merge_array_times);
		// free memory 
		deallocateArrays(merge_array);

		// run all necessary functions for quick sort
		// allocate space to hold numbers to be sorted
		allocateArrays(quick_array);
		// create function pointer
		void(*quick)(int*, int, int) = &Blyz::Sorter<int>::quickSort;
		// fill array with random numbers
		generateArrays(quick_array);
		// sort and take times
		collectSortTimes(quick, quick_array, quick_array_times);
		// free memory 
		deallocateArrays(quick_array);

		// run all necessary functions for quick insertion hybrid sort
		// allocate space to hold numbers to be sorted
		allocateArrays(quick_insert_array);
		// create function pointer
		void(*quick2)(int*, int, int) = &Blyz::Sorter<int>::quickInsertionSort;
		// fill array with random numbers
		generateArrays(quick_insert_array);
		// sort and take times
		collectSortTimes(quick2, quick_insert_array, quick_insert_array_times);
		// free memory 
		deallocateArrays(quick_insert_array);

		// run all necessary functions for quick sort with random pivot
		// allocate space to hold numbers to be sorted
		allocateArrays(quick_random_array);
		// create function pointer
		void(*quick3)(int*, int, int) = &Blyz::Sorter<int>::quickSortRanomPivot;
		// fill array with random numbers
		generateArrays(quick_random_array);
		// sort and take times
		collectSortTimes(quick3, quick_random_array, quick_random_array_times);
		// free memory 
		deallocateArrays(quick_random_array);
	#pragma endregion

	#pragma region Results
		// display time results for the following sorting algorithms
		displayResults("Insert Sort", insert_array_times);
		displayResults("Merge Sort", merge_array_times);
		displayResults("Quick Sort", quick_array_times);
		displayResults("Quick Insert Sort", quick_insert_array_times);
		displayResults("Quick Random Sort", quick_random_array_times);
	#pragma endregion

	#pragma region Deallocate
		// free memory
		deallocateTimers(insert_array_times);
		deallocateTimers(merge_array_times);
		deallocateTimers(quick_array_times);
		deallocateTimers(quick_insert_array_times);
		deallocateTimers(quick_random_array_times);
	#pragma endregion
}

// fill arrays with random numbers
void generateArrays(int**** arr)
{
	#pragma region Generating Arrays W/ Numbers

		for (int j = 0; j < CONDITIONS; j++)
		{
			for (int k = 0; k < MAX_POWER; k++)
			{
				for (int l = 0, random_number = 0, ram = 0; l < ((int)pow(2, k + 1)); l++)
				{
					random_number = -9999 + rand() % (10000 - (-9999) + 1);
					arr[0][j][k][l] = random_number;
				}
			}
		}
	#pragma endregion

	#pragma region Ascending Sorting

		for (int j = 0; j < MAX_POWER; j++)
			Blyz::Sorter<int>::maxHeapSort(arr[0][CONDITIONS - 2][j], pow(2, j + 1));

	#pragma endregion 

	#pragma region Descending Sorting

		for (int j = 0; j < MAX_POWER; j++)
			Blyz::Sorter<int>::minHeapSort(arr[0][CONDITIONS - 1][j], pow(2, j + 1));

	#pragma endregion

	#pragma region Rest Of Arrays

		for (int j = 0; j < CONDITIONS; j++)
		{
			for (int k = 0; k < MAX_POWER; k++)
			{
				for (int l = 0, random_number = 0, ram = 0; l < ((int)pow(2, k + 1)); l++)
				{
					for (int i = 1; i < AVERAGE_COUNT; i++)
						arr[i][j][k][l] = arr[0][j][k][l];
				}
			}
		}

	#pragma endregion
}

// allocate the arrays with proper space for this project
void allocateArrays(int****& arr)
{
	#pragma region Allocate Arrays

		arr = new int***[AVERAGE_COUNT];

		for (int i = 0; i < AVERAGE_COUNT; i++)
			arr[i] = new int**[CONDITIONS];

		for (int i = 0; i < AVERAGE_COUNT; i++)
		{
			for (int j = 0; j < CONDITIONS; j++)
				arr[i][j] = new int*[MAX_POWER];
		}

		for (int i = 0; i < AVERAGE_COUNT; i++)
		{
			for (int j = 0; j < CONDITIONS; j++)
			{
				for (int k = 0; k < MAX_POWER; k++)
					// 2^1 - 2^16
					arr[i][j][k] = new int[((int)pow(2, k + 1))];
			}
		}

	#pragma endregion
}

// allocate space for the timer arrays
void allocateTimers(double**& arr)
{
	arr = new double*[CONDITIONS];

	for (int i = 0; i < CONDITIONS; i++)
		arr[i] = new double[MAX_POWER];

	for (int i = 0; i < CONDITIONS; i++)
	{
		for (int j = 0; j < MAX_POWER; j++)
			arr[i][j] = 0;
	}
}

// free up space
void deallocateArrays(int****& arr)
{
	for (int i = 0; i < AVERAGE_COUNT; i++)
	{
		for (int j = 0; j < CONDITIONS; j++)
		{
			for (int k = 0; k < MAX_POWER; k++)
				delete[] arr[i][j][k];
			delete[] arr[i][j];
		}
		delete[] arr[i];
	}
	delete[] arr;
}

// free up space
void deallocateTimers(double**& arr)
{
	for (int i = 0; i < CONDITIONS; i++)
		delete[] arr[i];
	delete[] arr;
}

// display only what is needed for this project with formatting
void displayResults(std::string name, double** arr)
{
	using namespace std;

	std::cout << std::endl;
	std::cout << "Results for: " << name << std::endl;
	std::cout << std::endl;

	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << "Powers of 2's " << setw(15) << "Time in nanoseconds" << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;

	std::cout << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << "Random #1" << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;


#pragma region Random 1

	std::cout.clear();
	for (int j = 0; j < MAX_POWER; j++)
		std::cout << "2^" << j + 1 << ": " << setw(45) << arr[CONDITIONS - 4][j] << left << std::fixed << std::setprecision(15) << std::endl;

#pragma endregion

#pragma region Random 2

	std::cout << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << "Random #2" << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << std::endl;

	for (int j = 0; j < MAX_POWER; j++)
		std::cout << "2^" << j + 1 << ": " << setw(15) << arr[CONDITIONS - 3][j] << std::fixed << std::setprecision(15) << std::endl;

#pragma endregion

#pragma region Ascending Sorted

	std::cout << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << "Sorted #1" << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << std::endl;

	for (int j = 0; j < MAX_POWER; j++)
		std::cout << "2^" << j + 1 << ": " << setw(15) << arr[CONDITIONS - 2][j] << std::fixed << std::setprecision(15) << std::endl;

#pragma endregion

#pragma region Descending Sorted

	std::cout << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << "Sorted #2" << std::endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	std::cout << std::endl;

	for (int j = 0; j < MAX_POWER; j++)
		std::cout << "2^" << j + 1 << ": " << setw(15) << arr[CONDITIONS - 1][j] << std::fixed << std::setprecision(15) << std::endl;

	std::cout << std::endl;

#pragma endregion
}

// reads in function pointer to read all sort methods the same and does same process with them all
void collectSortTimes(void(*ptr)(int*, int, int), int**** arr, double** arr2)
{
	for (int j = 0; j < CONDITIONS; j++)
	{
		for (int k = 0, power = 0; k < MAX_POWER; k++)
		{
			power = (int)pow(2, k + 1);
			auto t1 = boost::chrono::high_resolution_clock::now();
			for (int i = 0; i < AVERAGE_COUNT; i++)
				ptr(arr[i][j][k], 0, power - 1);
			auto t2 = boost::chrono::high_resolution_clock::now();
			auto time_span = boost::chrono::duration_cast<boost::chrono::duration<double, boost::nano>>(t2 - t1);
			arr2[j][k] = ((double)(time_span.count()) / (double)(AVERAGE_COUNT));
		}
	}
}