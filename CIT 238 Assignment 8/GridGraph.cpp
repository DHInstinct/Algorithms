#include <iostream>
#include <stack>
#include <queue>

#include "GridGraph.h" 

GridGraph::GridGraph(int numRows, int numColumns)
{
	rows = numRows;
	columns = numColumns;

	//Add the nodes.
	//Each node will be named according to its row-column symbols
	//a.k.a. 00, A1, 9Z, etc. Think battleship, but with more.
	for (int r = 0; r < rows; ++r)
		for (int c = 0; c < columns; ++c)
		{
			string name;
			name += NumberToRowColumn(r);
			name += NumberToRowColumn(c);
			Add(name);
		}

	ConnectGrid();
}

GridGraph& GridGraph::operator=(GridGraph& otherGraph)
{
	rows = otherGraph.rows;
	columns = otherGraph.columns;
	nodes = otherGraph.nodes;
	for (int i = 0; i < nodes.size(); ++i)
		nodes[i].neighbors.clear();
	ConnectGrid();
	return *this;
}

int ColorWeight(Color c)
{
	switch (c)
	{
	case Color::black:
	case Color::red:
		return INT_MAX;//black for walls/obstacles, red is lava
	case Color::blue:
	case Color::cyan:
		return 3;//blues are water. we can swim.
	case Color::yellow:
		return 2;//rock or sand or soil
	default:
		return 1;//grass
	}
}

void GridGraph::ConnectGrid()
{
	//Connect the nodes
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			int currentNode = r * columns + c;

			//Connect to the node to the right of the current node
			if (c < columns - 1)//if we are not on the last column
			{
				int rightNode = r * columns + c + 1;
				AddEdge(&nodes[currentNode], &nodes[rightNode], ColorWeight(nodes[currentNode].GetColor()));
			}

			//connect to the node below the current node
			if (r < rows - 1)
			{
				int downNode = (r + 1) * columns + c;
				AddEdge(&nodes[currentNode], &nodes[downNode], ColorWeight(nodes[currentNode].GetColor()));
			}
		}
	}
}

void GridGraph::AddEdge(Node *node, Node *neighbor, double weight, bool bothWays)
{
	node->neighbors.push_back(Edge(neighbor, weight));
	if (bothWays)
		neighbor->neighbors.push_back(Edge(node, weight));
}

void GridGraph::Display() const
{
	//Output header row
	ConsoleColorer::SetConsoleColor(Color::white);
	cout << "  ";
	for (int c = 0; c < columns; ++c)
		cout << NumberToRowColumn(c);
	cout << endl;

	for (int r = 0; r < rows; ++r)
	{
		//Output header column
		ConsoleColorer::SetConsoleColor(Color::white);
		cout << NumberToRowColumn(r) << ' ';
		
		//Output grid
		for (int c = 0; c < columns; ++c)
		{ 
			ConsoleColorer::SetConsoleColor(nodes[r*columns + c].GetColor());
			cout << nodes[r*columns + c].GetDisplayChar();
		}
		cout << endl;
	}
}

void GridGraph::ResetForSearch()
{
	for (int i = 0; i < nodes.size(); ++i)
	{
		nodes[i].visited = false;
		nodes[i].pushed = false;
		nodes[i].visitedFrom = nullptr;
		nodes[i].d = INT_MAX;
	}
}

void GridGraph::DepthFirstSearch(Node* startPoint, string target)
{
	if (!startPoint)
		return;
	if (startPoint->name == target)
		return;

	ResetForSearch();

	stack<Node*> nodesToCheck;
	nodesToCheck.push(startPoint);

	Node* currentNode;
	while (!nodesToCheck.empty())
	{
		currentNode = nodesToCheck.top();
		nodesToCheck.pop();
		if (currentNode->visited)
			continue;

		cout << "Checking node " << currentNode->name << endl;
		currentNode->visited = true;

		if (currentNode->name == target)
		{
			cout << target << " found!" << endl;
			return;
		}

		for (Edge e : currentNode->neighbors)//check neighbors
		{
			if (e.neighbor->pushed == false)
			{
				nodesToCheck.push(e.neighbor);
				e.neighbor->visitedFrom = currentNode;
				e.neighbor->pushed = true;
			}
		}
	}
}

void GridGraph::BreadthFirstSearch(Node* startPoint, string target)
{
	if (!startPoint)
		return;
	if (startPoint->name == target)
		return;

	ResetForSearch();

	queue<Node*> nodesToCheck;
	nodesToCheck.push(startPoint);

	Node* currentNode;
	while (!nodesToCheck.empty())
	{
		currentNode = nodesToCheck.front();
		nodesToCheck.pop();
		if (currentNode->visited)
			continue;

		cout << "Checking node " << currentNode->name << endl;
		currentNode->visited = true;
		if (currentNode->name == target)
		{
			cout << target << " found!" << endl;
			return;
		}

		for (Edge e : currentNode->neighbors)//check neighbors
			if (e.neighbor->pushed == false)
			{
				nodesToCheck.push(e.neighbor);
				e.neighbor->visitedFrom = currentNode;	
				e.neighbor->pushed = true;
			}
	}
}

void GridGraph::PrintPath(Node* startNode, Node* endNode)
{
	Node* temp = endNode;
	string path = "";
	while (temp != startNode)
	{
		path = "From " + temp->visitedFrom->name +
			" go to " + temp->name + "\n" + path;
		temp = temp->visitedFrom;
		temp->ChangeColor(Color::yellow);
	}
	cout << path;
}

