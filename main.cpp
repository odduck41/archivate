#include <fstream>
#include <iostream>

#include "archiver.h"

int main() {
    HuffmanTree tree;
    tree.read("../СЫЧ.in");
    tree.pack("../СЫЧ.sq");
    std::ofstream os("os");
    os << tree.unpack("../СЫЧ.sq");
    return 0;
}
