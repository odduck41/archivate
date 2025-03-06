#include <fstream>

#include "include/HuffmanTree.h"

int main() {
    HuffmanTree a("../images.jpeg");
    a.encode("../e.packed");
    a.save("../images.jpeg", "../e.tree");

    HuffmanTree b;
    b.load("../e.tree");
    b.decode("../e.packed", "../e.jpeg");

    // HuffmanTree a("../input.txt");
    // a.encode("../e.packed");
    // a.save("../input.txt", "../e.tree");

    // HuffmanTree b;
    // b.load("../e.tree");
    // b.decode("../e.packed", "../output.txt");
}
