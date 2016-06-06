//Zelarous

#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

void createMaze(char maze[][200], int &rows, int &columns, int cheeseRows[], int cheeseColumns[], int &totalCheese, int &mouseStartRow, int &mouseStartColumn);
void outputMaze(char maze[][200], int rows, int columns);
void mouse(char maze[][200], int &rows, int &columns, int cheeseRows[], int cheeseColumns[], int &totalCheese, int &mouseStartRow, int &mouseStartColumn);
bool moveUp(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn);
bool moveDown(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn);
bool moveRight(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn);
bool moveLeft(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn);
bool checkForDeadEnd(char maze[][200], int currentRow, int currentColumn);
void move(char maze[][200], int &currentRow, int &currentColumn);
int foundCheese(char maze[][200], int cheeseRows[],int cheeseColumns[], int totalCheese);
int main()
{
	int rows;
	int columns;
	int totalCheese, mouseStartRow, mouseStartColumn;
	int cheeseFoundByMouse = 0;

	char maze[200][200];
	int cheeseRows[200];
	int cheeseColumns[200];

	createMaze(maze, rows, columns, cheeseRows, cheeseColumns, totalCheese, mouseStartRow, mouseStartColumn);
	outputMaze(maze, rows, columns);	
	//this is a marker for the original starting point of the mouse
	maze[mouseStartRow][mouseStartColumn] = 'o';
	mouse(maze, rows, columns, cheeseRows, cheeseColumns, totalCheese, mouseStartRow, mouseStartColumn);
	cout << endl << endl << endl;
	outputMaze(maze, rows, columns);
	cheeseFoundByMouse = foundCheese(maze, cheeseRows, cheeseColumns, totalCheese);
	cout << endl << cheeseFoundByMouse << " out of " << totalCheese << " pieces of cheese were found. \n\n";

	system("pause");
	return 0;
}

void createMaze(char maze[][200], int &rows, int &columns, int cheeseRows[], int cheeseColumns[], int &totalCheese, int &mouseStartRow, int &mouseStartColumn){
	int count = 0;

	ifstream inputFile("Maze.txt");	

	//reads rows and columns
	inputFile >> rows >> columns;
	
	//reads in maze
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			inputFile >> maze[i][j];
		}
	}
	
	inputFile >> mouseStartRow >> mouseStartColumn;
	inputFile >> totalCheese;

	for(int i = 0; i < totalCheese; i++){
		inputFile >> cheeseRows[i];
		inputFile >> cheeseColumns[i];
	}

	inputFile.close();	
}

void outputMaze(char maze[][200], int rows, int columns){

	//writes out the maze
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			cout << maze[i][j];
		}
		cout << endl;
	}

}

void mouse(char maze[][200], int &rows, int &columns, int cheeseRows[], int cheeseColumns[], int &totalCheese, int &mouseStartRow, int &mouseStartColumn){

	stack<int> theMouseRow;
	stack<int> theMouseColumn;

	int mouseMoveRow = mouseStartRow;
	int mouseMoveColumn = mouseStartColumn;
	int cheeseFound = 0;

	//push starting position onto the row and column stack
	theMouseRow.push(mouseMoveRow);
	theMouseColumn.push(mouseMoveColumn);
	
	//while the maze can go up it will
	
	move(maze, mouseMoveRow, mouseMoveColumn);

	//attempt to make a loop that will start with up, i want the mouse to move up until it hits a dead end

}

bool checkForAlternateRoutes(char maze[][200], int currentRow, int currentColumn){
	
	int totalRoutes = 0;

	//this is just a straight path upwards or downwards
	if((maze[currentRow + 1][currentColumn] != '+' && maze[currentRow - 1][currentColumn] != '+')  && 
		(maze[currentRow][currentColumn + 1] == '+' && maze[currentRow][currentColumn - 1] == '+'))
			return false;

	//this is a straight path going from left to right
	if((maze[currentRow][currentColumn + 1] != '+' && maze[currentRow][currentColumn - 1] != '+') &&
		(maze[currentRow + 1][currentColumn] == '+' && maze[currentRow - 1][currentColumn] == '+'))
			return false;

	if(maze[currentRow + 1][currentColumn] != '+')
		totalRoutes++;

	if(maze[currentRow - 1][currentColumn] != '+')
		totalRoutes++;

	if(maze[currentRow][currentColumn + 1] != '+')
		totalRoutes++;

	if(maze[currentRow][currentColumn + 1] != '+')
		totalRoutes++;

	
	//we have found either an edge or a crossroad (2-4 directions)
	if(totalRoutes > 1)
		return true;

	else
		return false;
}

bool checkForDeadEnd(char maze[][200], int currentRow, int currentColumn){

	int totalRoutes = 0;

	if(maze[currentRow + 1][currentColumn] == '.')
		totalRoutes++;

	if(maze[currentRow - 1][currentColumn] == '.')
		totalRoutes++;

	if(maze[currentRow][currentColumn + 1] == '.')
		totalRoutes++;

	if(maze[currentRow][currentColumn + 1 == '.'])
		totalRoutes++;

	//if the mouse only has 1 route (or less) to choose from
	if(totalRoutes <= 1){
		return true;
	}

	else 
		return false;
		
}

