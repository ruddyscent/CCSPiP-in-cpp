/**
 * @file weighted_graph.h
 * @brief WeightedGraph class represents a weighted graph.
 * @details WeightedGraph class represents a weighted graph. The graph is represented as an adjacency list using a vector of vectors.
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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "graph.h"
#include "weighted_edge.h"

/**
 * @brief WeightedGraph class is a derived class of Graph class. It represents a weighted graph.
 * 
 * @tparam V Type of vertices in the graph.
 */
template <typename V>
class WeightedGraph : public Graph<V> {
public:
    /**
     * @brief Construct a new WeightedGraph object with given vertices.
     * 
     * @param vertices Vector of vertices to be added to the graph.
     */
    WeightedGraph(const std::vector<V>& vertices) : Graph<V>(vertices) {
        _edges.resize(vertices.size());
    }

    /**
     * @brief Adds an edge to the graph.
     * 
     * @param edge The edge to be added.
     */
    void add_edge(const WeightedEdge& edge) {
        _edges[edge.get_u()].push_back(edge);
        _edges[edge.get_v()].push_back(edge.reversed());
    }

    /**
     * @brief Adds an edge to the graph by indices of the vertices.
     * 
     * @param u Index of the first vertex.
     * @param v Index of the second vertex.
     * @param weight Weight of the edge.
     */
    void add_edge_by_indices(int u, int v, float weight) {
        WeightedEdge edge(u, v, weight);
        this->add_edge(edge);
    }

    /**
     * @brief Adds an edge to the graph by vertices.
     * 
     * @param first First vertex of the edge.
     * @param second Second vertex of the edge.
     * @param weight Weight of the edge.
     */
    void add_edge_by_vertices(const V& first, const V& second, float weight) {
        int u = std::find(this->_vertices.begin(), this->_vertices.end(), first) - this->_vertices.begin();
        int v = std::find(this->_vertices.begin(), this->_vertices.end(), second) - this->_vertices.begin();
        add_edge_by_indices(u, v, weight);
    }

    /**
     * Returns a vector of WeightedEdges that are adjacent to the vertex at the given index.
     * 
     * @param index The index of the vertex to get adjacent edges for.
     * @return A vector of WeightedEdges that are adjacent to the vertex at the given index.
     */
    std::vector<WeightedEdge> edges_for_index(int index) const {
        return _edges[index];
    }
    
    /**
     * @brief Returns a vector of pairs of neighbors of a vertex with their corresponding weights.
     * 
     * @param index Index of the vertex.
     * @return std::vector<std::pair<V, float>> Vector of pairs of neighbors of the vertex with their corresponding weights.
     */
    std::vector<std::pair<V, float>> neighbors_for_index_with_weights(int index) const {
        std::vector<std::pair<V, float>> result;
        for (const WeightedEdge& edge : this->edges_for_index(index)) {
            result.push_back({this->vertex_at(edge.get_v()), edge.get_weight()});
        }
        return result;
    }

    /**
     * @brief Prints the graph.
     * 
     */
    void print() const {
        for (int i = 0; i < this->vertex_count(); ++i) {
            std::cout << this->vertex_at(i) << " -> ";
            for (const auto& pair : neighbors_for_index_with_weights(i)) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << "\n";
        }
    }

protected:
    /**
     * A weighted graph represented as an adjacency list of edges.
     * Each vertex is represented by an index in the vector.
     * Each element in the vector is a vector of edges that are adjacent to the vertex.
     * Each edge is represented by a WeightedEdge struct.
     */
    std::vector<std::vector<WeightedEdge>> _edges;
};

#endif // WEIGHTED_GRAPH_H