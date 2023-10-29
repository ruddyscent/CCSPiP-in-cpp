/**
 * @file dna_search.cc   
 * @brief Searches for a DNA sequence in a given string.
 * @details This program searches for a DNA sequence in a given string using
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
#include <cstdlib>
#include <iostream>
#include <vector>

enum class Nucleotide { A, C, G, T};

using Codon = std::tuple<Nucleotide, Nucleotide, Nucleotide>;
using Gene = std::vector<Codon>;

/**
 * @brief Overloads the less-than operator for Codon objects.
 * 
 * @param left The left-hand side Codon object.
 * @param right The right-hand side Codon object.
 * @return true if left is less than right, false otherwise.
 */
bool operator<(const Codon &left, const Codon &right)
{
    bool result = false;
    if (std::get<0>(left) < std::get<0>(right)) {
        result = true;
    } else if (std::get<0>(left) == std::get<0>(right)) {
        if (std::get<1>(left) < std::get<1>(right)) {
            result = true;
        } else if (std::get<1>(left) == std::get<1>(right)) {
            if (std::get<2>(left) < std::get<2>(right)) {
                result = true;
            }
        }
    }
    return result;
}

/**
 * Converts a string representation of a gene to a Gene object.
 *
 * @param s The string representation of the gene.
 * @return The Gene object corresponding to the given string.
 */
Gene string_to_gene(std::string s) {
    Gene gene;
    for (int i = 0; i < s.length(); i += 3) {
        if (i + 2 >= s.length()) {
            return gene;
        }

        std::vector<Nucleotide> tmp;
        for (int i = 0; i < 3; i++) {
            switch (s[i]) {
                case 'A':
                    tmp.push_back(Nucleotide::A);
                    break;
                case 'C':
                    tmp.push_back(Nucleotide::C);
                    break;
                case 'G':
                    tmp.push_back(Nucleotide::G);
                    break;
                case 'T':
                    tmp.push_back(Nucleotide::T);
                    break;
                default:
                    std::cerr << "Invalid Nucleotide: " << s[i] << std::endl;
                    exit(EXIT_FAILURE);
            }
        }
        Codon codon = std::make_tuple(tmp[0], tmp[1], tmp[2]);
        gene.push_back(codon);
    }
    return gene;
}

/**
 * Determines whether a given codon is present in a gene using linear search.
 *
 * @param gene The gene to search for the codon.
 * @param key_codon The codon to search for in the gene.
 * @return true if the codon is found in the gene, false otherwise.
 */
bool linear_contains(const Gene& gene, const Codon& key_codon) {
    for (const auto& codon : gene) {
        if (codon == key_codon) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if a given codon is present in a gene using binary search.
 * @param gene The gene to search in.
 * @param key_codon The codon to search for.
 * @return True if the codon is present in the gene, false otherwise.
 */
bool binary_contains(const Gene& gene, const Codon& key_codon) {
    auto it = std::lower_bound(gene.begin(), gene.end(), key_codon);
    return it != gene.end() && *it == key_codon;
}

/**
 * @brief Main function that searches for a DNA sequence in a given string.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char* argv[]) {
    std::string gene_str = "ACGTGGCTCTCTAACGTACGTACGTACGGGGTTTATATATACCCTAGGACTCCCTTT";
    Gene my_gene = string_to_gene(gene_str);

    Codon acg = {Nucleotide::A, Nucleotide::C, Nucleotide::G};
    Codon gat = {Nucleotide::G, Nucleotide::A, Nucleotide::T};

    std::cout << std::boolalpha;
    std::cout << linear_contains(my_gene, acg) << std::endl; // true
    std::cout << linear_contains(my_gene, gat) << std::endl; // false
        
    Gene my_sorted_gene = my_gene;
    std::sort(my_sorted_gene.begin(), my_sorted_gene.end());

    std::cout << binary_contains(my_sorted_gene, acg) << std::endl; // true
    std::cout << binary_contains(my_sorted_gene, gat) << std::endl; // false

    return EXIT_SUCCESS;
}
