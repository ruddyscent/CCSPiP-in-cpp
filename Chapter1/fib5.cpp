/**
 * @file fib5.cpp
 * @brief A program that calculates the nth Fibon.cppi number using an iterative algorithm.
 * @details This program defines an iterative function to calculate the nth Fibon.cppi number and a main function that calls the function to calculate and print the 5th Fibon.cppi number to the console.
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

/**
 * Calculates the nth Fibon.cppi number iteratively.
 * @param n The index of the Fibon.cppi number to calculate.
 * @return The nth Fibon.cppi number.
 */
int fib5(int n) {
    if (n == 0) return n;  // special case
    int last = 0;  // initially set to fib(0)
    int next = 1;  // initially set to fib(1)
    for (int i = 1; i < n; ++i) {
        int tmp = next;
        next = last + next;
        last = tmp;
    }
    return next;
}

/**
 * @brief The main function that calls the fib5 function and prints its result.
 * 
 * @param argc The number of command-line arguments provided.
 * @param argv An array of strings containing the command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    std::cout << fib5(5) << std::endl;
    return EXIT_SUCCESS;
}
