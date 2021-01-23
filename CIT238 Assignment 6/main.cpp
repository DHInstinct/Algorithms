#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

#include "Heap.h"
#include "Timer.h"

using namespace std; 


void GreedyMoney(double amount)
{
	//breaking amount into cents
	int fullChange = amount * 100;

	//dividing cents by 25, then subtracting that from the cents * 25, done so on and so forth
	int quarters = fullChange / 25;
	fullChange -= quarters * 25;
	
	int dimes = fullChange / 10;
	fullChange -= dimes * 10;

	int nickles = fullChange / 5;
	fullChange -= nickles * 5;
	
	int pennies = fullChange / 1;
	fullChange -= pennies * 1;
	
	cout << amount <<" cents: Quarters: " << quarters << " Dimes: " << dimes
		<< " Nickles: " << nickles << " Pennies: " << pennies << endl;

}

#pragma region RabinKarp
string ReadFile(string filename)
{
	string result = "";
	ifstream fin;
	fin.open(filename);

	//Figure out how much space we need to store the file contents
	fin.seekg(0, ios::end);//Move to end of the file
	result.reserve(fin.tellg());
	fin.seekg(0, ios::beg);//Move to beginning of the file

	//Read the file. Multiple ways to do this; this method is fast for simply grabbing everything (no parsing)
	result.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());

	fin.close();//Make sure to do this - otherwise it'll say 'file is open in another program' until you restart your computer (usually)
	return result;
}
vector<int> RabinKarp(string source, string pattern)
{
	int sSize = source.size();
	int pSize = pattern.size();

	vector<int> results;
	int pSum = 0;
	int sSum = 0;
	for (int i = 0; i < pSize; ++i)
		pSum += int(pattern[i]);

	for (int i = 0; i < pSize; ++i)
		sSum += int(source[i]);

	for (int i = 0; i < sSize - (pSize - 1); ++i)
	{
		if (sSum == pSum)
		{
			for (int j = 0; j < pSize; ++j) 
				if (pattern[j] != source[i + j])
					break;
				results.emplace_back(i);
		}
		if (i < (sSize - pSize))
		{
			sSum -= int(source[i]);
			sSum += source[i + pSize];
		}
	}
	return results;
}
#pragma endregion

int main()
{
	/* Assignment 6, Part 1:
	Implemented perfectly, this program should only need to call BuildHeap
	exactly 2 times, and display the values indicated.
	Modify Heap.h (but not main) to achieve both goals.

	Making the user manually call BuildHeap at the right times is bad design and doesn't count.

	The 'BuildHeap' method in the Heap class is the most expensive part of maintaining a heap.
	Currently, our implementaiton has it either getting called every time a value is added to the heap,
	or everytime a value is retrieved or displayed from the heap.
	Either way we end up doing it more than necessary, and thats inefficient.
	BuildHeap() should only run if
		1. We are trying to access or display a value in the heap
			AND
		2. The heap has not been built since the last time something was added.

	Note that the 'Pop' function already makes sure it maintains
	the 'heap property' so it doesn't have to rebuild when Pop is called.
	*/

	string hamlet = ReadFile("Hamlet.txt");
	string binary = ReadFile("Binary.txt");
	string dna = ReadFile("DNA.txt");
	string loremIpsum = ReadFile("LoremIpsum150.txt");


	vector<int> results;
	Heap heap;
	Timer timer;

	heap.Add(5);
	heap.Add(12);
	heap.Add(7);
	heap.Add(3);
	heap.Add(4);
	heap.Add(13);

	cout << "Displaying the Heap." << endl;
	heap.Display();

	cout << "The top is: " << heap.Top() << " (Expected: 3)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "The top is: " << heap.Top() << " (Expected: 4)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "The top is: " << heap.Top() << " (Expected: 5)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "The top is: " << heap.Top() << " (Expected: 7)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "Adding a couple more..." << endl;
	heap.Add(6);
	heap.Add(2);
	heap.Add(17);
	heap.Add(20);

	cout << "The top is: " << heap.Top() << " (Expected: 2)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "The top is: " << heap.Top() << " (Expected: 6)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "The top is: " << heap.Top() << " (Expected: 12)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	cout << "The top is: " << heap.Top() << " (Expected: 13)\n";
	cout << "Popping!" << endl;
	heap.Pop();

	//Greedy Money 
	cout << endl;
	GreedyMoney(0.50);
	cout << endl;

	GreedyMoney(0.80);
	cout << endl;

	GreedyMoney(0.99);
	cout << endl;

	GreedyMoney(1.49);
	cout << endl;


	string dnaPattern = "acttttttttattc";

	// RabinKarp Algorithm 
	timer.Start();
	results = RabinKarp(dna, dnaPattern);
	timer.Stop();
	timer.Report("RabinKarp Results");
	cout << "Found " << results.size() << " matches. " << endl;
	for (int i = 0; i < results.size(); ++i)
		cout << "Match at index: " << results[i] << endl;

	return 0;
}