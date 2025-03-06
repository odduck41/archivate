#include "../include/HuffmanTree.h"

#include <fstream>

HuffmanTree::HuffmanTree(const char *filename) {
    std::ifstream is(filename, std::ios_base::binary);
    is.seekg(0, std::ifstream::end);
    const size_t sz = is.tellg();
    is.seekg(0, std::ifstream::beg);

    data_.create(sz);
    is.read(data_, sz);

    build();
}

void HuffmanTree::build() {
}
