/**
 * @file graph.cpp
 * @brief The Graph class represents a graph.
 * @details The Graph class represents a graph.
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

#include "graph.h"

/**
 * The main function is the entry point of the program.
 * It returns an integer value indicating the exit status of the program.
 * In this program, it initializes the graph and performs some operations on it.
 * @return An integer value indicating the exit status of the program.
 */
int main() {
    Graph<std::string> city_graph({"Seattle", "San Francisco", "Los Angeles", "Riverside", "Phoenix", "Chicago", "Boston", "New York", "Atlanta", "Miami", "Dallas", "Houston", "Detroit", "Philadelphia", "Washington"});
    city_graph.add_edge_by_vertices("Seattle", "Chicago");
    city_graph.add_edge_by_vertices("Seattle", "San Francisco");
    city_graph.add_edge_by_vertices("San Francisco", "Riverside");
    city_graph.add_edge_by_vertices("San Francisco", "Los Angeles");
    city_graph.add_edge_by_vertices("Los Angeles", "Riverside");
    city_graph.add_edge_by_vertices("Los Angeles", "Phoenix");
    city_graph.add_edge_by_vertices("Riverside", "Phoenix");
    city_graph.add_edge_by_vertices("Riverside", "Chicago");
    city_graph.add_edge_by_vertices("Phoenix", "Dallas");
    city_graph.add_edge_by_vertices("Phoenix", "Houston");
    city_graph.add_edge_by_vertices("Dallas", "Chicago");
    city_graph.add_edge_by_vertices("Dallas", "Atlanta");
    city_graph.add_edge_by_vertices("Dallas", "Houston");
    city_graph.add_edge_by_vertices("Houston", "Atlanta");
    city_graph.add_edge_by_vertices("Houston", "Miami");
    city_graph.add_edge_by_vertices("Atlanta", "Chicago");
    city_graph.add_edge_by_vertices("Atlanta", "Washington");
    city_graph.add_edge_by_vertices("Atlanta", "Miami");
    city_graph.add_edge_by_vertices("Miami", "Washington");
    city_graph.add_edge_by_vertices("Chicago", "Detroit");
    city_graph.add_edge_by_vertices("Detroit", "Boston");
    city_graph.add_edge_by_vertices("Detroit", "Washington");
    city_graph.add_edge_by_vertices("Detroit", "New York");
    city_graph.add_edge_by_vertices("Boston", "New York");
    city_graph.add_edge_by_vertices("New York", "Philadelphia");
    city_graph.add_edge_by_vertices("Philadelphia", "Washington");
    city_graph.print();
    return 0;
}