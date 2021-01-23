#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <class T, class Key>
class HashTable
{
	struct KeyValuePair
	{
		Key key;
		T value;
		KeyValuePair(Key k, T val)
			: key(k), value(val) //member initialization list
		{
		}
	};

public:
	HashTable(int initialSize = 100)
	{
		table.resize(initialSize);
	}

	void Add(T data, Key key)
	{
		//the hash determines which chain or bucket to put the value in
		table[Hash(key)].push_back(KeyValuePair(key, data));
	}

	//must return a valid index in 'table', and must result in the same index everytime the same key is provided
	int Hash(Key key)
	{
		return key % table.size();
	}

	T Get(Key key)
	{
		int hash = Hash(key);//usually store a value instead of recalculating multiple times.
		for(int i = 0; i < table[hash].size(); ++i)
			if(table[hash][i].key == key)
				return table[hash][i].value;

		throw string("key not found");
	}

	//Contains Function 
	bool Contains(Key key)
	{
		int hash = Hash(key);
		for(int i = 0; i < table[hash].size(); ++i)
			if (table[hash][i].key == key)
				return true;
			else
				return false;
	}

	void Remove(Key key) // This is technically O(n) but if the buckets are spaced out well enough then it is basically O(1) time.
	{
		int hash = Hash(key);
		for (int i = 0; i < table[hash].size(); ++i)
			if (table[hash][i].key == key)
				table[hash].erase(table[hash].begin() + i);
			
	}
	 
	void RemoveData(T data)
	{
		for (int i = 0; i < table.size(); ++i)
			for (int j = 0; j < table[i].size(); ++j)
				if (table[i][j].value == data)
					table[i].erase(table[i].begin() + j);
	}
	
private:
	vector<vector<KeyValuePair>> table;
};