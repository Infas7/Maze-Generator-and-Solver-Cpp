#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <fstream>
#include <stdlib.h>

using namespace std;

//%%%%%%%%%%%%%% Edit this value(default = 21) to generate a differnt size maze. ONLY ENTER AN ODD VALUE. %%%%%%%%%%%%%%%%%%//
#define mazeSize 21 

struct Cell
{
	bool visited;
	bool topWall;
	bool bottomWall;
	bool leftWall;
	bool rightWall;
	char display;
};

// ----------------------------------------------- Function Declarations -----------------------------------------------------//
void mazeInitializer(Cell Level[][mazeSize]);
void clearScreen();
void reDrawMaze(Cell Level[][mazeSize]);
void generateMaze(Cell Level[][mazeSize], int& posX, int& posY, int& goalX, int& goalY);
void saveMazeToFile(Cell Level[][mazeSize]);

// ---------------------------------------------------- Main Function --------------------------------------------------------//
int main() {
	Cell Level[mazeSize][mazeSize];
	int posX = 0, posY = 0, goalX = 0, goalY = 0;
	bool gameOver = false;

	while (!gameOver) {
		cout << "\a\n\nPlease change the \"mazeSize\" value in the source file \n"
				"to generate a different size maze. ONLY USE AN ODD NUMBER.\n"
				"to continue with the default size 21 :\n";
		system("pause");
		system("cls");
		mazeInitializer(Level);
		reDrawMaze(Level);
		generateMaze(Level, posX, posY, goalX, goalY);
		saveMazeToFile(Level);

		char input;
		cout << "Do you want to create a new Maze? (Y)/(N): ";
		cin >> input;

		if ((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
			cout << "Invalid input!" << endl;
		else if ((input == 'n') || (input == 'N')) {
			gameOver = true;
			cout << "\nProgram Ended Successfully!\n\n";
		}
	}

	system("pause");

	return 0;
}

// ----------------------------------------------- Initialize Maze -----------------------------------------------------//
void mazeInitializer(Cell Level[][mazeSize]) {
	for (int i = 0; i < mazeSize; i++) {
		for (int j = 0; j < mazeSize; j++) {
			Level[i][j].display = '1';
			Level[i][j].visited = false;
			Level[i][j].topWall = true;
			Level[i][j].bottomWall = true;
			Level[i][j].leftWall = true;
			Level[i][j].rightWall = true;
		}
	}
	for (int i = 1; i < mazeSize - 1; i++) {
		for (int j = 1; j < mazeSize - 1; j++) {
			//Setting boarder cells;
			Level[1][j].topWall = false;           
			Level[mazeSize - 2][j].bottomWall = false;
			Level[i][1].leftWall = false;
			Level[i][mazeSize - 2].rightWall = false;
		}
	}
}

//------------------------------------------------- Clear the screen --------------------------------------------------------//
void clearScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// ----------------------------------------------- Draw Maze to the console-----------------------------------------------------//
void reDrawMaze(Cell Level[][mazeSize]) {
	for (int i = 0; i < mazeSize; i++) {
		
		for (int j = 0; j < mazeSize; j++) {
			cout <<  Level[i][j].display;
		}
		cout << endl;
	}
}

// ------------------------------------------------- Generate Maze ----------------------------------------------------------//
void generateMaze(Cell Level[][mazeSize], int& posX, int& posY, int& goalX, int& goalY) {
	srand((unsigned)time(NULL));				        					// Pick random start cell
	int random = 0;
	int randX = ((2 * rand()) + 1) % (mazeSize - 1);						// Generate a random odd number between 1 and mazeSize
	int randY = ((2 * rand()) + 1) % (mazeSize - 1);						// Generate a random odd number between 1 and mazeSize
	posX = randX;                       						// Save player's initial X position
	posY = randY;                      						// Save player's initial Y position
	int visitedCells = 1;
	int totalCells = ((mazeSize - 1) / 2) * ((mazeSize - 1) / 2);
	int percentage = 0;
	stack<int> back_trackX, back_trackY; 						// Stack is used to trace the reverse path

	Level[randY][randX].display = 'A';						// Set S as the start cell
	Level[randY][randX].visited = true;						// Set start cell as visited;

	while (visitedCells < totalCells)
	{
		if (((Level[randY - 2][randX].visited == false) && (Level[randY][randX].topWall == true && Level[randY - 2][randX].bottomWall == true)) ||
			((Level[randY + 2][randX].visited == false) && (Level[randY][randX].bottomWall == true && Level[randY + 2][randX].topWall == true)) ||
			((Level[randY][randX - 2].visited == false) && (Level[randY][randX].leftWall == true && Level[randY][randX - 2].rightWall == true)) ||
			((Level[randY][randX + 2].visited == false) && (Level[randY][randX].rightWall == true && Level[randY][randX + 2].leftWall == true)))
		{
			random = (rand() % 4) + 1;		// Pick a random wall 1-4 to knock down

			 // Move up
			if ((random == 1) && (randY > 1)) {
				if (Level[randY - 2][randX].visited == false) {	// If not visited
					Level[randY - 1][randX].display = '0';	// Delete display
					Level[randY - 1][randX].visited = true;	// Mark cell as visited
					Level[randY][randX].topWall = false;	// Knock down wall

					back_trackX.push(randX); 			// Push X for back track
					back_trackY.push(randY);			// Push Y for back track

					randY -= 2;					// Move to next cell
					Level[randY][randX].visited = true;		// Mark cell moved to as visited
					Level[randY][randX].display = '0';		// Update path
					Level[randY][randX].bottomWall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// Move down
			else if ((random == 2) && (randY < mazeSize - 2)) {
				if (Level[randY + 2][randX].visited == false) {	// If not visited
					Level[randY + 1][randX].display = '0';	// Delete display
					Level[randY + 1][randX].visited = true;	// Mark cell as visited
					Level[randY][randX].bottomWall = false;	// Knock down wall

					back_trackX.push(randX); 			// Push X for back track
					back_trackY.push(randY);			// Push Y for back track

					randY += 2;					// Move to next cell
					Level[randY][randX].visited = true;		// Mark cell moved to as visited
					Level[randY][randX].display = '0';		// Update path
					Level[randY][randX].topWall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// Move left
			else if ((random == 3) && (randX > 1)) {
				if (Level[randY][randX - 2].visited == false) {	// If not visited
					Level[randY][randX - 1].display = '0';	// Delete display
					Level[randY][randX - 1].visited = true;	// Mark cell as visited
					Level[randY][randX].leftWall = false;	// Knock down wall

					back_trackX.push(randX); 			// Push X for back track
					back_trackY.push(randY);			// Push Y for back track

					randX -= 2;					// Move to next cell
					Level[randY][randX].visited = true;		// Mark cell moved to as visited
					Level[randY][randX].display = '0';		// Update path
					Level[randY][randX].rightWall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			//Move Right
			else if ((random == 4) && (randX < mazeSize - 2)) {
				if (Level[randY][randX + 2].visited == false) {	// If not visited
					Level[randY][randX + 1].display = '0';	// Delete display
					Level[randY][randX + 1].visited = true;	// Mark cell as visited
					Level[randY][randX].rightWall = false;	// Knock down wall

					back_trackX.push(randX); 			// Push X for back track
					back_trackY.push(randY);			// Push Y for back track

					randX += 2;					// Move to next cell
					Level[randY][randX].visited = true;		// Mark cell moved to as visited
					Level[randY][randX].display = '0';		// Update path
					Level[randY][randX].leftWall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			percentage = (visitedCells * 100 / totalCells * 100) / 100;		// Progress in percentage
			cout << endl << "Generating... " << percentage << "%" << endl;
		}
		else {
			randX = back_trackX.top();
			back_trackX.pop();

			randY = back_trackY.top();
			back_trackY.pop();
		}

		clearScreen();
		reDrawMaze(Level);
	}

	goalX = randX;
	goalY = randY;
	Level[goalY][goalX].display = 'B';
	system("cls");
	clearScreen();
	reDrawMaze(Level);
	cout << endl << "\a	Completed!!!" << endl;
}

// ----------------------------------------------- Save to a file function -----------------------------------------------------//
void saveMazeToFile(Cell Level[][mazeSize]) {
	ofstream output;
	char file[20];
	char input;

	cout << endl << "Do you want to save the Maze? (Y)/(N): ";
	cin >> input;

	if ((input == 'y') || (input == 'Y')) {
		cout << endl << "Enter the file name you want to save with \".txt\" : ";
		cin >> file;

		output.open(file);
		for (int i = 0; i < mazeSize; i++) {
			for (int j = 0; j < mazeSize; j++) {
				output << Level[i][j].display;
			}

			if(i < mazeSize - 1) output << endl;
		}

		cout << "Maze has been sucessfully saved to - " <<  file <<  endl;
		output.close();
	}

}