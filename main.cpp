#include <bitset>
#include <iostream>

#include "archiver.h"

int main(int argc, const char** argv) {
    HuffmanTree h;
    h.create(L"Hello");
    std::wcout << std::bitset<sizeof(size_t)>(h['H']) << std::endl;
    std::wcout << std::bitset<sizeof(size_t)>(h['e']) << std::endl;
    std::wcout << std::bitset<sizeof(size_t)>(h['l']) << std::endl;
    std::wcout << std::bitset<sizeof(size_t)>(h['o']) << std::endl;
}
