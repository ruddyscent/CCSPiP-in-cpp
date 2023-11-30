#ifndef MST_H
#define MST_H

#include <vector>
#include "weighted_graph.h"
#include "weighted_edge.h"

using WeightedPath = std::vector<WeightedEdge>;

float total_weight(const WeightedPath& wp);

WeightedPath mst(WeightedGraph<std::string>& wg, int start = 0);

void print_weighted_path(WeightedGraph<std::string>& wg, const WeightedPath& wp);

#endif // MST_H