#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>

#include "Timer.h"

using namespace std;

//complexity: O(n)
int Max(vector<int>& vec)
{
	int max = vec[0];
	for (int i = 0; i < vec.size(); ++i)
		if (max < vec[i])
			max = vec[i];
	return max;

}

//complexity: O(n)
int Min(vector<int>& vec)
{
	int min = vec[0];
	for (int i = 0; i < vec.size(); ++i)
		if (min > vec[i])
			min = vec[i];
	return min;
}

//complexity: O(n)
int Mean(vector<int>& vec)
{
	int sum = 0;
	for (int i = 0; i < vec.size(); ++i)
		sum += vec[i];

	return sum / vec.size();
}

//complexity: O(n)
int Mode(vector<int>& vec)
{
	int mode = vec[0];
	int counter = 0;
	int maxCount = 0;

	for(int i = 0; i < vec.size() - 1; ++i)
	{ 
		if (vec[i] == vec.size() - 1)
			return mode;

		if (vec[i + 1] != vec.size() - 1 && vec[i] == vec[i + 1])
			counter++;
		
		//if the counter is greater than the previous counter that means there is a greater mode
		if (counter > maxCount)
		{
			maxCount = counter;
			mode = vec[i];
		}
		if(vec[i + 1] != vec.size() - 1 && vec[i] != vec[i + 1])
			counter = 0;
	}
	
	return mode;
}

//complexity: O(n)
void DisplayVec(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << ", ";
	}
}

//complexity: O(1)
template<class T>
void Swap(T& val1, T& val2)
{
	T temp = val1;
	val1 = val2;
	val2 = temp;
}

//complexity: O(n^2)
void BubbleSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
		for (int j = 0; j < vec.size() - 1; ++j)
			if (vec[j] > vec[j + 1])
				Swap(vec[j], vec[j + 1]);
}

//complexity: O(n^2)
void BubbleSortNew(vector<int>& vec)
{
	bool isSwapped;
	for (int i = 0; i < vec.size(); ++i)
	{
		isSwapped = false;
		for (int j = 0; j < vec.size() - i - 1; ++j) // subtracting i here because we're subtracting the amount 
		{											 // of elements that are already sorted. So it checks the least
			if (vec[j] > vec[j + 1])				 //amount of elements possible
			{
				Swap(vec[j], vec[j + 1]);
				isSwapped = true;

			}
		}
		if (isSwapped == false) // just checking if no elements were swapped in the loop it stops early
			break;				// this prevents the loop from checking an already sorted container.

		
	}
}

int main()
{
	srand(time(NULL));

	Timer timer;
		
	int n1 = 10, n2 = 100, n3 = 1000;

	vector<int> vec;
	vec.resize(n3);

	//placing nums into vector
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i] = rand() % 1000 + 1;
	}

	//To see the mode working
	vec[0] = 42;
	vec[1] = 42;
	vec[2] = 42;
	vec[3] = 42;

	sort(vec.begin(), vec.end()); 
	//DisplayVec(vec);
	cout << endl;
	cout << "Min: " << Min(vec) << endl;
	cout << "Max: " << Max(vec) << endl;
	cout << "Mean: " << Mean(vec) << endl;
	cout << "Mode: " << Mode(vec) << endl;
	
	cout << endl;

	//Shuffling the already sorted vector from min max mean mode.
	random_shuffle(vec.begin(), vec.end());

	timer.Start();
	BubbleSort(vec);
	timer.Stop();
	timer.Report("BubbleSort");

	//Shuffling the already sorted vector from in class bubble sort
	random_shuffle(vec.begin(), vec.end());

	timer.Start();
	BubbleSortNew(vec);
	timer.Stop();
	timer.Report("NewBubbleSort");
	//DisplayVec(vec);

	return 0;
}