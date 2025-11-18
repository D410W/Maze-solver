# OBS:

This repository is an implementation from 'https://codeberg.org/selan/Projeto-AMazing'

# Presentation

This is a simple programming project designed to help you get started with maze solving and prepare you to tackle the Snaze programming project.

The objective is to implement a recursive function that receives a maze representation (C++ object), a start position, and an exit position, calculates and returns a path, if one exists, from the start position the the exit.

For that to work, you first have to implement a function to read a maze representation from a ascii file, and store that information in a `Maze` class. This class represents a maze, and provides methods to help the client understand the maze layout. This class should also provide methods that set which cells are part of the solution path to the maze's exit (if such a path exists). This means that the `solve_maze()` function should _"write"_ the `Maze` object, so that it may keep track of the locations visited.

# Coding Your Solution.

The suggestion here is to apply the **backtracking** strategy to systematically explore (visit) the solution space in search of a path that leads from the start to the exit position. Note that the input maze may have loops, which means there might be more than one path that leads to the exit. Your goal here is just to find one path.

The solution strategy suggested here were introduced in previous class and it represents a [**depth-first search**](https://en.wikipedia.org/wiki/Depth-first_search) (DFS) strategy. You may find the slides [**here**](docs/solving_maze.pdf).

For more information on alternative maze-solving algorithms, please visit [this Wikipedia entry](https://en.wikipedia.org/wiki/Maze-solving_algorithm).

# The Code

The code available in this repository is **incomplete**. Your goal is to complete the code, in special the function `solve_maze()`, as discussed in class.

You do not need to submit this code for grading. This assignment is proposed only to offer you an opportunity get involved with maze-solving algorithms, as a way to get you going with the Snaze Programming Project.
