/**
 * @file hanoi.cc
 * @brief Solves the Tower of Hanoi problem.
 * @details The Tower of Hanoi is a mathematical puzzle where you have three rods and n disks of different sizes.
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

#include <cstdlib>
#include <iostream>
#include <stack>

/**
 * Solves the Tower of Hanoi problem recursively.
 * Moves the top n disks from the begin stack to the end stack using the temp stack as a buffer.
 * @param begin The stack where the disks start.
 * @param end The stack where the disks should end up.
 * @param temp The stack used as a buffer.
 * @param n The number of disks to move.
 */
void hanoi(std::stack<int>& begin, std::stack<int>& end, std::stack<int>& temp, int n) {
    if (n == 1) {
        end.push(begin.top());
        begin.pop();
    } else {
        hanoi(begin, temp, end, n - 1);
        end.push(begin.top());
        begin.pop();
        hanoi(temp, end, begin, n - 1);
    }
}

/**
 * @brief Prints the contents of a stack of integers.
 * 
 * @param s The stack to be printed.
 */
void print_stack(const std::stack<int>& s) {
    std::stack<int> temp = s;
    std::cout << "[";
    while (!temp.empty()) {
        std::cout << temp.top();
        temp.pop();
        if (!temp.empty()) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief The main function that solves the Tower of Hanoi problem.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    int num_discs = 3;
    std::stack<int> tower_a;
    std::stack<int> tower_b;
    std::stack<int> tower_c;

    for (int i = 1; i <= num_discs; ++i) {
        tower_a.push(i);
    }
    
    hanoi(tower_a, tower_c, tower_b, num_discs);
    print_stack(tower_a);
    print_stack(tower_b);
    print_stack(tower_c);

    return EXIT_SUCCESS;
}