bool moveUp(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn){

	if(maze[currentRow - 1][currentColumn] == '.'){
		currentRow--;
		
		if(checkForAlternateRoutes(maze, currentRow, currentColumn)){
			maze[currentRow][currentColumn] = 'c';
		}
		else
			maze[currentRow][currentColumn] = 'd';

		mouseRow.push(currentRow);
		return true;
	}

	else
		return false;
}

bool moveRight(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn){

	if(maze[currentRow][currentColumn + 1] == '.'){
		currentColumn++;
		
		//this will mark all cross roads (annywhere with multiple paths including corners)
		if(checkForAlternateRoutes(maze, currentRow, currentColumn)){
			maze[currentRow][currentColumn] = 'c';
		}
		//a marker that marks where the mouse has been
		else
			maze[currentRow][currentColumn] = 'd';

		mouseColumn.push(currentColumn);
		cout << mouseColumn.top();
		return true;
	}

	else
		return false;
}

bool moveLeft(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn){

	if(maze[currentRow][currentColumn - 1] == '.'){
		currentColumn--;

		if(checkForAlternateRoutes(maze, currentRow, currentColumn)){
			maze[currentRow][currentColumn] = 'c';
		}
		//a marker that marks where the mouse has been
		else
			maze[currentRow][currentColumn] = 'd';

		mouseColumn.push(currentColumn);
		return true;
	}

	else
		return false;
}

bool moveDown(char maze[][200], int &currentRow, int &currentColumn, stack<int> &mouseRow, stack<int> &mouseColumn){

	if(maze[currentRow + 1][currentColumn] == '.'){
		currentRow++;
		
		//this will mark all cross roads (annywhere with multiple paths including corners)
		if(checkForAlternateRoutes(maze, currentRow, currentColumn)){
			maze[currentRow][currentColumn] = 'c';
		}
		//a marker that marks where the mouse has been
		else
			maze[currentRow][currentColumn] = 'd';

		mouseRow.push(currentRow);
		mouseRow.top();
		return true;
	}

	else 
		return false;
}

void move(char maze[][200], int &currentRow, int &currentColumn){
	cout << endl << endl << endl;
	outputMaze(maze, 5, 9);

	int originalRow = currentRow;
	int originalColumn = currentColumn;
	stack<int> mouseRow;
	stack<int> mouseColumn;

	//if the mouse is standing in the crossroads, push c onto the stack ( though sometimes c will just mean the mouse is travelling on the outside where there is only path and no walls)
	if(maze[currentRow][currentColumn] == 'c'){
		mouseRow.push(currentRow);
		mouseColumn.push(currentColumn);
	}

	//if the mouse is standing at the starting spot (original), push o onto the stack
	if(maze[currentRow][currentColumn] == 'o'){
		mouseRow.push(currentRow);
		mouseColumn.push(currentColumn);
	}

	while(moveUp(maze, currentRow, currentColumn, mouseRow, mouseColumn)){}

	if(currentRow != originalRow || currentColumn != originalColumn){
		
		while(maze[mouseRow.top()][currentColumn] != 'c' && maze[mouseRow.top()][currentColumn] != 'o'){
			mouseRow.pop();
			currentRow = mouseRow.top();
		}

		move(maze, currentRow, currentColumn);

		currentRow = originalRow;
		currentColumn = originalColumn;
	}
	

	while(moveRight(maze, currentRow, currentColumn, mouseRow, mouseColumn)){}
	
	if(currentRow != originalRow || currentColumn != originalColumn){
	
		while(maze[currentRow][mouseColumn.top()] != 'c' && maze[currentRow][mouseColumn.top()] != 'o'){
			cout << mouseColumn.top() << endl;
			mouseColumn.pop();
			currentColumn = mouseColumn.top();
		}
	
		move(maze, currentRow, currentColumn);
	
		currentRow = originalRow;
		currentColumn = originalColumn;
	}

	while(moveLeft(maze, currentRow, currentColumn, mouseRow, mouseColumn)){}

	if(currentRow != originalRow || currentColumn != originalColumn){

		
		while(maze[currentRow][mouseColumn.top()] != 'c' && maze[currentRow][mouseColumn.top()] != 'o'){
			mouseColumn.pop();
			currentColumn = mouseColumn.top();
		}
	

		move(maze, currentRow, currentColumn);
		
		currentRow = originalRow;
		currentColumn = originalColumn;
	}

	while(moveDown(maze, currentRow, currentColumn, mouseRow, mouseColumn)){}
	
	if(currentRow != originalRow || currentColumn != originalColumn){
	
		while(maze[mouseRow.top()][currentColumn] != 'c' && maze[mouseRow.top()][currentColumn] != 'o'){			
			mouseRow.pop();
			currentRow = mouseRow.top();
		}
		
		move(maze, currentRow, currentColumn);

		currentRow = originalRow;
		currentColumn = originalColumn;
	}
}

int foundCheese(char maze[][200], int cheeseRows[], int cheeseColumns[], int totalCheese){
	
	int cheeseFound = 0;
	for(int i = 0; i < totalCheese; i++){
		if(maze[cheeseRows[i]][cheeseColumns[i]] == '.' || maze[cheeseRows[i]][cheeseColumns[i]] != '+'){
			cheeseFound++;
		}
	}
	return cheeseFound;
}
