/**
 * @file calculating_pi.cpp
 * @brief A program that calculates the value of pi using the Leibniz formula.
 * @details This program defines a function to calculate the value of pi using the Leibniz formula and a main function that calls the function to calculate and print the value of pi with 1,000,000 terms to the console.
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
 * Calculates the value of pi using the Leibniz formula.
 * @param n_terms The number of terms to use in the calculation.
 * @return The calculated value of pi.
 */
float calculate_pi(int n_terms) {
    float numerator = 4.0;
    float denominator = 1.0;
    float operation = 1.0;
    float pi = 0.0;

    for (int i = 0; i < n_terms; ++i) {
        pi += operation * (numerator / denominator);
        denominator += 2.0;
        operation *= -1.0;
    }

    return pi;
}

/**
 * The main function that calls the calculate_pi function to calculate the value of pi with 1,000,000 terms and prints it to the console.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return EXIT_SUCCESS if the program executes s.cppessfully.
 */
int main(int argc, char* argv[]) {
    cout << calculate_pi(1000000) << endl;
    return EXIT_SUCCESS;
}