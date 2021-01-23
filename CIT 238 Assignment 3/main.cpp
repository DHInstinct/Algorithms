/*
Daniel Hartley 
Assignment 3 
Due : 2/24/20
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

#include "Timer.h"
#include "SortFunctions.h"

using namespace std;


int main()
{
	srand(time(0));
	int n1 = 10, n2 = 100, n3 = 1000;

	vector<int> inputVec = { 2, 1, 0, 2, 0, 1, 1, 2, 2 };

	vector<int> testVec = { 7, 3, 6, 8, 2, 1, 7, 4, 3, 7, 4, 9, 4, 6, 4 };
	
	vector<int> vec(n2);
	for (int i = 0; i < vec.size(); ++i)
		vec[i] = rand() % 100 + 1;


	cout << "Vector to sort:" << endl;
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl << endl;

	//Insertion Sort

	cout << "Insertion Sort without Params " << endl;
	InsertionSort(vec);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl << endl;
	
	cout << "Insertion Sort with Params 1st Half" << endl;
	InsertionSort(vec, 0, vec.size()/2);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl << endl;

	cout << "Insertion Sort with Params 2nd Half" << endl;
	InsertionSort(vec, 5, vec.size());
	//InsertionSort(vec, 50, vec.size()); Use for n2(100ints)
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl << endl;

	//MergeSort Part

	cout << "MergeSort using Insertion" << endl;
	MergeSort(vec);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl << endl;

	cout << "MergeSort" << endl;
	MergeSort(vec);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl << endl;

	//CountingSort Part

	cout << "CountingSort" << endl;
	CountingSort(inputVec);
	DisplayVec(inputVec);
	random_shuffle(inputVec.begin(), inputVec.end());
	cout << endl << endl;

	//QuickSelect Part

	cout << "QuickSelect 3rd smallest number is : " ;
	cout <<	QuickSelect(vec, 0, vec.size() - 1, 3) << endl;
	InsertionSort(vec);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl;

	cout << "QuickSelect 15th smallest number is : ";
	cout << QuickSelect(vec, 0, vec.size() - 1, 15) << endl;
	InsertionSort(vec);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl;

	cout << "QuickSelect 50th smallest number is (Median Value) : ";
	cout << QuickSelect(vec, 0, vec.size() - 1, 50) << endl;
	InsertionSort(vec);
	DisplayVec(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << endl;

	return 0;
}