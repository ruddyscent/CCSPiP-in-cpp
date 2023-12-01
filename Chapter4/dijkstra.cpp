#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <optional>
#include <iostream>
#include <utility>
#include <string>

#include "mst.h"
#include "weighted_graph.h"
#include "weighted_edge.h"

struct DijkstraNode {
    DijkstraNode(int vertex, double distance) : vertex(vertex), distance(distance) {}

    bool operator<(const DijkstraNode& other) const {
        return distance > other.distance;
    }

    bool operator==(const DijkstraNode& other) const {
        return distance == other.distance;
    }

    int vertex;
    double distance;
};

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

template <typename V>
std::unordered_map<V, double> distance_array_to_vertex_dict(const WeightedGraph<V>& wg, std::vector<double>& distances) {
    std::unordered_map<V, double> distance_dict;
    for (int i = 0; i < distances.size(); i++) {
        distance_dict[wg.vertex_at(i)] = distances[i];
    }
    return distance_dict;
}

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

    auto return_pair = dijkstra<std::string>(city_graph2, "Los Angeles");
    auto name_distance = distance_array_to_vertex_dict<std::string>(city_graph2, return_pair.first);

    std::cout << "Distances from Los Angeles:\n";
    for (const auto& key_value : name_distance) {
        std::cout << key_value.first << " : " << key_value.second << "\n";
    }
    std::cout << "\n"; // blank line

    std::cout << "Shortest path from Los Angeles to Boston:\n";
    std::vector<WeightedEdge> path = path_dict_to_path(city_graph2.index_of("Los Angeles"), city_graph2.index_of("Boston"), return_pair.second);
    print_weighted_path(city_graph2, path);

    return EXIT_SUCCESS;
}