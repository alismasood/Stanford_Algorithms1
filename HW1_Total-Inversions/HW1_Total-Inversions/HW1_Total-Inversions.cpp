// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

// Returns the number of inversions in an array of integers of size n.
// Inversions are out-of-order numbers.
unsigned int sortcount(int* numbers_array, int n);

// Merges and sorts a passed array of length n. 
// Used internally by sortcount()
unsigned int _mergecount(int* numbers_array, int n);

// Read input file.
bool read_integer_file(std::string filename, int* numbers_array, int& n);

// Uses mocks to test the sortcount() function.
void _test_sortcount();

// Tests the array for some deviations from IntegerArray.txt
void _test_file(int* numbers_array, int n);

// Tests if the array is sorted properly, and that there are no duplicates
void _test_sort(int* numbers_array, int n);

int main()
{
	_test_sortcount();
	int numbers_array [100000];
	int n = 0;

	if (!read_integer_file("IntegerArray.txt", numbers_array, n)) {
		std::cout << "File failed to open." << std::endl;
		return 1;
	}
	_test_file(numbers_array, n);
	unsigned int inversions = sortcount(numbers_array, n);
	_test_sort(numbers_array, n);
	std::cout << "Inversions: " << inversions << std::endl;

    return 0;
}

unsigned int sortcount(int* numbers_array, int n) {
	//
	if (n < 2) {
		return 0;
	}
	else if (n == 2) {
		// If there is an inversion
		if (numbers_array[0] > numbers_array[1]) {
			int temp = numbers_array[0];
			numbers_array[0] = numbers_array[1];
			numbers_array[1] = temp;
			return 1;
		}
		// No Inversion
		else
			return 0;
	}

	else {
		int n_left = (n + 1) / 2;
		int n_right = n / 2; 
		int i_left = 0;
		int i_right = n_left;
		int* right_array = &(numbers_array[i_right]);			// address of first element of the right side of the array
		// Count number of inversions on the left
		unsigned int left = sortcount(numbers_array, n_left);

		// Count number of inversions on the right
 		unsigned int right = sortcount(right_array, n_right);

		// Count inversions between both sides
		unsigned int split = _mergecount(numbers_array, n);

		// Return total
		return left + right + split;
	}
}

unsigned int _mergecount(int* numbers_array, int n) {
	int* temp_array = new int[n];
	int n_left = (n + 1) / 2;		
	int n_right = n / 2;
	int i_left = 0;
	int i_right = n_left;
	int i_temp = 0;

	int end_left = n_left - 1;
	int end_right = n - 1;
	unsigned int num_inversions = 0;

	// While neither array is empty
	while (i_left <= end_left && i_right <= end_right) {
		// Compare current indices
		if (numbers_array[i_left] <= numbers_array[i_right]) {
			temp_array[i_temp++] = numbers_array[i_left++];
		}
		else {
			assert(end_left - i_left + 1 >= 1);
			num_inversions += end_left - i_left + 1;
			temp_array[i_temp++] = numbers_array[i_right++];
			
		}
	}
	// If right is empty
	while (i_left <= end_left) {
		temp_array[i_temp++] = numbers_array[i_left++];
	}
	// If left is empty
	while (i_right <= end_right){
		temp_array[i_temp++] = numbers_array[i_right++];
	}

	// Move sorted numbers back into number array
	for(int i = 0; i < n; i++) {
		numbers_array[i] = temp_array[i];
	}

	delete[] temp_array;

	return num_inversions;
}

bool read_integer_file(std::string filename, int* numbers_array, int& n) {
	std::ifstream inputfile(filename);

	if (inputfile.bad()) {
		return false;
	}
	int number;
	while (inputfile >> number) {
		numbers_array[n] = number;
		n++;
	}
	return true;
}

void _test_sortcount() {
	int test1[3] = { 0, 2, 1 };
	assert(sortcount(test1, 3) == 1);
	int test2[6] = { 5, 4, 3, 2, 1, 0 };
	assert(sortcount(test2, 6) == 15);
	int test3[20] = { 0, 1, 20, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	assert(sortcount(test3, 20) == 17);
	int test4[21] = { 0, 1, 21, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	assert(sortcount(test4, 21) == 18);
	int test5[13] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	assert(sortcount(test5, 13) == 78);

}

void _test_file(int* numbers_array, int n) {
	assert(n == 100000);
	assert(numbers_array[0] == 54044);
	assert(numbers_array[99999] == 91901);
}

void _test_sort(int* numbers_array, int n) {
	for (int i = 1; i < n; i++) {
		assert(numbers_array[i] > numbers_array[i - 1]);
	}
}