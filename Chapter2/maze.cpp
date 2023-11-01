/**
 * @file maze.cpp
 * @brief A program that solves a maze using depth-first search, breadth-first search, and A*.
 * @details This program uses the generic_search.h header file to solve a maze using depth-first search, breadth-first search, and A*.
 * @copyright Copyright 2023 Kyungwon Chun
 * 
 * @license Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "generic_search.h"

enum class Cell { EMPTY, BLOCKED, START, GOAL, PATH };

/**
 * @brief A struct representing a location in a maze.
 * 
 */
struct MazeLocation {
    int row, column;

    /**
     * @brief Compares two MazeLocation objects.
     * 
     * @param other The other MazeLocation object to compare to.
     * @return true if this MazeLocation is less than the other MazeLocation, false otherwise.
     */
    bool operator<(const MazeLocation& other) const {
        return std::tie(row, column) < std::tie(other.row, other.column);
    }
};

/**
 * @brief A class representing a maze.
 * 
 */
class Maze {
public:
    /**
     * @brief Construct a new Maze object
     * 
     * @param rows The number of rows in the maze.
     * @param columns The number of columns in the maze.
     * @param sparseness The sparseness of the maze.
     * @param start The starting location of the maze.
     * @param goal The goal location of the maze.
     */
    Maze(int rows = 10, int columns = 10, float sparseness = 0.2, MazeLocation start = {0, 0}, MazeLocation goal = {9, 9})
        : _rows(rows), _columns(columns), _start(start), _goal(goal) {
        // fill the grid with empty cells
        _grid = std::vector<std::vector<Cell>>(rows, std::vector<Cell>(columns, Cell::EMPTY));
        // populate the grid with blocked cells
        _randomly_fill(rows, columns, sparseness);
        // fill the start and goal locations in
        _grid[start.row][start.column] = Cell::START;
        _grid[goal.row][goal.column] = Cell::GOAL;
    }

    /**
     * @brief Check if the given location is the goal location.
     * 
     * @param ml The location to check.
     * @return true if the location is the goal location, false otherwise.
     */
    bool goal_test(const MazeLocation& ml) const {
        return ml.row == _goal.row && ml.column == _goal.column;
    }

    /**
     * @brief Get the list of possible s.cppessor locations from the given location.
     * 
     * @param ml The location to get s.cppessors from.
     * @return A vector of possible s.cppessor locations.
     */
    std::vector<MazeLocation> successors(const MazeLocation& ml) const {
        std::vector<MazeLocation> locations;
        if (ml.row + 1 < _rows && _grid[ml.row + 1][ml.column] != Cell::BLOCKED) {
            locations.push_back({ml.row + 1, ml.column});
        }
        if (ml.row - 1 >= 0 && _grid[ml.row - 1][ml.column] != Cell::BLOCKED) {
            locations.push_back({ml.row - 1, ml.column});
        }
        if (ml.column + 1 < _columns && _grid[ml.row][ml.column + 1] != Cell::BLOCKED) {
            locations.push_back({ml.row, ml.column + 1});
        }
        if (ml.column - 1 >= 0 && _grid[ml.row][ml.column - 1] != Cell::BLOCKED) {
            locations.push_back({ml.row, ml.column - 1});
        }
        return locations;
    }

    /**
     * @brief Mark the given path in the maze.
     * 
     * @param path The path to mark.
     */
    void mark(const std::vector<MazeLocation>& path) {
        for (auto maze_location : path) {
            _grid[maze_location.row][maze_location.column] = Cell::PATH;
        }
        _grid[_start.row][_start.column] = Cell::START;
        _grid[_goal.row][_goal.column] = Cell::GOAL;
    }

    /**
     * @brief Clear the given path in the maze.
     * 
     * @param path The path to clear.
     */
    void clear(const std::vector<MazeLocation>& path) {
        for (auto maze_location : path) {
            _grid[maze_location.row][maze_location.column] = Cell::EMPTY;
        }
        _grid[_start.row][_start.column] = Cell::START;
        _grid[_goal.row][_goal.column] = Cell::GOAL;
    }

