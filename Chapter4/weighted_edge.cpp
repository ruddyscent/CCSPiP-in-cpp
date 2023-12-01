/**
 * @file weighted_edge.cpp
 * @brief The WeightedEdge class represents a weighted directed edge in a graph.
 * @details The WeightedEdge class represents a weighted directed edge in a graph.
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

#include "weighted_edge.h"

/**
 * @brief The main function creates a WeightedEdge object and prints its string representation and the string representation of its reversed edge.
 * 
 * @param argc The number of command-line arguments provided.
 * @param argv An array of pointers to the arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    WeightedEdge e(1, 2, 0.5);
    std::cout << e.to_string() << std::endl;
    std::cout << e.reversed().to_string() << std::endl;
    return EXIT_SUCCESS;
}