//Given a number from 0-62, returns the character
	//we will use in ASCII for that number, from 0-9, A-Z, a-z
	//This is for nothing more than displaying the header row/column
	//and making it easy to display, format, and choose a grid location.
char GridGraph::NumberToRowColumn(int i) const
{
	if (i <= 9)
		i += 48;
	else if (i <= 35)
		i = 65 + (i - 10);
	else
		i = 97 + (i - 36);
	return (char)i;
}

//Given a row and column (like A1 or 6z)
//returns the index of that graph node in the vector<Node> nodes 
//This is just some ASCII chart conversion (skipping punctuation marks)
//65 = 'A' in ASCII, 48 = '0', and 97 = 'a'
int GridGraph::RowColToIndex(char row, char column)
{
	int r = row;
	if (row <= '9')
		r -= 48;
	else if (row <= 'Z')
		r = -65 + (r + 10);
	else
		r = -97 + (r + 36);

	int c = column;
	if (c <= '9')
		c -= 48;
	else if (c <= 'Z')
		c = -65 + (c + 10);
	else
		c = -97 + (c + 36);

	return r * columns + c;
}
 
void GridGraph::ShowNeighbors(char row, char column)
{
	int index = RowColToIndex(row, column);
	if (!isValidIndex(index))
		return; 
	
	nodes[index].ChangeColor(Color::yellow);
	for (int i = 0; i < nodes[index].neighbors.size(); ++i)
		nodes[index].neighbors[i].neighbor->ChangeColor(Color::magenta);
	
	//Or alternatively (less typing):
	//nodes[index].ChangeColor(Color::yellow);
	//for (Edge& e : nodes[index].neighbors)//range-based for loop
	//	e.neighbor->ChangeColor(Color::magenta);
}

void GridGraph::RadialBrush(char row, char column, int radius)
{
	//nodes[index] is the graph node the user chose in main().
	//Refer to ShowNeighbors() above to see how to color a node or visit its neighbors
	int index = RowColToIndex(row, column);
	if (!isValidIndex(index))
		return;

	// base case
	if (radius == 0)
		return;
	//Up
	nodes[RowColToIndex(row, column)].ChangeColor(Color::black);
	RadialBrush(row + 1, column, radius - 1);
	//Down
	nodes[RowColToIndex(row, column)].ChangeColor(Color::black);
	RadialBrush(row - 1, column, radius - 1);
	//Left
	nodes[RowColToIndex(row, column)].ChangeColor(Color::black);
	RadialBrush(row, column + 1, radius - 1);
	// Right
	nodes[RowColToIndex(row, column)].ChangeColor(Color::black);
	RadialBrush(row, column - 1, radius - 1);



} 

void GridGraph::PaintFill(char row, char column, Color color)
{
	//nodes[index] is the graph node the user chose in main().
	//Refer to ShowNeighbors() above to see how to color a node or visit its neighbors
	int index = RowColToIndex(row, column);
	if (!isValidIndex(index))
		return;

	//Base Case
	if (nodes[RowColToIndex(row + 1, column)].GetColor() == color)
		return;
	if (nodes[RowColToIndex(row - 1, column)].GetColor() == color)
		return;
	if (nodes[RowColToIndex(row, column + 1)].GetColor() == color)
		return;
	if (nodes[RowColToIndex(row, column - 1)].GetColor() == color)
		return;

	nodes[RowColToIndex(row, column)].ChangeColor(color);
	PaintFill(row + 1, column, color);
	nodes[RowColToIndex(row, column)].ChangeColor(color);
	PaintFill(row - 1, column, color);
	nodes[RowColToIndex(row, column)].ChangeColor(color);
	PaintFill(row, column + 1, color);
	nodes[RowColToIndex(row, column)].ChangeColor(color);
	PaintFill(row, column - 1, color);

}

void GridGraph::UniformCostSearch(char sR, char sC, char eR, char eC)
{
	//nodes[startIndex] is the start point the user chose in main().
	//nodes[endIndex] is the end point the user chose in main().
	//Refer to ShowNeighbors() above to see how to color a node or visit its neighbors
	int startIndex = RowColToIndex(sR, sC);
	int endIndex = RowColToIndex(eR, eC);

	if (!isValidIndex(startIndex) || !isValidIndex(endIndex))
		return; 

	ResetForSearch();
	nodes[startIndex].d = 0;
	vector<Node*> unvistited;
	unvistited.emplace_back(&nodes[startIndex]);
	Node* current = nullptr;

	while (unvistited.size() != 0)
	{
		int currentIndex = 0;
		Node* temp = &nodes[endIndex];
		for (int i = 0; i < unvistited.size(); ++i)
		{
			if (temp->d >= unvistited[i]->d)
			{
				temp = unvistited[i];
				currentIndex = i;
			}
				
		}
		current = temp;

		if (current == &nodes[endIndex])
		{
			break;
		}

		for (int i = 0; i < current->neighbors.size(); ++i)
		{
			if (current->neighbors[i].cost < INT_MAX)
			{
				int g = current->d + current->neighbors[i].cost;
				if (g < current->neighbors[i].neighbor->d)
				{
					current->neighbors[i].neighbor->d = g;
					current->neighbors[i].neighbor->visitedFrom = current;
					unvistited.emplace_back(current->neighbors[i].neighbor);
					cout << "This is a test " << endl;
				}
			}
		}
		current->visited = true;
		unvistited.erase(unvistited.begin() + currentIndex);
	}
	
}

