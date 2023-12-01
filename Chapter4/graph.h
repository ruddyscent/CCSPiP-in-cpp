/**
 * @file graph.h
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

#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
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
     * @brief Constructs a new Graph object.
     * 
     * @param vertices A vector containing all the vertices in the graph.
     */
    Graph(const std::vector<V>& vertices) : _vertices(vertices) {
        _edges.resize(vertices.size());
    }

    /**
     * @brief Returns the number of vertices in the graph.
     * 
     * @return int The number of vertices in the graph.
     */
    int vertex_count() const {
        return _vertices.size();
    }

    /**
     * @brief Returns the number of edges in the graph.
     * 
     * @return int The number of edges in the graph.
     */
    int edge_count() const {
        int count = 0;
        for (const auto& edge_list : _edges) {
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
        _vertices.push_back(vertex);
        _edges.push_back({});
    }

    /**
     * @brief Adds a new edge to the graph.
     * 
     * @param edge The edge to be added.
     */
    void add_edge(const Edge& edge) {
        _edges[edge.get_u()].push_back(edge);
        _edges[edge.get_v()].push_back(edge.reversed());
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
        int u = std::find(_vertices.begin(), _vertices.end(), first) - _vertices.begin();
        int v = std::find(_vertices.begin(), _vertices.end(), second) - _vertices.begin();
        add_edge_by_indices(u, v);
    }

    /**
     * @brief Returns the vertex at the specified index.
     * 
     * @param index The index of the vertex.
     * @return V The vertex at the specified index.
     */
    V vertex_at(int index) const {
        return _vertices[index];
    }

    /**
     * @brief Returns the index of the specified vertex.
     * 
     * @param vertex The vertex whose index is to be returned.
     * @return int The index of the specified vertex.
     */
    int index_of(const V& vertex) const {
        return std::find(_vertices.begin(), _vertices.end(), vertex) - _vertices.begin();
    }

    /**
     * @brief Returns a vector containing all the neighbors of the vertex at the specified index.
     * 
     * @param index The index of the vertex.
     * @return std::vector<V> A vector containing all the neighbors of the vertex at the specified index.
     */
    std::vector<V> neighbors_for_index(int index) const {
        std::vector<V> result;
        for (const Edge& edge : _edges[index]) {
            result.push_back(vertex_at(edge.get_v()));
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
        return _edges[index];
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

protected:
    /**
     * @brief A vector containing all the vertices in the graph.
     */
    std::vector<V> _vertices;

    /**
     * @brief A vector of vectors containing all the edges in the graph.
     */
    std::vector<std::vector<Edge>> _edges;
};

#endif // GRAPH_H