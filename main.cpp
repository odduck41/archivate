#include <fstream>

#include "include/HuffmanTree.h"

int main() {
    HuffmanTree a("../test/images.jpeg");
    a.encode("../test/e.packed");
    a.save("../test/images.jpeg", "../test/e.tree");

    HuffmanTree b;
    b.load("../test/e.tree");
    b.decode("../test/e.packed", "../test/e.jpeg");

    // HuffmanTree a("../input.txt");
    // a.encode("../e.packed");
    // a.save("../input.txt", "../e.tree");

    // HuffmanTree b;
    // b.load("../e.tree");
    // b.decode("../e.packed", "../output.txt");
}
