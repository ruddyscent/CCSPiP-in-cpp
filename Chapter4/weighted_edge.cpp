/**
 * @file weighted_edge.cpp
 * @brief The WeightedEdge class represents a weighted edge in a weighted graph.
 * @details The WeightedEdge class represents a weighted edge in a weighted graph.
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
#include <string>

#include "edge.h"

/**
 * @brief WeightedEdge class represents an edge in a weighted graph.
 * 
 */
class WeightedEdge : public Edge {
public:
    float weight;

    /**
     * @brief Construct a new WeightedEdge object
     * 
     * @param u The source vertex of the edge.
     * @param v The destination vertex of the edge.
     * @param weight The weight of the edge.
     */
    WeightedEdge(int u, int v, float weight) : Edge(u, v), weight(weight) {}

    /**
     * @brief Returns the reversed edge of the current edge.
     * 
     * @return WeightedEdge The reversed edge.
     */
    WeightedEdge reversed() const {
        return WeightedEdge(v, u, weight);
    }

    /**
     * @brief Overloads the less than operator to compare edges based on their weight.
     * 
     * @param other The other edge to compare with.
     * @return true if the weight of the current edge is less than the weight of the other edge.
     * @return false otherwise.
     */
    bool operator<(const WeightedEdge& other) const {
        return weight < other.weight;
    }

    /**
     * @brief Returns a string representation of the edge.
     * 
     * @return std::string The string representation of the edge.
     */
    std::string to_string() const {
        return std::to_string(u) + " " + std::to_string(weight) + "> " + std::to_string(v);
    }
};


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