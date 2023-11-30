/**
 * @file mst.cpp
 * @brief
 * @details
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
#include <functional>
#include <queue>
#include <vector>

#include "weighted_graph.h"
#include "weighted_edge.h"

using WeightedPath = std::vector<WeightedEdge>;

float total_weight(const WeightedPath& wp) {
    float total = 0.0;
    for (const auto& e : wp) {
        total += e.get_weight();
    }
    return total;
}

WeightedPath mst(WeightedGraph<std::string>& wg, int start = 0) {
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

void print_weighted_path(WeightedGraph<std::string>& wg, const WeightedPath& wp) {
    for (const auto& edge : wp) {
        std::cout << wg.vertex_at(edge.get_u()) << " " << edge.get_weight() << "> " << wg.vertex_at(edge.get_v()) << "\n";
    }
    std::cout << "Total Weight: " << total_weight(wp) << "\n";
}

int main(int argc, char* argv[]) {
    WeightedGraph<std::string> city_graph2({"Seattle", "San Francisco", "Los Angeles", "Riverside", "Phoenix", "Chicago", "Boston", "New York", "Atlanta", "Miami", "Dallas", "Houston", "Detroit", "Philadelphia", "Washington"});

    city_graph2.add_edge_by_vertices("Seattle", "Chicago", 1737);
    city_graph2.add_edge_by_vertices("Seattle", "San Francisco", 678);
    city_graph2.add_edge_by_vertices("San Francisco", "Riverside", 386);
    city_graph2.add_edge_by_vertices("San Francisco", "Los Angeles", 348);
    city_graph2.add_edge_by_vertices("Los Angeles", "Riverside", 50);
    city_graph2.add_edge_by_vertices("Los Angeles", "Phoenix", 357);
    city_graph2.add_edge_by_vertices("Riverside", "Phoenix", 307);
    city_graph2.add_edge_by_vertices("Riverside", "Chicago", 1704);
    city_graph2.add_edge_by_vertices("Phoenix", "Dallas", 887);
    city_graph2.add_edge_by_vertices("Phoenix", "Houston", 1015);
    city_graph2.add_edge_by_vertices("Dallas", "Chicago", 805);
    city_graph2.add_edge_by_vertices("Dallas", "Atlanta", 721);
    city_graph2.add_edge_by_vertices("Dallas", "Houston", 225);
    city_graph2.add_edge_by_vertices("Houston", "Atlanta", 702);
    city_graph2.add_edge_by_vertices("Houston", "Miami", 968);
    city_graph2.add_edge_by_vertices("Atlanta", "Chicago", 588);
    city_graph2.add_edge_by_vertices("Atlanta", "Washington", 543);
    city_graph2.add_edge_by_vertices("Atlanta", "Miami", 604);
    city_graph2.add_edge_by_vertices("Miami", "Washington", 923);
    city_graph2.add_edge_by_vertices("Chicago", "Detroit", 238);
    city_graph2.add_edge_by_vertices("Detroit", "Boston", 613);
    city_graph2.add_edge_by_vertices("Detroit", "Washington", 396);
    city_graph2.add_edge_by_vertices("Detroit", "New York", 482);
    city_graph2.add_edge_by_vertices("Boston", "New York", 190);
    city_graph2.add_edge_by_vertices("New York", "Philadelphia", 81);
    city_graph2.add_edge_by_vertices("Philadelphia", "Washington", 123);

    auto result = mst(city_graph2);
    print_weighted_path(city_graph2, result);

    return EXIT_SUCCESS;
}