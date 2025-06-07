#include "HashTable.h"
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include <filesystem>

static size_t simpleHash(const std::string& s) {
    size_t hash = 0;
    for (char c : s) hash += c;
    return hash;
}

static size_t polynomialHash(const std::string& s) {
    size_t hash = 0;
    for (char c : s) hash = hash * 13 + c;
    return hash;
}

static size_t djb2Hash(const std::string& s) {
    size_t hash = 5381;
    for (char c : s) hash = ((hash << 5) + hash) + c;
    return hash;
}

static std::vector<std::string> generateRandomStrings(size_t count, size_t length = 10) {
    std::vector<std::string> result;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist('a', 'z');
    for (size_t i = 0; i < count; ++i) {
        std::string s;
        for (size_t j = 0; j < length; ++j) {
            s += static_cast<char>(dist(rng));
        }
        result.push_back(s);
    }
    return result;
}

static std::vector<std::string> generateOptimisticStrings(size_t count) {
    std::vector<std::string> result;
    for (size_t i = 0; i < count; ++i) {
        result.push_back("str" + std::to_string(i));
    }
    return result;
}

static std::vector<std::string> generatePessimisticStrings(size_t count) {
    std::vector<std::string> result;
    for (size_t i = 0; i < count; ++i) {
        result.push_back("aaaaaaa" + std::to_string(i));
    }
    return result;
}

template<typename HashFunc>
void testHashFunction(const std::string& hashName, HashFunc hashFunc, size_t tableSize, size_t numElements,
    const std::string& caseName, const std::vector<std::string>& data) {
    HashTable<std::string> table(tableSize, hashFunc);

    auto startInsert = std::chrono::high_resolution_clock::now();
    for (const auto& s : data) {
        table.insert(s);
    }
    auto endInsert = std::chrono::high_resolution_clock::now();

    auto startRemove = std::chrono::high_resolution_clock::now();
    for (const auto& s : data) {
        table.remove(s);
    }
    auto endRemove = std::chrono::high_resolution_clock::now();

    auto insertTime = std::chrono::duration_cast<std::chrono::microseconds>(endInsert - startInsert).count();
    auto removeTime = std::chrono::duration_cast<std::chrono::microseconds>(endRemove - startRemove).count();
    
    std::string folder = "wyniki/";
    std::filesystem::create_directories(folder);

    std::string insertFileName = folder + "insert_times_" + caseName + "_" + hashName + ".csv";
    bool fileExists = std::filesystem::exists(insertFileName);
    std::ofstream insertOut(insertFileName, std::ios::app);
    if (!fileExists || std::filesystem::file_size(insertFileName) == 0)
        insertOut << "liczba elementow,czas\n";
    insertOut << tableSize << "," << insertTime << "\n";
    insertOut.close();

    std::string removeFileName = folder + "remove_times" + caseName + "_" + hashName + ".csv";
    fileExists = std::filesystem::exists(removeFileName);
    std::ofstream removeOut(removeFileName, std::ios::app);
    if (!fileExists || std::filesystem::file_size(removeFileName) == 0)
        removeOut << "liczba elementow,czas\n";
    removeOut << tableSize << "," << removeTime << "\n";
    removeOut.close();



}

int main() {
    std::vector<size_t> sizes = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for (size_t n : sizes) {
        auto optimistic = generateOptimisticStrings(n);
        testHashFunction("simpleHash", simpleHash, n, n, "optymistyczny", optimistic);
        testHashFunction("polynomialHash", polynomialHash, n, n, "optymistyczny", optimistic);
        testHashFunction("djb2Hash", djb2Hash, n, n, "optymistyczny", optimistic);

        auto average = generateRandomStrings(n);
        testHashFunction("simpleHash", simpleHash, n, n, "sredni", average);
        testHashFunction("polynomialHash", polynomialHash, n, n, "sredni", average);
        testHashFunction("djb2Hash", djb2Hash, n, n, "sredni", average);

        auto pessimistic = generatePessimisticStrings(n);
        testHashFunction("simpleHash", simpleHash, n, n, "pesymistyczny", pessimistic);
        testHashFunction("polynomialHash", polynomialHash, n, n, "pesymistyczny", pessimistic);
        testHashFunction("djb2Hash", djb2Hash, n, n, "pesymistyczny", pessimistic);
    }

    std::cout << "Testy zakonczone. Wyniki zapisane w plikach." << std::endl;
    return 0;
}
