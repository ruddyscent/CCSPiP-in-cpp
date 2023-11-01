/**
 * @file edge.h
 * @brief The Edge class represents a directed edge in a graph.
 * @details The Edge class represents a directed edge in a graph.
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

// #include <cstdlib>
#include <iostream>
#include <string>

/**
 * @brief The Edge class represents a directed edge in a graph.
 * 
 */
class Edge {
public:
    int u; // the "from" vertex
    int v; // the "to" vertex

    /**
     * @brief Construct a new Edge object.
     * 
     * @param u The "from" vertex.
     * @param v The "to" vertex.
     */
    Edge(int u, int v) : u(u), v(v) {}

    /**
     * @brief Get the reversed edge.
     * 
     * @return Edge The reversed edge.
     */
    Edge reversed() const {
        return Edge(v, u);
    }

    /**
     * @brief Get the string representation of the edge.
     * 
     * @return std::string The string representation of the edge.
     */
    std::string to_string() const {
        return std::to_string(u) + " -> " + std::to_string(v);
    }
};

// /**
//  * The main function of the program.
//  * 
//  * @param argc The number of command-line arguments provided.
//  * @param argv An array of strings containing the command-line arguments.
//  * @return An integer representing the exit status of the program.
//  */
// int main(int argc, char* argv[]) {
//     Edge e(1, 2);
//     std::cout << e.to_string() << std::endl;
//     std::cout << e.reversed().to_string() << std::endl;
//     return EXIT_SUCCESS;
// }