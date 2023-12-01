#include <vector>
#include <iostream>

#include "dijkstra.h"
#include "mst.h"

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