#pragma once

#include <vector>
#include <string>

#include "ConsoleColorer.h"

using namespace std;

/*
This is the same graph class we made together in class, but we 
are going to stick to grid-shaped graphs instead of arbitrary graphs for
your final. This is for 1 reason only - they will look much nicer in the console :)
All the topics we discussed and the algorithms you will be writing would work 
on any shaped graph, grid or otherwise.

Grids are common types of graphs anyway - in well structured city blocks, in
raster images (like photoshop-filter algorithms), in video games, etc.

I've added several functions to make it more visually appealing, and to
make it work smoothly with user-input provided in main.cpp.

The only function we did together that I changed is the Display function,
which will display the graph as a grid of single chars instead of a long list
of city names and what they're connected to. Enjoy!
*/
class GridGraph
{
public:
	struct Node;//Forward Declaration

	struct Edge//Connection
	{
		Node* neighbor = nullptr;
		double cost = 0;

		Edge(Node* n, double c = 0)
			: neighbor(n), cost(c) { }

		void SetCost(double c)
		{
			cost = c;
			for (int i = 0; i < neighbor->neighbors.size(); ++i)//for a grid, will only loop 1-4 times max
			{
				//For the purposes of this graph class, if there is an edge that goes both ways between nodes,
				//then we automatically set the cost to be the same both ways.
				//Some graphs may want to control this, for example a steep hill is cheaper going down than going up.
				if (neighbor->neighbors[i].neighbor == neighbor)
				{
					neighbor->neighbors[i].cost = c;
					break;
				}
			}
		}
	};

	struct Node//Vertex
	{
		//Constructor
		Node(string n = "unnamed", int xPos = 0, int yPos = 0)
			: name(n), x(xPos), y(yPos), visited(false),
			pushed(false), visitedFrom(nullptr), d(INT_MAX),
			color(Color::green), displayChar((char)219) { }

		//Connections to other Nodes
		vector<Edge> neighbors;

	private:
		//For Display purposes
		//I made these private because you should use the 'ChangeColor'
		//function to change these instead.
		//If anyone's wondered about it, Node is complex enough that in other
		//languages it would be a class instead of a struct at this point.
		//Technically it makes no difference in C++ except by 'tradition'
		Color color;
		char displayChar;

	public:
		//For Searching Algorithms
		string name;
		int x, y;//position in space
		bool visited;
		bool pushed;
		int d;
		Node* visitedFrom;

		Color GetColor() const
		{
			return color;
		}
		
		char GetDisplayChar() const
		{
			return displayChar;
		}
		
		void SetAllEdgeCosts(double c)
		{
			for (auto& e : neighbors)
				e.SetCost(c);
		}

		void ChangeColor(Color c)
		{
			if (color == c)
				return;

			color = c;
			
			//Change Symbol
			switch (color)
			{
			case Color::blue:
			case Color::cyan:
			case Color::red:
				displayChar = (char)178;//Not quite solid (for watery colors)
				//These are 'expanded' ASCII characters (weird symbols)
				//Remember ASCII only uses 7 bits for historical reasons,
				//before 8-bit bytes were ubiquitous in computing.
				//Nowadays the 8th bit is used for extra symbols like accented letters.
				break;
			default:
				displayChar = (char)219;//Solid color
			}

			//Change weights
			switch (color)
			{
			case Color::green:
				SetAllEdgeCosts(1);
				break;
			case Color::yellow:
				SetAllEdgeCosts(3);
				break;
			case Color::blue:
			case Color::cyan:
				SetAllEdgeCosts(10);
				break;
			case Color::black:
			case Color::red:
				SetAllEdgeCosts(INT_MAX);
			default://Don't change for other colors (debugging colors)
				break;
			}
		}
	};

	GridGraph(int w, int l);
	GridGraph& operator=(GridGraph& otherGraph); 
	void ConnectGrid();
	void AddEdge(Node *node, Node *neighbor, double weight = 0, bool bothWays = true);
	void Display() const;
	void ResetForSearch();
	void DepthFirstSearch(Node* startPoint, string targetCity);
	void BreadthFirstSearch(Node* startPoint, string targetCity);
	void PrintPath(Node* startNode, Node* endNode); 

	//Just to visualize which nodes are connected
	void ShowNeighbors(char row, char column);

	//Implemeting these 3 algorithms is your final project**************
	//See the .cpp file for pseudocode and the function bodies.
	void PaintFill(char row, char column, Color color);

	void RadialBrush(char row, char column, int radius);

	void UniformCostSearch(char sR, char sC, char eR, char eC);
	//******************************************************************

	//Given a number from 0-62, returns the character
	//we will use in ASCII for that number, from 0-9, A-Z, a-z
	//This is for nothing more than displaying the header row/column
	//and making it easy to display, format, and choose a grid location.
	char NumberToRowColumn(int i) const;

	//Given a row and column (like A1 or 6z)
	//returns the index of that graph node in the vector<Node> nodes 
	//This is just some ASCII chart conversion (skipping punctuation marks)
	//65 = 'A' in ASCII, 48 = '0', and 97 = 'a'
	int RowColToIndex(char row, char column);
	
	//Copy Ctor (Constructor)
	GridGraph(GridGraph& otherGraph)
	{
		*this = otherGraph;
	}

	bool isValidIndex(char row, char column)
	{
		int index = RowColToIndex(row, column);
		return index >= 0 && index < nodes.size();
	}

	bool isValidIndex(int index)
	{
		return index >= 0 && index < nodes.size();
	}

	Node* operator[](int index)
	{
		return &nodes[index];
	}

	Node* GetNode(int row, int column)
	{
		return &nodes[row * columns + column];
	}

	void Add(string n)
	{
		nodes.emplace_back(Node(n));
	} 
	
private:
	int rows = 0, columns = 0;
	vector<Node> nodes;
};