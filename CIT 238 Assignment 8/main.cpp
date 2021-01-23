#include <iostream>
#include <time.h>

#include "GridGraph.h"

using namespace std;

//Simple platform-independent way to clear the console
void ClearScreen()
{
	for (int i = 0; i < 30; ++i)
		cout << "\n";
}

Color MenuChoiceToColor(int choice)
{
	switch (choice)
	{
	case 1:
		return Color::green;
	case 2:
		return Color::yellow;//Color::blue is too dark for me.
	case 3:
		return Color::blue;
	case 4:
		return Color::red;
	case 5:
		return Color::black;
	}
	return Color::green;//default color if invalid
}

int main()
{
	srand((unsigned int)time(0));

	GridGraph grid(20, 62);
	grid.Display();

	char response = ' ';
	while (response != '5')
	{
		ConsoleColorer::SetConsoleColor(Color::white);
		cout << "1. Radial Brush Tool\n"
			<< "2. Paint Fill Tool\n"
			<< "3. Uniform Cost Search Tool\n"
			<< "4. Check the neighbors of a node\n"
			<< "5. Exit\n"
			<< "Choose an option: ";
		cin >> response;
		switch (response)
		{
		case '1'://Radial Brush Algorithm
		{
			char row = ' ', column = ' ';
			int radius = 0;
			cout << "Enter a row, column, and radius (Ex. 4a 5): ";
			cin.ignore(100, '\n');
			row = cin.get();
			column = cin.get();
			cin >> radius;
			if (cin.fail() || !grid.isValidIndex(row, column))
			{
				cout << "Invalid Input.";
				break;
			}

/******************************************************************************/
			grid.RadialBrush(row, column, radius);
/******************************************************************************/

			break;
		}
		case '2'://Paint Fill Algorithm
		{
			char row = -1, column = -1;
			cout << "Enter a row and column (Ex. A1 or 6C): ";
			cin.ignore(100, '\n');
			row = cin.get();
			column = cin.get();
			if (cin.fail() || !grid.isValidIndex(row, column))
			{
				cout << "Invalid Input.";
				break;
			}

			int colorChoice = -1;
			cout << "\n1. Green (Grass, Cost: 1)\n"
				<< "2. Yellow (Rock, Cost: 2)\n"
				<< "3. Blue (Water Cost: 3)\n"
				<< "4. Red (Lava, Cost: INF)\n"
				<< "5. Black (Walls, Cost: INF)\n"
				<< "Choose a color: " << endl;
			cin >> colorChoice;
			if (cin.fail() || colorChoice < 1 || colorChoice > 5)
			{
				cout << "Invalid Input.";
				break;
			}

/******************************************************************************/
			grid.PaintFill(row, column, MenuChoiceToColor(colorChoice));
/******************************************************************************/

			break;
		}
		case '3'://Uniform Cost Search (Shortest Path) Algorithm
		{
			char startRow = -1, startColumn = -1;
			char endRow = -1, endColumn = -1;
			cout << "Enter a start row & column and end row & column\n"
				<< "Ex. A1 Z9): ";	
			cin.ignore(100, '\n');
			startRow = cin.get();
			startColumn = cin.get();
			cin.get();//get the space between inputs
			endRow = cin.get();
			endColumn = cin.get();
			if (cin.fail()
				|| !grid.isValidIndex(startRow, startColumn)
				|| !grid.isValidIndex(endRow, endColumn))
			{
				cout << "Invalid Input.";
				break;
			}

			GridGraph temp = grid; 
/******************************************************************************/
			temp.UniformCostSearch(startRow, startColumn, endRow, endColumn);
/******************************************************************************/
			temp.Display(); 
			ConsoleColorer::SetConsoleColor(Color::white);
			cout << "Press any key to return to original map.";
			cin.get();

			break;
		}
		case '4'://Show neighbors of a node
		{
			char row = -1, column = -1;
			cout << "Enter a row and column (Ex. A1 or 6C): ";
			cin.ignore(100, '\n');
			row = cin.get();
			column = cin.get();
			if (cin.fail() || !grid.isValidIndex(row, column))
			{
				cout << "Invalid Input.";
				break;
			}

			GridGraph temp = grid;
			temp.ShowNeighbors(row, column);
			temp.Display();
			ConsoleColorer::SetConsoleColor(Color::white);
			cout << "Press any key to return to original map.";
			cin.get();

			break;
		}
		case '5':
			cout << "Goodbye!\n";
			return 0;

		default:
			cout << "Invalid choice.";
			break;
		}

		cin.clear();
		cin.ignore(100, '\n');
		ClearScreen();
		grid.Display();
	}

	return 0;
}