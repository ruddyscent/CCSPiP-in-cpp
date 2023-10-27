/**
 * @file fib1.cc
 * @brief A program that calculates the nth Fibonacci number using a recursive algorithm.
 * @details This program defines a recursive function to calculate the nth Fibonacci number and a main function that calls the function to calculate and print the 5th Fibonacci number to the console.
 * The program takes no input from the user and returns EXIT_SUCCESS if it executes successfully.
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

using namespace std;

/**
 * Calculates the nth Fibonacci number recursively.
 * @param n The index of the Fibonacci number to calculate.
 * @return The nth Fibonacci number.
 */
int fib1(int n) {
    return fib1(n - 1) + fib1(n - 2);
}

/**
 * The main function that calls the fib1 function to calculate the 5th Fibonacci number and prints it to the console.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return EXIT_SUCCESS if the program executes successfully.
 */
int main(int argc, char* argv[]) {
    cout << fib1(5) << endl;
    return EXIT_SUCCESS;
}
