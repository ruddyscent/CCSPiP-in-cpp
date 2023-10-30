/**
 * @file unbreakable_encryption.cc
 * @brief Demonstrates the use of the one-time pad encryption algorithm.
 * @details The one-time pad encryption algorithm is an unbreakable encryption algorithm.
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

#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

/**
 * Encrypts a given string using an unbreakable encryption algorithm.
 *
 * @param original The original string to encrypt.
 * @return A tuple containing the encrypted string and the encryption key.
 */
std::tuple<int, int> encrypt(const std::string& original) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 255);

    int dummy = 0;
    for (int i = 0; i < original.size(); i++) {
        dummy <<= 8;
        dummy |= distrib(gen);
    }

    int original_key = 0;
    for (char c : original) {
        original_key <<= 8;
        original_key |= static_cast<unsigned char>(c);
    }

    int encrypted = original_key ^ dummy;

    return std::make_tuple(dummy, encrypted);
}

/**
 * Decrypts a message using two keys.
 * @param key1 The first key used for decryption.
 * @param key2 The second key used for decryption.
 * @return The decrypted message as a string.
 */
std::string decrypt(int key1, int key2) {
    int decrypted = key1 ^ key2;

    std::string temp;
    while (decrypted != 0) {
        temp += static_cast<char>(decrypted & 0xFF);
        decrypted >>= 8;
    }

    return std::string(temp.rbegin(), temp.rend());
}

/**
 * @brief Encrypts a given string using a two-step encryption process.
 * 
 * The function divides the input string into chunks of size equal to the size of an integer.
 * Each chunk is encrypted using the `encrypt` function and the resulting keys are stored in a dummy vector.
 * The encrypted chunks are stored in another vector and returned as a tuple along with the dummy vector.
 * 
 * @param original The string to be encrypted.
 * @return A tuple containing two vectors - the dummy vector and the encrypted vector.
 */
std::tuple<std::vector<int>, std::vector<int>> encrypt2(const std::string& original) {
    int chunk_size = sizeof(int) * 8 / 8;
    int num_chunks = int(original.size() / chunk_size + 1);

    std::vector<int> dummy;
    std::vector<int> encrypted;
    int i = 0;
    while (i < num_chunks - 1) {
        auto keys = encrypt(original.substr(i * chunk_size, chunk_size));
        dummy.emplace_back(std::get<0>(keys));
        encrypted.emplace_back(std::get<1>(keys));
        i++;
    }
    
    auto keys = encrypt(original.substr(i * chunk_size));
    dummy.emplace_back(std::get<0>(keys));
    encrypted.emplace_back(std::get<1>(keys));

    return std::make_tuple(dummy, encrypted);
}

/**
 * @brief A sequence of characters represented as a string.
 */
std::string decrypt2(const std::vector<int>& keys1, const std::vector<int>& keys2) {
    std::string result;
    for (int i = 0; i < keys1.size(); i++) {
        result += decrypt(keys1[i], keys2[i]);
    }

    return result;
}

/**
 * @brief Main function that demonstrates the use of the encrypt2 and decrypt2 functions to perform unbreakable encryption.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char* argv[]) {
    auto keys = encrypt2("One Time Pad!");
    std::string result = decrypt2(std::get<0>(keys), std::get<1>(keys));
    std::cout << result << std::endl;

    return EXIT_SUCCESS;
}