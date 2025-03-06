#include "include/Byte.h"
#include "include/HuffmanTree.h"

int main() {
    HuffmanTree b;
    b.decode("../result.packed", "../Hello.jpg", "../tree.tree");
}
