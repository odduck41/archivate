#include "include/Byte.h"
#include "include/HuffmanTree.h"
#include <fstream>

int main() {
    HuffmanTree a("../hello.txt");
    a.save("../tree.tree");
    a.encode("../encoded.p");

    HuffmanTree b;
    b.decode("../encoded.p", "../out.txt", "../tree.tree");
}
