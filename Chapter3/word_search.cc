/**
 * @file word_search.cc
 * @brief Word search problem
 * @details This is a word search problem. The goal is to assign letters to a grid of size 9x9 such that the letters form words in the rows and columns. The words are given in a list. The words can be placed in the grid in any direction (left to right, right to left, top to bottom, bottom to top, and diagonally in all four directions).
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
 */

#include <cstdlib>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "csp.h"

class GridLocation {
public:
    int row;
    int column;

    GridLocation(int row, int column) : row(row), column(column) {}

    bool operator<(const GridLocation& other) const {
        return row < other.row || (row == other.row && column < other.column);
    }
};

using Grid = std::vector<std::vector<char>>;

Grid generate_grid(int rows, int columns) {
    // initialize grid with random letters
    Grid grid(rows, std::vector<char>(columns));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    for (auto& row : grid) {
        std::generate(row.begin(), row.end(), [&]() { return static_cast<char>('A' + dis(gen)); });
    }
    return grid;
}

void display_grid(const Grid& grid) {
    for (const auto& row : grid) {
        for (const auto& letter : row) {
            std::cout << letter;
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<GridLocation>> generate_domain(const std::string& word, const Grid& grid) {
    std::vector<std::vector<GridLocation>> domain;
    int height = grid.size();
    int width = grid[0].size();
    int length = word.length();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::vector<GridLocation> locations;
            std::vector<int> columns(length);
            std::iota(columns.begin(), columns.end(), col);
            std::vector<int> rows(length);
            std::iota(rows.begin(), rows.end(), row);
            if (col + length <= width) {
                // left to right
                std::transform(columns.begin(), columns.end(), std::back_inserter(locations), [&](int c) { return GridLocation(row, c); });
                // diagonal towards bottom right
                if (row + length <= height) {
                    std::transform(rows.begin(), rows.end(), std::back_inserter(locations), [&](int r) { return GridLocation(r, col + (r - row)); });
                }
            }
            if (row + length <= height) {
                // top to bottom
                std::transform(rows.begin(), rows.end(), std::back_inserter(locations), [&](int r) { return GridLocation(r, col); });
                // diagonal towards bottom left
                if (col + 1 - length >= 0) {
                    std::transform(rows.begin(), rows.end(), std::back_inserter(locations), [&](int r) { return GridLocation(r, col - (r - row)); });
                }
            }
            if (!locations.empty()) {
                domain.push_back(locations);
            }
        }
    }
    return domain;
}

class WordSearchConstraint : public Constraint<std::string, std::vector<GridLocation>> {
public:
    std::vector<std::string> words;

    WordSearchConstraint(const std::vector<std::string>& words) : Constraint(words), words(words) {}

    bool satisfied(std::unordered_map<std::string, std::vector<GridLocation>>& assignment) override {
        std::vector<GridLocation> all_locations;
        for (const auto& locs : assignment) {
            all_locations.insert(all_locations.end(), locs.second.begin(), locs.second.end());
        }
        return std::set<GridLocation>(all_locations.begin(), all_locations.end()).size() == all_locations.size();
    }
};

int main(int argc, char* argv[]) {
    Grid grid = generate_grid(9, 9);
    std::vector<std::string> words = {"MATTHEW", "JOE", "MARY", "SARAH", "SALLY"};
    std::unordered_map<std::string, std::vector<std::vector<GridLocation>>> locations;
    for (const auto& word : words) {
        locations[word] = generate_domain(word, grid);
    }

    CSP<std::string, std::vector<GridLocation>> csp(words, locations);
    csp.add_constraint(std::make_shared<WordSearchConstraint>(words));
    auto solution = csp.backtracking_search();
    
    if (solution.empty()) {
        std::cout << "No solution found!" << std::endl;
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        for (const auto& n : solution) {
            auto word = n.first;
            auto grid_locations = n.second;
            // random reverse half the time
            if (dis(gen) < 0.5) {
                std::reverse(grid_locations.begin(), grid_locations.end());
            }
            for (int index = 0; index < word.length(); ++index) {
                int row = grid_locations[index].row;
                int col = grid_locations[index].column;
                grid[row][col] = word[index];
            }
        }
        display_grid(grid);
    }

    return EXIT_SUCCESS;
}