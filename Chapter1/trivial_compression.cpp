/**
 * @file trivial_compression.cpp
 * @brief This file contains the implementation of a simple gene compression algorithm.
 * @details The algorithm compresses a DNA sequence by converting each nucleotide to a 2-bit code and concatenating them.
 * The compressed sequence is then stored in an integer array. The algorithm also provides a decompression method to
 * convert the compressed sequence back to the original DNA sequence. The implementation uses templates to allow for
 * different integer types to be used for the compressed sequence.
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

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief A class that compresses and decompresses gene sequences.
 * 
 * @tparam T The type of the compressed gene.
 */
template<typename T>
class CompressedGene {
public:
    /**
     * @brief Constructor for CompressedGene class that takes a gene string and compresses it.
     * 
     * @tparam T The type of the compressed gene.
     * @param gene The gene string to be compressed.
     */
    CompressedGene<T>(const std::string& gene): _bit_string(1) {
        _compress(gene);
    }

    /**
     * @brief Decompresses the compressed gene sequence.
     * 
     * @tparam T The type of the compressed gene.
     * @return The decompressed gene sequence.
     */
    std::string decompress() const {
        std::string gene;
        for (int i = bit_length() - 3; i >= 0; i -= 2) {  // - 3 to exclude sentinel
            int bits = (_bit_string >> i) & 0b11;  // get just 2 relevant bits
            switch (bits) {
                case 0b00:  // A
                    gene += 'A';
                    break;
                case 0b01:  // C
                    gene += 'C';
                    break;
                case 0b10:  // G
                    gene += 'G';
                    break;
                case 0b11:  // T
                    gene += 'T';
                    break;
                default:
                    throw std::invalid_argument("Invalid bits: " + std::to_string(bits));
            }
        }
        return gene;
    }

    /**
     * @brief Returns the compressed gene sequence.
     * 
     * @tparam T The type of the compressed gene.
     * @return The compressed gene sequence.
     */
    T bit_string() const {
        return _bit_string;
    }

    /**
     * @brief Returns the length of the compressed gene sequence in bits.
     * 
     * @tparam T The type of the compressed gene.
     * @return The length of the compressed gene sequence in bits.
     */
    int bit_length() const {
        return log2(_bit_string) + 1;
    }

private:
    /**
     * @brief Compresses the gene sequence.
     * 
     * @tparam T The type of the compressed gene.
     * @param gene The gene sequence to be compressed.
     */
    void _compress(const std::string& gene) {
        for (char nucleotide : gene) {
            _bit_string <<= 2;  // shift left two bits
            switch (nucleotide) {  
                case 'A':  // change last two bits to 00
                    _bit_string |= 0b00;
                    break;
                case 'C':  // change last two bits to 01
                    _bit_string |= 0b01;
                    break;
                case 'G':  // change last two bits to 10
                    _bit_string |= 0b10;
                    break;
                case 'T':  // change last two bits to 11
                    _bit_string |= 0b11;
                    break;
                default:
                    throw std::invalid_argument("Invalid Nucleotide: " + std::string(1, nucleotide));
            }
        }
    }

    T _bit_string;
};


/**
 * @brief A template function that performs trivial compression on a given data type.
 * 
 * @tparam T The data type to be compressed.
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const CompressedGene<T>& gene) {
    out << gene.decompress();
    return out;
}

/**
 * @brief A class that represents a compressed gene using a vector of CompressedGene objects.
 * 
 * @tparam T The type of the CompressedGene object.
 */
template<typename T>
class CompressedGene2 {
public:
    /**
     * @brief Constructs a CompressedGene2 object from a given gene string.
     * 
     * @param gene The gene string to be compressed.
     */
    CompressedGene2<T>(const std::string& gene) {
        int chunk_size = (sizeof(T) * 8 - 1) / 2;
        int num_chunks = int(gene.size() / chunk_size + 1);
        int i = 0;
        while (i < num_chunks - 1) {
            container.emplace_back(CompressedGene<T>(gene.substr(i * chunk_size, chunk_size)));
            i++;
        }
        container.emplace_back(gene.substr(i * chunk_size));
    }

    /**
     * @brief Decompresses the gene string and returns it.
     * 
     * @return The decompressed gene string.
     */
    std::string decompress() const {
        std::string gene;
        for (const CompressedGene<T>& chunk : container) {
            gene += chunk.decompress();
        }
        return gene;
    }

    /**
     * @brief Returns the bit length of the compressed gene.
     * 
     * @return The bit length of the compressed gene.
     */
    int bit_length() const {
        return 8 * sizeof(T) * container.size();
    }

private:
    std::vector<CompressedGene<T>> container;
};

/**
 * @brief A template function that compresses data of any type T.
 * 
 * @tparam T The type of data to be compressed.
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const CompressedGene2<T>& gene) {
    out << gene.decompress();
    return out;
}

/**
 * @brief Main function that compresses a file using a trivial compression algorithm.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char* argv[]) {
    std::string original;
    for (int i = 0; i < 100; i++) {
        original += "TAGGGATTAACCGTTATATATATATAGCCATGGATCGATTATATAGGGATTAACCGTTATATATATATAGCCATGGATCGATTATA";
    }

    std::cout << "original is " << original.size() * sizeof(char) << " bytes" << std::endl;
    CompressedGene2<int> compressed(original);  // compress
    std::cout << "compressed is " << compressed.bit_length() / 8 << " bytes" << std::endl;
    std::cout << compressed << std::endl;  // decompress
    std::cout << "original and decompressed are the same: " << (original == compressed.decompress() ? "true" : "false") << std::endl;

    return EXIT_SUCCESS;
}
