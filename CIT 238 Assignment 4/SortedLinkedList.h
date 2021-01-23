#pragma once

#include<iostream>

using namespace std;

template<class T>
class SortedLinkedList
{
public:
	struct Node
	{
		Node(T data, Node* next = nullptr)
			: next(next),
			data(data)	{	}

		T data;
		Node* next;
	};

	SortedLinkedList() { 	}//has to be defined explicitly because we defined a copy constructor down below
	SortedLinkedList(SortedLinkedList& otherList) = delete;//= delete means do not automatically provide this function
	SortedLinkedList& operator=(SortedLinkedList& otherList) = delete;

	virtual ~SortedLinkedList()
	{
		//delete all nodes
		Node* temp, * temp2;
		temp2 = temp = head;

		while (temp != nullptr)//find the end of the list
		{
			temp2 = temp->next;
			delete temp;
			temp = temp2;
		}
	}

	void Display() const
	{
		if (IsEmpty())
			cout << "list is empty" << endl;
		else
		{
			Node* temp = head;
			while (temp != nullptr)//loop through all nodes
			{
				cout << temp->data << " -> ";
				temp = temp->next;//move to the next node (by assigning its address to temp)
			}
			cout << "nullptr" << endl;
		}
	}

	int Size() const
	{
		return size;
	}

	bool IsEmpty() const
	{
		return head == nullptr;
		return size == 0;
	}

	void PopFront()
	{
		if (IsEmpty())//Case 1: List is Empty
			return;

		if (head == tail)
		{
			//Case 2: List has 1 node
			delete head;
			head = tail = nullptr;
		}
		else
		{
			//Case 3: list has multiple nodes
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void PopBack()
	{
		if (IsEmpty())//Case 1: List is Empty
			return;

		if (head == tail)
		{
			//Case 2: List has 1 node
			delete head;
			head = tail = nullptr;
		}
		else//Case 3: List has multiple nodes
		{
			Node* temp = head;
			while (temp->next != tail)//loop until we find the 2nd to last node.
				temp = temp->next;

			temp->next = nullptr;
			delete tail;
			tail = temp;
		}
	}

	void Add(T data)
	{
		Node* temp;
		Node* insertNode;
		

		//Assignment 4 Part 1:
		//This is a normal linked list's push_front. 
		//Change it to add elements to the list so that they are always sorted.
		if (IsEmpty())
			head = tail = new Node(data, head);
		else
		{
			temp = head;
			insertNode = new Node(data);

			while (temp != nullptr)
			{
				// if the data reaches the end of the list
				if (temp->next == nullptr)
				{
					temp->next = insertNode;
					break;
				}

				//handles if the node we're adding is smaller than the head
				if (data <= head->data)
				{
					insertNode->next = head;
					head = insertNode;
					break;
				}

				//
				if (data >= temp->data && data <= temp->next->data)
				{
					insertNode->next = temp->next;
					temp->next = insertNode;
					break;
				}

					temp = temp->next;
			}
		}

		
		//Should add 'data' to the list so that the list maintains a sorted order.
		//i.e. all nodes before it should be smaller than 'data's node, and 
		//all nodes after it should be larger.
		//Hints: you will need a while loop, a temporary Node* pointer, and the 'new' keyword somewhere
		//		you don't need delete - its taken care of in the base class destructor.
	}

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
};