    /**
     * @brief Overload the << operator to print the maze.
     * 
     * @param os The output stream.
     * @param maze The maze to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Maze& maze) {
        std::string output;
        for (auto row : maze._grid) {
            for (auto cell : row) {
                switch (cell) {
                    case Cell::EMPTY:
                        output += " ";
                        break;
                    case Cell::BLOCKED:
                        output += "X";
                        break;
                    case Cell::START:
                        output += "S";
                        break;
                    case Cell::GOAL:
                        output += "G";
                        break;
                    case Cell::PATH:
                        output += "*";
                        break;
                }
            }
            output += "\n";
        }
        os << output;
        return os;
    }

    /**
     * @brief Get the start location of the maze.
     * 
     * @return MazeLocation The start location of the maze.
     */
    MazeLocation start() const { return _start; }

    /**
     * @brief Get the goal location of the maze.
     * 
     * @return MazeLocation The goal location of the maze.
     */
    MazeLocation goal() const { return _goal; }

private:
    int _rows, _columns;
    MazeLocation _start, _goal;
    std::vector<std::vector<Cell>> _grid;

    /**
     * @brief Fill the grid with blocked cells randomly.
     * 
     * @param rows The number of rows in the maze.
     * @param columns The number of columns in the maze.
     * @param sparseness The sparseness of the maze.
     */
    void _randomly_fill(int rows, int columns, float sparseness) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1.0);
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                if (dis(gen) < sparseness) {
                    _grid[row][column] = Cell::BLOCKED;
                }
            }
        }
    }
};

/**
 * Returns a lambda function that calculates the Euclidean distance between a given MazeLocation and a goal MazeLocation.
 * 
 * @param goal The goal MazeLocation to calculate the distance to.
 * @return A lambda function that takes a MazeLocation as input and returns the Euclidean distance to the goal MazeLocation.
 */
auto euclidean_distance(MazeLocation goal) {
    return [goal](MazeLocation ml) {
        int xdist = ml.column - goal.column;
        int ydist = ml.row - goal.row;
        return std::sqrt(xdist * xdist + ydist * ydist);
    };
}

/**
 * Calculates the Manhattan distance between the current location and the given goal location.
 * 
 * @param goal The goal location to calculate the distance to.
 * @return The Manhattan distance between the current location and the goal location.
 */
auto manhattan_distance(MazeLocation goal) {
    return [goal](MazeLocation ml) {
        int xdist = std::abs(ml.column - goal.column);
        int ydist = std::abs(ml.row - goal.row);
        return xdist + ydist;
    };
}

/**
 * @brief The main function that tests the DFS, BFS, and A* algorithms on a maze.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    Maze m;
    std::cout << m;

    // Test DFS
    auto solution1 = dfs<MazeLocation>(m.start(), 
        std::bind_front(&Maze::goal_test, &m), 
        std::bind_front(&Maze::successors, &m));
    if (!solution1) {
        std::cout << "No solution found using depth-first search!\n";
    } else {
        auto path1 = node_to_path(solution1);
        m.mark(path1);
        std::cout << m;
        m.clear(path1);
    }

    // Test BFS
    auto solution2 = bfs<MazeLocation>(m.start(), 
        std::bind_front(&Maze::goal_test, &m),
        std::bind_front(&Maze::successors, &m));
    if (!solution2) {
        std::cout << "No solution found using breadth-first search!\n";
    } else {
        auto path2 = node_to_path(solution2);
        m.mark(path2);
        std::cout << m;
        m.clear(path2);
    }

    // Test A*
    auto distance = manhattan_distance(m.goal());
    auto solution3 = astar<MazeLocation>(m.start(), 
        std::bind_front(&Maze::goal_test, &m),
        std::bind_front(&Maze::successors, &m),
        distance);
    if (!solution3) {
        std::cout << "No solution found using A*!\n";
    } else {
        auto path3 = node_to_path(solution3);
        m.mark(path3);
        std::cout << m;
    }

    return EXIT_SUCCESS;
}