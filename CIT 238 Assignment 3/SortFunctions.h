#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <functional>
#include <assert.h>

#include "Timer.h"


using namespace std;

#pragma region Helper Functions

void DisplayVec(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << ", ";
}

template<class T>
void Swap(T& val1, T& val2)
{
	T temp = val1;
	val1 = val2;
	val2 = temp;
}

int Max(vector<int>& vec)
{
	int max = vec[0];
	for (int i = 0; i < vec.size(); ++i)
		if (max < vec[i])
			max = vec[i];
	return max;

}

int Partition(vector<int>& vec, int leftIndex, int rightIndex)
{
	int midIndex = (leftIndex + rightIndex) / 2;

	//to guarantee faster performance
	//choose a pivot at random, 
	//or calculate an approximate one with 
	//median of 3
	//take the middle value of the left index value, right index value, and midindex value
	int pivot = vec[midIndex];
	if (pivot > vec[leftIndex] && pivot > vec[rightIndex])
		pivot = vec[leftIndex] > vec[rightIndex] ? vec[rightIndex] : vec[leftIndex];
	//repeat for min values

	int i = leftIndex;
	int j = rightIndex;

	bool done = false;
	while (!done)
	{
		//while values to the left pivot are smaller, move to the next
		while (vec[i] < pivot)
			++i;

		while (vec[j] > pivot)
			--j;

		if (i >= j)
			done = true;
		else
		{
			swap(vec[i], vec[j]);
			++i;
			--j;
		}
	}

	//return last index of the smaller partition.
	//NOT the index where the pivot value ended up
	return j;
}

#pragma endregion

#pragma region InsertionSort

void InsertionSort(vector<int>& vec, int left = 0, int right = -1)
{
	if (right == -1)
		right = vec.size();

	for (int i = left + 1; i < right; ++i)
	{
		int j = i;
		while (j > left && vec[j] < vec[j - 1])
		{
			Swap(vec[j], vec[j - 1]);
			--j;
		}
	}
}

#pragma endregion

#pragma region MergeSort
//O(n) space-complexity - has to allocate n memory to move items around.
//NOT an in-place sort, it requires extra vectors to work in while it processes data
void Merge(vector<int>& vec, int leftIndex, int midIndex, int rightIndex)
{
	int numItemsToMerge = rightIndex - leftIndex + 1;
	vector<int> temp(numItemsToMerge);

	//1. compare first number in both sections, take the smallest each time.
	//continue until one section is empty.
	int leftPosition = leftIndex;
	int rightPosition = midIndex + 1;
	int mergedIndex = 0;

	//while both halves have values to compare, compare and take the smaller
	while (leftPosition <= midIndex && rightPosition <= rightIndex)
	{
		if (vec[leftPosition] < vec[rightPosition])
			temp[mergedIndex++] = vec[leftPosition++];
		else
			temp[mergedIndex++] = vec[rightPosition++];
	}

	//2. Take all the remaining values in the left half (if any)
	while (leftPosition <= midIndex)
		temp[mergedIndex++] = vec[leftPosition++];

	//3. Take all the remaining values in the right half (if any)
	while (rightPosition <= rightIndex)
		temp[mergedIndex++] = vec[rightPosition++];

	//4. Copy the merged sorted values (temp) back into the orignal vec
	for (int i = 0; i < numItemsToMerge; ++i)
		vec[leftIndex + i] = temp[i];
	//have to have leftIndex + i because we aren't always starting at the beginning of the vector in each merge
}

//this is the main one with multiple params
//O(nlog(n)) - linearithmic
//better than n^2, worse than n
//head recursion

void MergeSortMain(vector<int>& vec, int leftIndex, int rightIndex)
{
	//Base Case
	if (leftIndex >= rightIndex) return;

	//if the subset we are sorting currently (between left and right) is 10 or fewer, then
	//call insertion instead of recursively calling merge sort.
	if (rightIndex - leftIndex <= 10)
		InsertionSort(vec, leftIndex, rightIndex + 1);

	//General Case
	else
	{
		int midIndex = (rightIndex + leftIndex) / 2;
		MergeSortMain(vec, leftIndex, midIndex);//sort 1st half
		MergeSortMain(vec, midIndex + 1, rightIndex);//sort 2nd half
		Merge(vec, leftIndex, midIndex, rightIndex);//merge 2 sorted halves
	}
}

//User calls this one with just 1 param
void MergeSort(vector<int>& vec)
{
	//don't make the user (future-you programmer)
	//type in the 0 and vec.size()-1 everytime.

	MergeSortMain(vec, 0, vec.size() - 1); 
}

//52 5 97 56 46 64 62
//R1(52 5 97)       R2(56 46 64 62)
//R1-1(52)    R1-2(5 97)
//      R1-2-1(5)      R1-2-2(97)
//			 M1(5, 97)
//M2(5, 52, 97)     (46, 56, 62 64)
//			^			 ^      	
//5, 46, 52, 56, 62, 64, 97
#pragma endregion

#pragma region Counting Sort

//Pesudo Code for counting sort
/*
Input: vector of values.

Create a vector of integers called ‘counts’ with an initial size equal to the largest value in the input vector + 1.
Initialize all values in ‘counts’ to 0.

Loop through the input vector: for each number increment  counts[number] by 1 
(use the values themselves as array indices).

Create an int ‘counter’ starting at 0.
With another counter ‘i’ = 0, Loop through the ‘counts’ vector

While the value at counts[i] is not zero,
Set input vector[counter] = i
decrement counts[i] by 1
increment counter by 1

*/

void CountingSort(vector<int>& vec)
{
	int counter = 0;
	vector<int> counts(Max(vec) + 1);
	for (int i = 0; i < counts.size(); ++i)
		counts[i] = 0;
	
	for (int i = 0; i < vec.size(); ++i)
		counts[vec[i]] = counts[vec[i]] + 1;

	for(int i = 0; i < counts.size(); ++i)
		while (counts[i] != 0)
		{
			vec[counter] = i;
			counts[i]--;
			counter++;
		}
}

#pragma endregion 

#pragma region QuickSelect

int QuickSelect(vector<int>& vec, int left, int right, int k)
{
	try
	{
		if (vec.size() < k)
			throw k;
	}
	catch (int k)
	{
		cout << "The size of 'k' cannot be larger than the number of values inside the " << 
			"container. Size of 'k': " << k << endl;
	}

	//Base Case
	if (left >= right)
		return vec[left];

	int pIndex = Partition(vec, left, right);

	//General case
	if (vec.size() - k <= pIndex)
		return QuickSelect(vec, left, pIndex, k);
	else
		return QuickSelect(vec, pIndex + 1, right, k);
	
}

#pragma endregion
