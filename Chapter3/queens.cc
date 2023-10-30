/**
 * @file queens.cc
 * @brief N-Queens Problem
 * @details This file contains the implementation of the N-Queens problem using constraint satisfaction problem (CSP) framework from Chapter 3. The N-Queens problem is to place N queens on an N x N chessboard such that no two queens are in the same row, column, or diagonal.
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

#include "csp.h"

/**
 * @brief N-Queens Constraint
 * @details This class represents the constraint that no two queens are in the same row, column, or diagonal.
 * @see https://en.wikipedia.org/wiki/Eight_queens_puzzle
 */
class QueensConstraint : public Constraint<int, int> {
public:
    std::vector<int> columns;  // Columns of the chessboard

    /**
     * @brief Construct a new QueensConstraint object
     * @details This class represents the constraint that no two queens are in the same row, column, or diagonal.
     * @param columns Columns of the chessboard
    */
    QueensConstraint(const std::vector<int>& columns) : Constraint(columns), columns(columns) {}

    /**
     * @brief Check if the constraint is satisfied
     * @details A constraint is satisfied if it doesn't violate any of the constraints. In other words, if it doesn't violate any of the constraints, it is satisfied.
     * @param assignment A map of variables to their assigned values
     * @return true If the constraint is satisfied
     */
    bool satisfied(std::unordered_map<int, int>& assignment) override {
        for (const auto& [q1c, q1r] : assignment) {
            for (int q2c = q1c + 1; q2c <= columns.size(); ++q2c) {
                if (assignment.find(q2c) != assignment.end()) {
                    int q2r = assignment[q2c];
                    if (q1r == q2r) {
                        return false;
                    }
                    if (std::abs(q1r - q2r) == std::abs(q1c - q2c)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

/**
 * @brief Main function
 * @details This function is the entrypoint of the program.
 * @param argc The number of command-line arguments
 * @param argv The command-line arguments
 * @return EXIT_SUCCESS if the program exits successfully, EXIT_FAILURE otherwise
 */
int main(int argc, char* argv[]) {
    std::vector<int> columns = {1, 2, 3, 4, 5, 6, 7, 8};
    std::unordered_map<int, std::vector<int>> rows;
    for (const auto& column : columns) {
        rows[column] = {1, 2, 3, 4, 5, 6, 7, 8};
    }
    CSP<int, int> csp(columns, rows);
    csp.add_constraint(std::make_shared<QueensConstraint>(columns));
    std::unordered_map<int, int> solution = csp.backtracking_search();
    if (solution.empty()) {
        std::cout << "No solution found!" << std::endl;
    }
    else {
        std::cout << "{";
        for (int i = 1; i < 8; i++) {
            std::cout << i << ": " << solution[i] << ", ";
        }
        std::cout << 8 << ": " << solution[8] << "}" << std::endl;
    }
    return EXIT_SUCCESS;
}