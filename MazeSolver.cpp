#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum Cell { emty = 0, wall, goal, crumb };
char** maze;
int** visited;
int rows, cols;
int startRow;
int startCol;

//--------------------------------- Function for allocating memory in HEAP for maze array ------------------------------------------------//
void allocateMazeArray() {
	maze = new char* [rows];
	
	for (int i = 0; i < cols ; i++) {
		maze[i] = new char [cols];
	}	
}

//------------------------------Function for allocating memory in HEAP for visited cells array ------------------------------------------//
void allocateVisitedArray() {
	visited = new int* [rows];

	for (int i = 0; i < rows; i++) {
		visited[i] = new int[cols];
	}
}

//------------------------------------------- Function for updating visited cells -------------------------------------------------------//
void getVisited()
{
	allocateVisitedArray();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == '1') {
				visited[i][j] = wall;
			}
			else if (maze[i][j] == 'B') {
				visited[i][j] = goal;
			}
			else {
				visited[i][j] = emty;
			}
		}
	}
}


//------------------------------------------------ Function for print visited array-------------------------------------------------------//
void printVisited() {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << visited[i][j];
		}
		cout << endl;
	}
}

//------------------------------------------------ Function for print maze array----------------------------------------------------------//
void printMaze() {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
}

//------------------------------------- Function read from text file and setting up the maze array -----------------------------------//
void getMaze(string mazeFile) {

	fstream file;
	
	string line;

	file.open(mazeFile, ios::in);
	
	
	if (file.is_open()) {
		int countline = 0;
		
		//Counting the lines inside the text file.
		while (!file.eof()) {
			getline(file, line);
			countline++;
		}
			rows = countline;
			cols = countline;
	
			file.clear();
			file.seekg(0, file.beg); //Resetting the pointer to the beginning of the text file

			allocateMazeArray();
		
		//Inserting the characters in the text file into maze array.
		while (!file.eof()) {
			for (int i = 0; i < rows ; i++) {
				getline(file, line);
				for (int j = 0; j < cols ; j++) {
					maze [i][j] =line[j] ;
					if (line[j] == 'A') {
							startRow = i;
							startCol = j;
					}
				}
			}
		}


		 file.close();	
	}

	else {
		cout << "Cannot open the file: " << mazeFile << endl;
		cout << "Make sure the file is added to the solution directory." << endl;
		
	}


}

//--------------------------------------------- Function for udating the visited path -------------------------------------------------------//
void addCrumbs()
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (maze[i][j] != 'A' && visited[i][j] == crumb) {
				maze[i][j] = '#';
			}
		}
	}
}

//--------------------------------------- Recursive depth first search function to find the goal-----------------------------------------------//
bool dfs(int row, int col) {
	int* current = &visited[row][col];

	if (*current == goal) {
		return 1;
	}

	if (*current == emty) {
		*current = wall;

		if (dfs(row, col - 1)) {
			*current = crumb;
			return 1;
		}
		if (dfs(row + 1, col)) {
			*current = crumb;
			return 1;
		}
		if (dfs(row, col + 1)) {
			*current = crumb;
			return 1;
		}
		if (dfs(row - 1, col)) {
			*current = crumb;
			return 1;
		}
	}

	return 0;
}

//--------------------------------------------- Main Function -------------------------------------------------------//
int main() {
	string filename;
	cout << "Enter the file name with \".txt\" : ";
	cin >> filename;
	cout << endl;
	
	getMaze(filename);
	getVisited();

	cout << "%%%%%%%%%%%%%%%%%%%%%% Input Maze %%%%%%%%%%%%%%%%%%%%%%\n\n";
	printMaze();
	cout << endl << endl;
	//printVisited();
	dfs(startRow, startCol);
	addCrumbs();
	cout << "\n\a\tSolved Sucessfully..." << endl;

	
	cout << "\n\n%%%%%%%%%%%%%%%%%%%%%% Solved Maze %%%%%%%%%%%%%%%%%%%%%%\n\n";
	printMaze();
	

	//Delete HEAP arrays.
	for (int i = 0; i < rows; i++) {
		delete[] maze[i];
		delete[] visited[i];
	}
	delete[] maze;
	delete[] visited;
	maze = NULL;
	visited = NULL;

	cout << endl;
	system("pause");
	return 0;
}