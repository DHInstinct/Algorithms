/*
Daniel Hartley
Assigment 5

Asad and I collaborated on this assignment 

*/


#include <iostream>
#include <string>
#include <time.h>

#include "BinarySearchTree.h"
#include "Timer.h"

using namespace std;


int main()
{

	srand(time(NULL));
	Timer timer;

	BinarySearchTree<string, double> tree;
	tree.Add(5, "Pancakes");
	tree.Add(3, "Pasta");
	tree.Add(2, "Spaghetti");
	tree.Add(1, "Pizza");
	tree.Add(2.5, "Scones");
	tree.Add(4, "Fries");
	tree.Add(7, "Coffee");
	tree.Add(6, "Tea");
	tree.Add(6.5, "Crackers");
	tree.Add(9, "Cookie");
	tree.Add(8, "Sub");
	tree.Add(8.5, "Bread");
	tree.Add(10, "Cake");
	tree.Add(9.5, "Toast");

	
	tree.DisplayInTreeFormat();
	
	cout << endl;
	tree.BalanceTree();
	tree.DisplayInTreeFormat();

	BinarySearchTree<string, double> tree2;
	tree2.Add(1, "test");
	tree2.Add(2, "test");
	tree2.Add(3, "test");
	tree2.Add(4, "test");
	tree2.Add(5, "test");
	tree2.Add(6, "test");
	tree2.Add(7, "test");
	tree2.Add(8, "test");
	tree2.Add(9, "test");
	tree2.Add(10, "test");

	
	tree2.DisplayInTreeFormat();
	timer.Start();
	tree2.Search(10);
	timer.Stop();
	timer.Report("Time it takes to search for 10 unbalanced");

	tree2.BalanceTree();

	timer.Start();
	tree2.Search(10);
	timer.Stop();
	timer.Report("Time it takes to search for 10 Balanced");
	tree2.DisplayInTreeFormat();



	return 0;
}

