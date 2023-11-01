/**
 * @file graph.cpp
 * @brief The Graph class represents a graph data structure.
 * @details The Graph class represents a graph data structure.
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

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "edge.h"

/**
 * @brief A template class representing a graph data structure.
 * 
 * @tparam V The type of the vertices in the graph.
 */
template <typename V>
class Graph {
public:
    /**
     * @brief A vector containing all the vertices in the graph.
     */
    std::vector<V> vertices;

    /**
     * @brief A vector of vectors containing all the edges in the graph.
     */
    std::vector<std::vector<Edge>> edges;

    /**
     * @brief Constructs a new Graph object.
     * 
     * @param vertices A vector containing all the vertices in the graph.
     */
    Graph(const std::vector<V>& vertices) : vertices(vertices) {
        edges.resize(vertices.size());
    }

    /**
     * @brief Returns the number of vertices in the graph.
     * 
     * @return int The number of vertices in the graph.
     */
    int vertex_count() const {
        return vertices.size();
    }

    /**
     * @brief Returns the number of edges in the graph.
     * 
     * @return int The number of edges in the graph.
     */
    int edge_count() const {
        int count = 0;
        for (const auto& edge_list : edges) {
            count += edge_list.size();
        }
        return count;
    }

    /**
     * @brief Adds a new vertex to the graph.
     * 
     * @param vertex The vertex to be added.
     */
    void add_vertex(const V& vertex) {
        vertices.push_back(vertex);
        edges.push_back({});
    }

    /**
     * @brief Adds a new edge to the graph.
     * 
     * @param edge The edge to be added.
     */
    void add_edge(const Edge& edge) {
        edges[edge.u].push_back(edge);
        edges[edge.v].push_back(edge.reversed());
    }

    /**
     * @brief Adds a new edge to the graph by specifying the indices of the vertices.
     * 
     * @param u The index of the first vertex.
     * @param v The index of the second vertex.
     */
    void add_edge_by_indices(int u, int v) {
        Edge edge(u, v);
        add_edge(edge);
    }

    /**
     * @brief Adds a new edge to the graph by specifying the vertices.
     * 
     * @param first The first vertex.
     * @param second The second vertex.
     */
    void add_edge_by_vertices(const V& first, const V& second) {
        int u = std::find(vertices.begin(), vertices.end(), first) - vertices.begin();
        int v = std::find(vertices.begin(), vertices.end(), second) - vertices.begin();
        add_edge_by_indices(u, v);
    }

    /**
     * @brief Returns the vertex at the specified index.
     * 
     * @param index The index of the vertex.
     * @return V The vertex at the specified index.
     */
    V vertex_at(int index) const {
        return vertices[index];
    }

    /**
     * @brief Returns the index of the specified vertex.
     * 
     * @param vertex The vertex whose index is to be returned.
     * @return int The index of the specified vertex.
     */
    int index_of(const V& vertex) const {
        return std::find(vertices.begin(), vertices.end(), vertex) - vertices.begin();
    }

    /**
     * @brief Returns a vector containing all the neighbors of the vertex at the specified index.
     * 
     * @param index The index of the vertex.
     * @return std::vector<V> A vector containing all the neighbors of the vertex at the specified index.
     */
    std::vector<V> neighbors_for_index(int index) const {
        std::vector<V> result;
        for (const Edge& edge : edges[index]) {
            result.push_back(vertex_at(edge.v));
        }
        return result;
    }

    /**
     * @brief Returns a vector containing all the neighbors of the specified vertex.
     * 
     * @param vertex The vertex whose neighbors are to be returned.
     * @return std::vector<V> A vector containing all the neighbors of the specified vertex.
     */
    std::vector<V> neighbors_for_vertex(const V& vertex) const {
        return neighbors_for_index(index_of(vertex));
    }

    /**
     * @brief Returns a vector containing all the edges connected to the vertex at the specified index.
     * 
     * @param index The index of the vertex.
     * @return std::vector<Edge> A vector containing all the edges connected to the vertex at the specified index.
     */
    std::vector<Edge> edges_for_index(int index) const {
        return edges[index];
    }

    /**
     * @brief Returns a vector containing all the edges connected to the specified vertex.
     * 
     * @param vertex The vertex whose edges are to be returned.
     * @return std::vector<Edge> A vector containing all the edges connected to the specified vertex.
     */
    std::vector<Edge> edges_for_vertex(const V& vertex) const {
        return edges_for_index(index_of(vertex));
    }

    /**
     * @brief Prints the graph to the console.
     */
    void print() const {
        for (int i = 0; i < vertex_count(); ++i) {
            std::cout << vertex_at(i) << " -> ";
            for (const V& neighbor : neighbors_for_index(i)) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};

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