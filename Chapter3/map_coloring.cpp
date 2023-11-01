/**
 * @file map_coloring.cpp
 * @brief Map coloring problem
 * @details The map coloring problem is to assign colors to each region of a map such that no neighboring regions have the same color. This is an example of a constraint satisfaction problem.
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
 * @brief Map coloring constraint
 * @details The map coloring constraint is that two regions with a shared border cannot have the same color.
 */
class MapColoringConstraint : public Constraint<std::string, std::string> {
public:
    std::string place1;
    std::string place2;

    /**
     * @brief Construct a new Map Coloring Constraint object
     * @details The map coloring constraint is that two regions with a shared border cannot have the same color.
     * @param place1 First region
     * @param place2 Second region
     */
    MapColoringConstraint(const std::string& place1, const std::string& place2) : Constraint({place1, place2}), place1(place1), place2(place2) {}

    /**
     * @brief Check if the constraint is satisfied
     * @details A constraint is satisfied if it doesn't violate any of the constraints. In other words, if it doesn't violate any of the constraints, it is satisfied.
     * @param assignment A map of variables to their assigned values
     * @return true If the constraint is satisfied
     */
    bool satisfied(std::unordered_map<std::string, std::string>& assignment) override {
        if (assignment.find(place1) == assignment.end() || assignment.find(place2) == assignment.end()) {
            return true;
        }
        return assignment[place1] != assignment[place2];
    }
};

/**
 * @brief Main function
 * @details This is the main function.
 * 
 * @param argc Number of command-line arguments
 * @param argv Command-line arguments
 * @return EXIT_SUCCESS
 */
int main(int argc, char* argv[]) {
    std::vector<std::string> variables = {"Western Australia", "Northern Territory", "South Australia", "Queensland", "New South Wales", "Victoria", "Tasmania"};
    std::unordered_map<std::string, std::vector<std::string>> domains;

    for (const auto& variable : variables) {
        domains[variable] = {"red", "green", "blue"};
    }

    CSP<std::string, std::string> csp(variables, domains);
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Western Australia", "Northern Territory"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Western Australia", "South Australia"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("South Australia", "Northern Territory"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Queensland", "Northern Territory"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Queensland", "South Australia"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Queensland", "New South Wales"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("New South Wales", "South Australia"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Victoria", "South Australia"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Victoria", "New South Wales"));
    csp.add_constraint(std::make_shared<MapColoringConstraint>("Victoria", "Tasmania"));
    std::unordered_map<std::string, std::string> solution = csp.backtracking_search();
    
    if (solution.empty()) {
        std::cout << "No solution found!" << std::endl;
    }
    else {
        for (const auto& [variable, value] : solution) {
            std::cout << variable << ": " << value << std::endl;
        }
    }
    
    return EXIT_SUCCESS;
}