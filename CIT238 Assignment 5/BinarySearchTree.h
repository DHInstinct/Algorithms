#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
	Graph - set of vertices (storage nodes) and edges (like 'next' pointer)
		Tree Data Structure (Not the plant)
			A graph with limitations: no cycles or loops
			Unary Tree = Linked List (tree with one child for each node)
			Binary Tree = each node can have up to 2 children
			Decision Tree
			File Tree
			Quad Tree
			Oct Tree
			Binary Search Tree 
				The parent's key is larger than its left child's 
				key and smaller than its right child's key
				Also only works for unique keys.
				Search, Add, and Remove in O(Log(n))
				Traversal (display) O(n)
				
*/

template <class T, class K>
class BinarySearchTree
{
private:
	struct Node
	{
		Node* left = nullptr;
		Node* right = nullptr;
		//Node* parent;
		T value;
		K key;

		Node(K k, T val = T(), Node* l = nullptr, Node* r = nullptr)
			: key(k), value(val), left(l), right(r)
		{

		};
	};

	Node* root = nullptr;
	int size = 0;
	int height = 0;

public:
	void Add(K key, T value)
	{
		AddHelper(root, key, value);
	}

	//Add function overloaded 
	

	BinarySearchTree() {}//required because we defined another (copy) constructor
	~BinarySearchTree()
	{
		ClearHelper(root);
	}
	BinarySearchTree(BinarySearchTree& otherTree) = delete;
	BinarySearchTree& operator=(BinarySearchTree& otherTree) = delete;

	void Clear()//remove all nodes
	{
		ClearHelper(root);
		root = nullptr;
	}

	T Search(const K &key) const
	{
		return SearchHelper(root, key);//flowing off the end of a function = even with no return, it will return the last calcualted value
	}

	void Remove(K key)
	{
		RemoveHelper(root, key);
	}

private:

	void Add(Node *node)
	{
		AddHelper(root, node);
	}

	void AddHelper(Node*& node, Node* otherNode)
	{
		if (node == nullptr)
			node = otherNode;
		else if (otherNode->key > node->key)
			AddHelper(node->right, otherNode);
		else
			AddHelper(node->left, otherNode);
	}

	void ClearHelper(Node* node)
	{
		if (node)
		{
			ClearHelper(node->left);
			ClearHelper(node->right);
			delete node;
		}
	}
	
	void AddHelper(Node*& node, K key, T value)
	{
		if (node == nullptr)
			node = new Node(key, value);
		else if (key > node->key)
			AddHelper(node->right, key, value);
		else
			AddHelper(node->left, key, value);
	}

	T SearchHelper(Node* node, const K &key) const
	{
		if (node == nullptr)
			throw string(to_string(key) + " not found in tree.");

		if (node->key == key)
			return node->value;
		if (key > node->key)
			return SearchHelper(node->right, key);
		else
			return SearchHelper(node->left, key);
	}

	void RemoveHelper(Node*& node, const K &key)
	{
		if (node == nullptr)//value wasn't found (case 1)
			return;

		if (node->key == key)//target node found
		{
			//Case 2: Deleting a Leaf
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
			}
			//Case 4: Deleting a node with 2 children (hard one)
			else if (node->left && node->right)
			{
				Node* attachPoint = node->right;
				while (attachPoint->left != nullptr)
					attachPoint = attachPoint->left;//find the smallest node in the subtree with root at 'node->right'
				attachPoint->left = node->left;
				
				Node* temp = node->right;
				delete node;
				node = temp;
			}
			//Case 3: Deleting a node with 1 child (promote the child to replace the parent)
			else if (node->left)//only has a left child
			{
				Node* temp = node->left;
				delete node;
				node = temp;
			}
			else//only has a right child
			{
				Node* temp = node->right;
				delete node;
				node = temp;
			}
		}
		else if (key > node->key)
			RemoveHelper(node->right, key);
		else
			RemoveHelper(node->left, key);
	}

	void DisplayPreOrderHelper(Node* node)
	{
		if (node == nullptr) return;

		cout << "Node " << node->key << ": " << node->value << endl;
		DisplayPreOrderHelper(node->left);
		DisplayPreOrderHelper(node->right);
	}

	void DisplayPostOrderHelper(Node* node)
	{
		if (node == nullptr) return;

		DisplayPostOrderHelper(node->left);
		DisplayPostOrderHelper(node->right);
		cout << "Node " << node->key << ": " << node->value << endl;
	}

	void DisplayInOrderHelper(Node* node)
	{
		if (node == nullptr) return;

		DisplayInOrderHelper(node->left);
		cout << "Node " << node->key << ": " << node->value << endl;
		DisplayInOrderHelper(node->right);
	}
	
	void DisplayInTreeFormatHelper(Node* node, int height = 0)
	{
		int counter = 0;
		//Base Case
		if (node == nullptr) 
			return;
		
		//General case for left
		for (int i = 0; i < height; ++i) {
			cout << '\t';
		}

		// if the height is zero than display the root
		if (height == 0)
			cout << "Tree Root: " << root->key << ", " << root->value << endl;

		if (node->left == nullptr)
			cout << '\t' << node->value << " Left: Nullptr" << endl;
		else
			cout << '\t' << node->value << "Left: " << node->left->key << ", " << node->left->value << endl;
		
		DisplayInTreeFormatHelper(node->left, height + 1);

		//General Case for the right
		for (int i = 0; i < height; ++i) {
			cout << '\t';
		}

		if (node->right == nullptr)
			cout << '\t' << node->value << " Right: Nullptr" << endl;
		else
			cout << '\t' << node->value << " Right: " << node->right->key << ", " << node->right->value << endl;
		
		DisplayInTreeFormatHelper(node->right, height + 1);
	}
		
public:
	//PreOrder = Top Down, display a node first then its 2 children
	void DisplayPreOrder()
	{
		DisplayPreOrderHelper(root);
	}

	//PostOrder traversal = display children first, then parent
	void DisplayPostOrder()
	{
		DisplayPostOrderHelper(root);
	}

	//In-Order traversal: left to right (display left child first, then parent, then right child)
	void DisplayInOrder()
	{
		DisplayInOrderHelper(root);
	}


	void DisplayInTreeFormat()
	{
		DisplayInTreeFormatHelper(root);
	}

	void BalanceTree()
	{
		vector<Node*> nodePtr;											 
		if (root == nullptr)											 
			return;														 
		BalanceTreeHelper(nodePtr, root);								 
		random_shuffle(nodePtr.begin(), nodePtr.end());					 
		root = nodePtr[0];												 
		for (int i = 1; i < nodePtr.size(); ++i)						 
			this->Add(nodePtr[i]);										 

	}

	void BalanceTreeHelper(vector<Node*> &vec, Node *node)
	{
		if (node == nullptr)
			return;
		BalanceTreeHelper(vec, node->left);
		BalanceTreeHelper(vec, node->right);
		vec.emplace_back(node);
		node->left = nullptr;
		node->right = nullptr;

	}

	bool isEmpty()
	{
		return root == nullptr;
	}

	int Size()
	{
		return size;
	}

};