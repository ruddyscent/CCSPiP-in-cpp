/**
 * @file generic_search.h
 * @brief Generic search algorithms implementation.
 * @details This file contains the implementation of generic search algorithms such as depth-first search, breadth-first search, and A* search.
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
**/

#include <algorithm>
#include <deque>
// #include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

/**
 * Checks if a given key is present in the given iterable using linear search.
 * 
 * @tparam T The type of elements in the iterable.
 * @param iterable The iterable to search for the key.
 * @param key The key to search for in the iterable.
 * @return True if the key is present in the iterable, false otherwise.
 */
template <typename T>
bool linear_contains(const std::vector<T> &iterable, const T &key) {
    return std::find(iterable.begin(), iterable.end(), key) != iterable.end();
}

/**
 * Checks if a given key is present in the given iterable using binary search.
 * 
 * @tparam T The type of elements in the iterable.
 * @param sequence The iterable to search for the key.
 * @param key The key to search for in the iterable.
 * @return True if the key is present in the iterable, false otherwise.
 */
template <typename T>
bool binary_contains(const std::vector<T> &sequence, const T &key) {
    auto begin = sequence.begin(), end = sequence.end();
    while (begin != end) {
        auto mid = begin + (end - begin) / 2;
        if (key < *mid) {
            end = mid;
        } else if (*mid < key) {
            begin = mid + 1;
        } else {
            return true;
        }
    }
    return false;
}

/**
 * @brief A generic node class that stores the state, parent node, cost, and heuristic.
 * 
 * @tparam T The type of the state.
 */
template <typename T>
class Node {
   public:
    /**
     * @brief Construct a new Node object.
     * 
     * @param state The state stored in the node.
     * @param parent A pointer to the parent node.
     * @param cost The cost to reach this node from the start node.
     * @param heuristic The estimated cost to reach the goal node from this node.
     */
    Node(const T &state, Node *parent, double cost = 0.0, double heuristic = 0.0)
        : state(state), parent(parent), cost(cost), heuristic(heuristic) {}

    /**
     * @brief Compare two nodes based on their f-cost (cost + heuristic).
     * 
     * @param other The other node to compare to.
     * @return true if this node has a lower f-cost than the other node, false otherwise.
     */
    bool operator<(const Node &other) const {
        return (cost + heuristic) < (other.cost + other.heuristic);
    }

    T state; /**< The state stored in the node. */
    Node *parent; /**< A pointer to the parent node. */
    double cost; /**< The cost to reach this node from the start node. */
    double heuristic; /**< The estimated cost to reach the goal node from this node. */
};

/**
 * Returns a vector of states representing the path from the root node to the given node.
 * 
 * @tparam T The type of the state.
 * @param node A pointer to the node to get the path to.
 * @return A vector of states representing the path from the root node to the given node.
 */
template <typename T>
std::vector<T> node_to_path(Node<T> * node) {
    std::vector<T> path;
    while (node) {
        path.push_back(node->state);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

/**
 * @brief A generic search function that takes a container and a value to search for.
 * 
 * @tparam T The type of the elements in the container.
 * @param container The container to search in.
 * @param value The value to search for.
 * @return An iterator to the first element in the container that matches the value, or the end iterator if not found.
 */
template <typename T>
using SuccessorFunction = std::function<std::vector<T>(T &)>;

/**
 * Performs a depth-first search on a generic tree.
 * @tparam T The type of the tree nodes.
 * @param initial The initial state of the tree.
 * @param goal_test A function that returns true if the goal state is reached.
 * @param successors A function that returns the children of a given node.
 * @return A pointer to the node that contains the goal state, or nullptr if it is not found.
 */
template <typename T>
Node<T> *dfs(const T &initial, 
    const std::function<bool(const T &)> &goal_test,
            const SuccessorFunction<T> &successors) {
    std::stack<Node<T> *> frontier;
    frontier.push(new Node<T>(initial, nullptr));
    std::set<T> explored;

    while (!frontier.empty()) {
        Node<T> *current_node = frontier.top();
        frontier.pop();
        T current_state = current_node->state;

        if (goal_test(current_state)) {
            return current_node;
        }

        for (const T &child : successors(current_state)) {
            if (explored.count(child)) {
                continue;
            }
            explored.insert(child);
            frontier.push(new Node<T>(child, current_node));
        }
    }

    return nullptr;
}

/**
 * @brief Breadth-first search algorithm implementation.
 * 
 * @tparam T Type of the state.
 * @param initial The initial state.
 * @param goal_test A function that returns true if the given state is the goal state.
 * @param successors A function that returns a vector of possible successor states.
 * @return Node<T>* A pointer to the node containing the goal state, or nullptr if it is not found.
 */
template <typename T>
Node<T> *bfs(const T &initial, const std::function<bool(const T &)> &goal_test,
             const SuccessorFunction<T> &successors) {
    std::queue<Node<T> *> frontier;
    frontier.push(new Node<T>(initial, nullptr));
    std::set<T> explored;

    while (!frontier.empty()) {
        Node<T> *current_node = frontier.front();
        frontier.pop();
        T current_state = current_node->state;

        if (goal_test(current_state)) {
            return current_node;
        }

        for (const T &child : successors(current_state)) {
            if (explored.count(child)) {
                continue;
            }
            explored.insert(child);
            frontier.push(new Node<T>(child, current_node));
        }
    }

    return nullptr;
}

/**
 * @brief A generic search function that takes a container and a value to search for.
 * 
 * @tparam T The type of the container.
 * @param container The container to search in.
 * @param value The value to search for.
 * @return int The index of the value in the container, or -1 if not found.
 */
template <typename T>
Node<T> *astar(const T &initial, const std::function<bool(const T &)> &goal_test,
               const SuccessorFunction<T> &successors, const std::function<double(const T &)> &heuristic) {
    std::priority_queue<Node<T> *> frontier;
    frontier.push(new Node<T>(initial, nullptr, 0.0, heuristic(initial)));
    std::map<T, double> explored;

    while (!frontier.empty()) {
        Node<T> *current_node = frontier.top();
        frontier.pop();
        T current_state = current_node->state;

        if (goal_test(current_state)) {
            return current_node;
        }

        for (const T &child : successors(current_state)) {
            double new_cost = current_node->cost + 1;

            if (!explored.count(child) || explored[child] > new_cost) {
                explored[child] = new_cost;
                frontier.push(new Node<T>(child, current_node, new_cost, heuristic(child)));
            }
        }
    }

    return nullptr;
}

// int main() {
//     std::cout << std::boolalpha;

//     std::cout << linear_contains(std::vector<int>{1, 5, 15, 15, 15, 15, 20}, 5) << std::endl;  // true
//     std::cout << binary_contains(std::vector<std::string>{"a", "d", "e", "f", "z"}, std::string("f")) << std::endl;  // true
//     std::cout << binary_contains(std::vector<std::string>{"john", "mark", "ronald", "sarah"}, std::string("sheila")) << std::endl;  // false

//     return EXIT_SUCCESS;
// }