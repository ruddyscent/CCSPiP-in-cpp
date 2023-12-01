/**
 * @file dijkstra.h
 * @brief Header file for Dijkstra's algorithm implementation.
 * @details Header file for Dijkstra's algorithm implementation.
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

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits>
#include <queue>
#include <vector>
#include <unordered_map>

#include "weighted_graph.h"
#include "weighted_edge.h"

/**
 * @struct DijkstraNode
 * @brief Represents a node in Dijkstra's algorithm.
 */
struct DijkstraNode {
    /**
     * @brief Constructs a DijkstraNode object.
     * @param vertex The vertex index.
     * @param distance The distance from the source vertex.
     */
    DijkstraNode(int vertex, double distance) : vertex(vertex), distance(distance) {}

    /**
     * @brief Overloads the less than operator for DijkstraNode objects.
     * @param other The other DijkstraNode object to compare.
     * @return True if this node has a greater distance than the other node, false otherwise.
     */
    bool operator<(const DijkstraNode& other) const {
        return distance > other.distance;
    }

    /**
     * @brief Overloads the equality operator for DijkstraNode objects.
     * @param other The other DijkstraNode object to compare.
     * @return True if this node has the same distance as the other node, false otherwise.
     */
    bool operator==(const DijkstraNode& other) const {
        return distance == other.distance;
    }

    int vertex; ///< The vertex index.
    double distance; ///< The distance from the source vertex.
};

/**
 * @brief Implements Dijkstra's algorithm to find the shortest path in a weighted graph.
 * 
 * @tparam V The type of the vertices in the graph.
 * @param wg The weighted graph.
 * @param root The root vertex to start the algorithm from.
 * @return A pair containing the distances from the root vertex to each vertex in the graph,
 *         and a map representing the shortest path from the root vertex to each vertex.
 */
template <typename V>
std::pair<std::vector<double>, std::unordered_map<int, WeightedEdge>> dijkstra(const WeightedGraph<V>& wg, V root) {
    int first = wg.index_of(root);
    std::vector<double> distances(wg.vertex_count(), std::numeric_limits<double>::infinity());
    distances[first] = 0;
    std::unordered_map<int, WeightedEdge> path_dict;
    std::priority_queue<DijkstraNode> pq;
    pq.push(DijkstraNode(first, 0));

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();
        double dist_u = distances[u];

        for (WeightedEdge& we : wg.edges_for_index(u)) {
            double dist_v = distances[we.get_v()];
            if (dist_v == std::numeric_limits<double>::infinity() || dist_v > we.get_weight() + dist_u) {
                distances[we.get_v()] = we.get_weight() + dist_u;
                path_dict[we.get_v()] = we;
                pq.push(DijkstraNode(we.get_v(), we.get_weight() + dist_u));
            }
        }
    }

    return std::make_pair<std::vector<double>, std::unordered_map<int, WeightedEdge>>(std::move(distances), std::move(path_dict));
}

/**
 * Converts an array of distances to a dictionary mapping vertices to their respective distances.
 * 
 * @param wg The weighted graph.
 * @param distances The array of distances.
 * @return The dictionary mapping vertices to their respective distances.
 */
template <typename V>
std::unordered_map<V, double> distance_array_to_vertex_dict(const WeightedGraph<V>& wg, std::vector<double>& distances) {
    std::unordered_map<V, double> distance_dict;
    for (int i = 0; i < distances.size(); i++) {
        distance_dict[wg.vertex_at(i)] = distances[i];
    }
    return distance_dict;
}


/**
 * @brief Converts a path dictionary to a path represented as a vector of weighted edges.
 * 
 * This function takes a start node, an end node, and a path dictionary, and returns a path
 * from the start node to the end node as a vector of weighted edges. The path dictionary
 * is a mapping from each node in the path to the previous edge that leads to that node.
 * 
 * @param start The starting node of the path.
 * @param end The ending node of the path.
 * @param path_dict The path dictionary containing the mapping from nodes to edges.
 * @return A vector of weighted edges representing the path from start to end.
 */
std::vector<WeightedEdge> path_dict_to_path(int start, int end, std::unordered_map<int, WeightedEdge>& path_dict) {
    std::vector<WeightedEdge> path;
    WeightedEdge edge = path_dict[end];
    path.push_back(edge);

    while (edge.get_u() != start) {
        edge = path_dict[edge.get_u()];
        path.push_back(edge);
    }

    reverse(path.begin(), path.end());
    return path;
}

#endif // DIJKSTRA_H