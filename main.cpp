#include <bitset>
#include <iostream>

#include "archiver.h"

int main(int argc, const char** argv) {
    HuffmanTree h;
    h.create(L"Hello");
    std::wcout << std::bitset<sizeof(unsigned long long)>(h['H']) << std::endl;
    std::wcout << std::bitset<sizeof(unsigned long long)>(h['e']) << std::endl;
    std::wcout << std::bitset<sizeof(unsigned long long)>(h['l']) << std::endl;
    std::wcout << std::bitset<sizeof(unsigned long long)>(h['o']) << std::endl;
}
