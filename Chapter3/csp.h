/**
 * @file csp.h
 * @brief Constraint Satisfaction Problem
 * @details A constraint satisfaction problem is defined by three components: variables, domains, and constraints. The problem is to assign a value to each variable from its domain such that all constraints are satisfied. A constraint satisfaction problem can be represented as a graph with variables being nodes and constraints being edges.
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

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <vector>

/**
 * @brief Constraint Satisfaction Problem
 * @details A constraint satisfaction problem is defined by three components: variables, domains, and constraints. The problem is to assign a value to each variable from its domain such that all constraints are satisfied. A constraint satisfaction problem can be represented as a graph with variables being nodes and constraints being edges.
 * @tparam V Variable type
 * @tparam D Domain type
 *
 * @see https://en.wikipedia.org/wiki/Constraint_satisfaction_problem
 */
template <typename V, typename D>
class Constraint
{
public:
    std::vector<V> variables; // Variables that the constraint is between

    /**
     * @brief Construct a new Constraint object
     * @details A constraint is a relationship between variables. The variables that the constraint is between are passed in as a vector.
     * @param variables Variables that the constraint is between
     */
    Constraint(const std::vector<V> &variables) : variables(variables) {}

    /**
     * @brief Check if the constraint is satisfied
     * @details A constraint is satisfied if it doesn't violate any of the constraints. In other words, if it doesn't violate any of the constraints, it is satisfied.
     * @param assignment A map of variables to their assigned values
     * @return true If the constraint is satisfied
     */
    virtual bool satisfied(std::unordered_map<V, D> &assignment) = 0;
};

/**
 * @brief Constraint Satisfaction Problem
 * @details A constraint satisfaction problem is defined by three components: variables, domains, and constraints. The problem is to assign a value to each variable from its domain such that all constraints are satisfied. A constraint satisfaction problem can be represented as a graph with variables being nodes and constraints being edges.
 * @tparam V Variable type
 * @tparam D Domain type
 */
template <typename V, typename D>
class CSP
{
public:
    /**
     * @brief Construct a new CSP object
     * @details A constraint satisfaction problem is defined by three components: variables, domains, and constraints. The problem is to assign a value to each variable from its domain such that all constraints are satisfied. A constraint satisfaction problem can be represented as a graph with variables being nodes and constraints being edges.
     * @param variables Variables to be assigned
     * @param domains Domain of each variable
     */
    CSP(const std::vector<V> &variables, const std::unordered_map<V, std::vector<D>> &domains) 
        : _variables(variables), _domains(domains)
    {
        for (const auto &variable : _variables)
        {
            _constraints[variable] = std::vector<std::shared_ptr<Constraint<V, D>>>();
            if (_domains.find(variable) == _domains.end())
            {
                throw std::invalid_argument("Every variable should have a domain assigned to it.");
            }
        }
    }

    /**
     * @brief Add a constraint to the CSP
     * @details A constraint is a relationship between variables. The variables that the constraint is between are passed in as a vector.
     * @param constraint Constraint to be added
     */
    void add_constraint(std::shared_ptr<Constraint<V, D>> constraint)
    {
        for (const auto &variable : constraint->variables)
        {
            if (std::find(_variables.begin(), _variables.end(), variable) == _variables.end())
            {
                throw std::invalid_argument("Variable in constraint not in CSP");
            }
            else
            {
                _constraints[variable].push_back(constraint);
            }
        }
    }

    /**
     * @brief Check if the value assignment is consistent by checking all constraints
     * @details A constraint is satisfied if it doesn't violate any of the constraints. In other words, if it doesn't violate any of the constraints, it is satisfied.
     * @param variable Variable to be assigned
     * @param assignment A map of variables to their assigned values
     * @return true If the value assignment is consistent
     */
    bool consistent(V variable, std::unordered_map<V, D> &assignment)
    {
        for (const auto &constraint : _constraints[variable])
        {
            if (!constraint->satisfied(assignment))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Backtracking search
     * @details Backtracking search is a form of depth-first search where we try assigning values to one variable at a time. At each assignment, we check if the value assignment is consistent with all constraints. If so, we continue the search; otherwise, we backtrack.
     * @param assignment A map of variables to their assigned values
     * @return std::unordered_map<V, D> A map of variables to their assigned values
     **/
    std::unordered_map<V, D> backtracking_search(std::unordered_map<V, D> assignment = {})
    {
        if (assignment.size() == _variables.size())
        {
            return assignment;
        }

        std::vector<V> unassigned;
        std::copy_if(_variables.begin(), _variables.end(), std::back_inserter(unassigned),
                     [&assignment](V i) { return assignment.find(i) == assignment.end(); });

        auto first = unassigned.front();
        for (const auto &value : _domains[first])
        {
            std::unordered_map<V, D> local_assignment = assignment;
            local_assignment[first] = value;
            if (consistent(first, local_assignment))
            {
                std::unordered_map<V, D> result = backtracking_search(local_assignment);
                if (result.size() != 0)
                {
                    return result;
                }
            }
        }

        return {};
    }

private:
    std::vector<V> _variables;  // Variables to be assigned
    std::unordered_map<V, std::vector<D>> _domains;  // Domain of each variable
    std::unordered_map<V, std::vector<std::shared_ptr<Constraint<V, D>>>> _constraints;  // Constraints on variables
};