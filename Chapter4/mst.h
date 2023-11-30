/**
 * @file mst.h
 * @brief The minimum spanning tree (MST) of a weighted graph.
 * @details The minimum spanning tree (MST) of a weighted graph.
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

#ifndef MST_H
#define MST_H

#include <vector>
#include "weighted_graph.h"
#include "weighted_edge.h"

/**
 * @brief Represents a weighted path, which is a sequence of weighted edges.
 */
using WeightedPath = std::vector<WeightedEdge>;

/**
 * Calculates the total weight of a weighted path.
 *
 * @param wp The weighted path for which to calculate the total weight.
 * @return The total weight of the weighted path.
 */
float total_weight(const WeightedPath& wp);

/**
 * @brief Prints the weighted path in a weighted graph.
 * 
 * @tparam V The type of vertices in the graph.
 * @param wg The weighted graph.
 * @param wp The weighted path to be printed.
 */
template <typename V>
void print_weighted_path(WeightedGraph<V>& wg, const WeightedPath& wp) {
    for (const auto& edge : wp) {
        std::cout << wg.vertex_at(edge.get_u()) << " " << edge.get_weight() << "> " << wg.vertex_at(edge.get_v()) << "\n";
    }
    std::cout << "Total Weight: " << total_weight(wp) << "\n";
}

/**
 * @brief Calculates the minimum spanning tree (MST) of a weighted graph.
 * 
 * @tparam V The type of vertices in the graph.
 * @param wg The weighted graph.
 * @param start The starting vertex index (default is 0).
 * @return The minimum spanning tree as a weighted path.
 */
template <typename V>
WeightedPath mst(WeightedGraph<V>& wg, int start = 0) {
    WeightedPath result;
    std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, std::greater<>> pq;
    std::vector<bool> visited(wg.vertex_count(), false);

    auto visit = [&](int index) {
        visited[index] = true;
        for (const auto& edge : wg.edges_for_index(index)) {
            if (!visited[edge.get_v()]) {
                pq.push(edge);
            }
        }
    };

    visit(start);

    while (!pq.empty()) {
        auto edge = pq.top();
        pq.pop();
        if (visited[edge.get_v()]) {
            continue;
        }
        result.push_back(edge);
        visit(edge.get_v());
    }

    return result;
}

#endif // MST_H