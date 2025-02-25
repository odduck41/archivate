#include <fstream>
#include <iostream>

#include "archiver.h"

int main() {
    std::ifstream is("../СЫЧ.in");
    is.seekg(0, std::ifstream::end);
    const long long size_ = is.tellg();
    is.seekg(0, std::ifstream::beg);

    char* a = new char[size_];
    is.read(a, size_);

    std::string s(a);

    HuffmanTree e;
    // e.build(s);
    e.load("../e.tree");
    e.setText("СЫЧ СЫЧЧ СЫЧ СЫЧ СЫЧ");

    e.pack("../СЫЧ1.squeezed");
    // e.dump("../e.tree");

    delete[] a;
}
