/*
	Daniel Hartley
	Algorithms
	Assignment 1
*/

#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

void DisplayVec(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << endl;
	}
}

void ReturnLargest(vector<int> &vec) 
{
	int max = vec[0];

	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i] = rand() % 100 + 1;
		//cout << vec[i] << endl;
	}

	DisplayVec(vec);

	for (int i = 1; i < vec.size(); ++i)
	{
		if (vec[i] > max)
			max = vec[i];
	}

	cout << "The largest number is: " << max << endl;
}

void Return3rdLargest(vector<int> &vec) 
{
	for (int i = 0; i < 100; ++i) // Placing number into container
	{
		vec.emplace_back(i);
	}
	
	random_shuffle(vec.begin(), vec.end()); // randomize
	vec.resize(10);	// resize

	int first = vec[0];	  
	int second = 0;	   
	int third = 0;	   

	//First largest
	for (int i = 1; i < vec.size(); ++i)
	{
		if (vec[i] > first)
		{
			first = vec[i];
		}
	}
	 
	//Just to see what the vector contains
	DisplayVec(vec);
	//cout << "The 1st largest number is: " << first << endl;

	//Second Largest	
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int i = 0; i < vec.size(); ++i)
			if (vec[i] > second && vec[i] < first)
				second = vec[i];
	}
	//cout << "The 2nd largest number is: " << second << endl;

	//Third Largest
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int i = 0; i < vec.size(); ++i)
			if (vec[i] > third && vec[i] < second)
				third = vec[i];
	}

	cout << "The 3nd largest number is: " << third << endl;
}

void Return3rdLargestSort(vector<int>& vec)
{
	int first = vec[0];
	int second = 0;
	int third = 0;

	for (int i = 0; i < 100; ++i) // Placing number into container
	{
		vec.emplace_back(i);
	}

	random_shuffle(vec.begin(), vec.end()); // randomize
	vec.resize(10);	// resize
	sort(vec.rbegin(), vec.rend());// sorted from largest to smallest using reverse iterators

	DisplayVec(vec);
	
	
	//First largest
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] > first)
		{
			first = vec[i];
		}
	}
	//cout << "The 1st largest number is: " << first << endl;

	//Second Largest	
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int i = 0; i < vec.size(); ++i)
			if (vec[i] > second && vec[i] < first)
				second = vec[i];
	}
	//cout << "The 2nd largest number is: " << second << endl;

	//Third Largest
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int i = 0; i < vec.size(); ++i)
			if (vec[i] > third && vec[i] < second)
				third = vec[i];
	}

	cout << "(SORTED) The 3rd largest number is: " << third << endl;
}


int main()
{
	srand(time(0));

	vector<int> vec(10);
	vector<int> vec2(10);
	vector<int> vec3(10);

	ReturnLargest(vec);
	cout << '\n';
	Return3rdLargest(vec2); 
	cout << '\n';
	Return3rdLargestSort(vec3);

	/*
	4:

	  The most efficent algorithm is the sorted version
	  because if you know what value you're looking for 
	  (largest, or smallest) you know where the number is
	  located in the container if it is sorted, this is how
	  it affects it. 
	  
	  If the array is already sorted then the sorted one would
	  faster rather than unsorted. Because it wouldn't take more runtime to sort the
	  container. Then find the value you're looking for.
	
	*/


	return 0;
}	