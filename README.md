# Maze_Generator_and_Solver--Problem_solving_Cpp

### 1.The Maze Puzzle

The Maze puzzle is a popular puzzle game in which the player is required to find a route from the designated starting point to the endpoint of a maze-like puzzle. The Maze is typically rectangular and consists of paths usually denoted by white in which the player can freely travel through, and walls denoted by black which a player cannot move across. The image below shows a typical Maze Puzzle. 


![image](https://user-images.githubusercontent.com/76855463/200381588-00873a88-b9a9-4e97-bc78-5abc51406c46.png)

As can be observed from the image above, a maze puzzle consists of many paths that lead to a dead-end, and one path leading to the goal. There are some extended variants with more than one path leading to the goal as well.

### 2. Generating a puzzle maze

Generating a challenging puzzle maze with a valid solution is a task that is as challenging as solving one. One of the easiest ways to create a puzzle maze is by generating it using a computer with the help of a randomized algorithm. 

For this problem, we will break down the puzzle into “cells” where a single cell represents a single block on the puzzle. A ‘0’ would represent a white block which would be part of a path and 1 would represent a black block which would be a part of a wall. The starting point and the goal must always be on white blocks and must be denoted by the letters “A” and “B” respectively. All horizontal blocks must be space separated. For example, the puzzle in the above image would be represented by a 21x21 grid as follows:

![image](https://user-images.githubusercontent.com/76855463/200384785-088b39b8-01ed-497f-be12-c6fa7ae673f7.png)

Implement an algorithm to create a random square-shaped puzzle of a given size. The algorithm must always create a valid puzzle with one solution. The generated puzzle must be saved to a text file. The implementation will be graded according to the complexity of the puzzle as well as the time complexity of the algorithm.

### 3. Implementing a Maze Puzzle Solver

Implement a separate algorithm to solve the mazes generated and saved as text files in section 2. The algorithm must be completely separate from the generator implemented in part 2 and must not be able to access any variables of the generator. The Solver must incorporate recursion and backtracking. The solution path found by the algorithm must be denoted by replacing the cells with **“#”** symbols and saved to a separate text file. For example, the solution to the puzzle shown above must be denoted as follows:

![image](https://user-images.githubusercontent.com/76855463/200384725-a8281a9f-6633-4d9a-9d7f-1516efbf0d5e.png)



