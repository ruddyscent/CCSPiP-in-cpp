/**
 * @file fib2.cc
 * @brief A program that calculates the nth Fibonacci number using a recursive algorithm.
 * @details This program defines a recursive function to calculate the nth Fibonacci number and a main function that calls the function to calculate and print the 5th Fibonacci number to the console.
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
#include <iostream>

/**
 * Calculates the nth Fibonacci number recursively.
 * @param n The index of the Fibonacci number to calculate.
 * @return The nth Fibonacci number.
 */
int fib2(int n) {
    if (n < 2)  // base case
        return n;
    
    return fib2(n - 1) + fib2(n - 2);  // recursive case
}


/**
 * @brief The main function that calls the fib2 function and prints its result.
 * 
 * @param argc The number of command-line arguments provided.
 * @param argv An array of pointers to the arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    std::cout << fib2(5) << std::endl;
    return EXIT_SUCCESS;
}