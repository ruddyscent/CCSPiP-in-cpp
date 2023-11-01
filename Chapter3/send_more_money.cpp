/**
 * @file send_more_money.cpp
 * @brief Send More Money problem
 * @details This is a Send More Money problem. The goal is to assign digits to the letters S, E, N, D, M, O, R, Y such that the sum of the values assigned to the variables S, E, N, D, M, O, R, Y should add up to the value assigned to the variables M, O, N, E, Y. The solution is unique.
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
#include <set>

#include "csp.h"

/**
 * @brief SendMoreMoneyConstraint is a class that represents a constraint for the Send More Money problem.
 * 
 * This class inherits from the Constraint class and overrides the satisfied method to check if the current
 * assignment of variables satisfies the constraint. The constraint is that the sum of the values assigned to
 * the variables S, E, N, D, M, O, R, Y should add up to the value assigned to the variables M, O, N, E, Y.
 * 
 * @tparam std::string The type of the variables in the constraint.
 * @tparam int The type of the domain of the variables in the constraint.
 */
class SendMoreMoneyConstraint : public Constraint<std::string, int> {
public:

    /**
     * @brief Constructs a new SendMoreMoneyConstraint object.
     * 
     * @param letters A vector of strings representing the variables in the constraint.
     */
    SendMoreMoneyConstraint(const std::vector<std::string>& letters) : Constraint(letters) {
        _letters = letters;
    }

    /**
     * @brief Checks if the current assignment of variables satisfies the constraint.
     * 
     * @param assignment An unordered map representing the current assignment of variables.
     * @return true If the current assignment satisfies the constraint.
     * @return false If the current assignment does not satisfy the constraint.
     */
    bool satisfied(std::unordered_map<std::string, int>& assignment) override {
        // if there are duplicate values then it's not a solution
        std::set<int> values;
        std::transform(assignment.begin(), assignment.end(), std::inserter(values, values.begin()), [](const auto& a) { return a.second; });
        if (values.size() < assignment.size()) {
            return false;
        }
        // if all variables have been assigned, check if it adds correctly
        if (assignment.size() == _letters.size()) {
            int s = assignment["S"];
            int e = assignment["E"];
            int n = assignment["N"];
            int d = assignment["D"];
            int m = assignment["M"];
            int o = assignment["O"];
            int r = assignment["R"];
            int y = assignment["Y"];
            int send = s * 1000 + e * 100 + n * 10 + d;
            int more = m * 1000 + o * 100 + r * 10 + e;
            int money = m * 10000 + o * 1000 + n * 100 + e * 10 + y;
            return send + more == money;
        }
        return true; // no conflict
    }
    
private:
    std::vector<std::string> _letters;
};

/**
 * @brief The main function
 * 
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    std::vector<std::string> letters = {"S", "E", "N", "D", "M", "O", "R", "Y"};
    std::unordered_map<std::string, std::vector<int>> possible_digits;
    
    for (const auto& letter : letters) {
        possible_digits[letter] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    }
    
    possible_digits["M"] = {1}; // so we don't get answers starting with a 0
    CSP<std::string, int> csp(letters, possible_digits);
    csp.add_constraint(std::make_shared<SendMoreMoneyConstraint>(letters));
    std::unordered_map<std::string, int> solution = csp.backtracking_search();
    
    if (solution.empty()) {
        std::cout << "No solution found!" << std::endl;
    }
    else {
        for (const auto& [letter, digit] : solution) {
            std::cout << letter << ": " << digit << std::endl;
        }
    }

    return EXIT_SUCCESS;
}