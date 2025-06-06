#include "HashTable.h"
#include <string>

size_t simpleHash(const std::string& s) {
    size_t hash = 0;
    for (char c : s) hash += c;
    return hash;
}

size_t polynomialHash(const std::string& s) {
    size_t hash = 0;
    for (char c : s) hash = hash * 13 + c;
    return hash;
}

size_t djb2Hash(const std::string& s) {
    size_t hash = 5381;
    for (char c : s) hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}



int main() {
    HashTable<std::string> table(10, simpleHash);
    table.insert("ala");
    table.insert("kot");
    table.print();
    table.remove("ala");
    table.print();

}
