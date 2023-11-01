/**
 * @file edge.h
 * @brief The Edge class represents a directed edge in a graph.
 * @details The Edge class represents a directed edge in a graph.
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

#pragma once

#include <iostream>
#include <string>

/**
 * @brief The Edge class represents a directed edge in a graph.
 * 
 */
class Edge {
public:
    /**
     * @brief Construct a new Edge object.
     * 
     * @param u The "from" vertex.
     * @param v The "to" vertex.
     */
    Edge(int u, int v) : _u(u), _v(v) {}

    /**
     * @brief Get the reversed edge.
     * 
     * @return Edge The reversed edge.
     */
    Edge reversed() const {
        return Edge(_v, _u);
    }

    /**
     * @brief Get the string representation of the edge.
     * 
     * @return std::string The string representation of the edge.
     */
    std::string to_string() const {
        return std::to_string(_u) + " -> " + std::to_string(_v);
    }

    /**
     * Returns the first vertex of the edge.
     * @return The first vertex of the edge.
     */
    int get_u() const {
        return _u;
    }

    /**
     * Returns the second vertex of the edge.
     * @return The second vertex of the edge.
     */
    int get_v() const {
        return _v;
    }

protected:
    int _u; // the "from" vertex
    int _v; // the "to" vertex
};
