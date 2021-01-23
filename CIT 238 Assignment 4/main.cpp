#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <unordered_map>//Hash Table

#include "MemLeakDetector.h"
#include "Timer.h"
#include "SortedLinkedList.h"//Chain of nodes, each node contains a value and a pointer to the next node
#include "HashTable.h"

using namespace std;

//CIT 238 Assignment 4 Part 3: Finish this function.
//Returns all the modes (if any) of an unsorted input vector in O(n) time (no nested loops)
vector<int> FindAllModes(vector<int> unsortedInput)
{
	vector<int> result;
	int maxCount = 0;
	
	unordered_map<int, int> frequencyTable;

	//This is counting the number of values
	for (int i = 0; i < unsortedInput.size(); ++i)
		frequencyTable[unsortedInput[i]] = frequencyTable[unsortedInput[i]] + 1;

	//Finding the largest frequencyTable value
	maxCount = frequencyTable[0];
	for (int i = 0; i < frequencyTable.size(); ++i)
		if (maxCount < frequencyTable[i])
			maxCount = frequencyTable[i];

	//places modes into the results vector
  	for (int i = 0; i < frequencyTable.size(); ++i)
	{
		if (frequencyTable[i] == maxCount)
			result.emplace_back(i);
 	}
	
	//returing stored modes vector
	return result;
}

int main()
{
	srand(time(0));
	Timer timer;

	cout << "*****************************Part 1*******************************\n";

	//Assignment 4 Part 1 (Testing)
	SortedLinkedList<int> sortedList;
	for(int i = 0; i < 10; ++i)
		sortedList.Add(rand() % 100);
	sortedList.Display();//should display in Sorted order.


	cout << "\n*****************************Part 2*******************************\n";

	//Assignment 4 Part 2
	//Make a hash table with some values and test
	//the new functions 'Contains', 'Remove(key)', and 'Remove(data)' here.

	HashTable<string, int > hTable;
	hTable.Add("Jerry", 1);
	hTable.Add("Harry", 23);
	hTable.Add("Harry", 223);
	hTable.Add("Harry", 2223);
	hTable.Add("Harry", 22223);
	hTable.Add("Barry", 73);
	hTable.Add("Larry", 40);
	hTable.Add("Perry", 55);

	//Contains Function
	cout << "Hash Table contains 1 : " << hTable.Contains(1) << endl;
	cout << "Hash Table contains 200 : " << hTable.Contains(200) << endl;

	//Remove Function
	hTable.Remove(2223);
	hTable.RemoveData("Barry");

	
	cout << "\n*****************************Part 3*******************************\n";

	//Assignment 4 Part 3 (Testing)
	vector<int> randomVector(100);
	for (int& i : randomVector)
	{
		i = rand() % 10;
		cout << i << ", ";
	}
	cout << endl;

	vector<int> modes = FindAllModes(randomVector);

	cout << "The modes of the vector are: ";
	for (int i : modes)
		cout << i << ", ";
	cout << endl;
}