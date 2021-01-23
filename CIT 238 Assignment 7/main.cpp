#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

class Item
{
public:
	Item(string n, double w, double vPP)
		: name(n), weight(w), valuePerPound(vPP)
	{

	}

	string name;
	double weight;
	double valuePerPound;
	double Total()
	{
		return valuePerPound * weight;
	}

	bool operator<(const Item& rhs) const
	{
		return valuePerPound < rhs.valuePerPound;
	}

	bool operator>(const Item& rhs) const
	{
		return valuePerPound > rhs.valuePerPound;
	}
}; 

//Predicate 
bool SortItemsByDecreasingValue(const Item &l, const Item &r)
{
	return l.valuePerPound > r.valuePerPound;
}

//O(n)
//Returns the most profitable combination of items from shopInventory
//Assumes shopInventory is sorted by order of value per weight.
vector<Item> PartialKnapsack(vector<Item> &shopInventory, double weightLimit)
{
	vector<Item> knapsack;

	double currentWeight = 0;

	while (currentWeight < weightLimit && shopInventory.size())
	{
		knapsack.push_back(shopInventory[0]);
		if (shopInventory[0].weight + currentWeight > weightLimit)//take part 
		{
			double leftOver = weightLimit - currentWeight;
			knapsack.back().weight = leftOver;
			currentWeight = weightLimit;
			shopInventory[0].weight -= leftOver;		
		}
		else//take all of it
		{
			currentWeight += shopInventory[0].weight;
			shopInventory.erase(shopInventory.begin()); 
		}
	} 

	return knapsack;
}

void DisplayItems(const vector<Item> &items)
{
	if (items.size() == 0)
		cout << "No items! :(" << endl;
	else
		for (auto val : items)
			cout << val.name << ": " << val.weight << " lbs worth " << val.Total() << " gold" << endl;
}

//Assignment 7: Finish this!
//In this version we CANNNOT take parts of items. Its either all or nothing.
//This algorithm is like the Fibonacci one - it takes forever if you do it 
//the 'easy' recursive way which is O(n*2^n), but with dynamic programming its efficient.
//This is O(n * w) where n is the number of items, w is the weight limit
//Returns the most profitable combination of items from shopInventory 
//Sorting is not required ahead of time for this one
vector<Item> BinaryKnapsack(vector<Item>& shopInventory, double weightLimit)
{
	vector<Item> knapsack;
	
	if (shopInventory.empty() || weightLimit <= 0)
		return knapsack;

	int NumRows = shopInventory.size() + 1;
	int NumColumns = weightLimit + 1;
	vector<vector<int>> table(NumRows, vector<int>(NumColumns));

	for (int i = 0; i < NumRows; ++i)
		for (int j = 0; j < NumColumns; ++j)
			if (i == 0 || j == 0)
				table[i][j] = 0;
			else if (shopInventory[i - 1].weight <= j)
			{
				int totalPrice = shopInventory[i - 1].Total() + table[i - 1][j - (int)shopInventory[i - 1].weight];
				int prevMax = table[i - 1][j];
				if (totalPrice < prevMax)
					table[i][j] = prevMax;
				else
				{
					table[i][j] = totalPrice;
				}
			}else
			{
				table[i][j] = table[i - 1][j];
			}

			int i = shopInventory.size();
			double j = weightLimit;
			while(i > 0 && j >= 0)
			{
				if (table[i][j] != table[i - 1][j])
				{
					j -= shopInventory[i - 1].weight;
					knapsack.emplace_back(shopInventory[i - 1]);
					shopInventory.erase(shopInventory.begin() + i - 1);
				}
				i--;
			}
	
	return knapsack;
}

int main()
{ 
	double weightLimit = 25;
	cout << "Weight Limit: " << weightLimit << endl << endl;

	cout << "The Partial Knapsack Algorithm (which uses Greedy Programming):" << endl;
	vector<Item> alchemistInventory;
	alchemistInventory.push_back({ "Gunpowder", 30, 10 });
	alchemistInventory.push_back({ "Healing Potion", 50, 1 });
	alchemistInventory.push_back({ "Giant Strength Potion", 10, 100 });
	alchemistInventory.push_back({ "Invisibility Potion", 5, 150 });

	cout << "The Alchemist's Inventory:" << endl; 
	DisplayItems(alchemistInventory);

	//Using a predicate function:
	sort(alchemistInventory.begin(), alchemistInventory.end(), SortItemsByDecreasingValue);

	cout << endl << "After Sorting." << endl;
	DisplayItems(alchemistInventory);

	cout << endl << "Stealing some items..." << endl;
	vector<Item> result = PartialKnapsack(alchemistInventory, weightLimit);
	DisplayItems(result);

	cout << endl << "Now, the Binary Knapsack Algorithm (which uses Dynamic Programming):" << endl;
	vector<Item> blacksmithInventory;
	blacksmithInventory.push_back({ "Spear", 10, 8 });//80 gold total
	blacksmithInventory.push_back({ "Sword", 20, 10 });//remember 20 is the weight, 10 is the value per pound. Sword = 200 gold total
	blacksmithInventory.push_back({ "Shield", 15, 9 });//135 gold total 

	cout << "The Blacksmith's Inventory:" << endl;
	DisplayItems(blacksmithInventory);

	//Assignment 7:
	//When you are done, the the correct (most profitable) result should be taking the Spear and the Shield worth 215 total.
	//Even though the sword is worth the most per pound, if we take it then we don't have enough
	//room for anything else. If we take the Spear then we can also take the Shield, getting a higher total value.
	cout << endl << "Stealing some items..." << endl;
	result = BinaryKnapsack(blacksmithInventory, weightLimit);
	DisplayItems(result);

	return 0;
}