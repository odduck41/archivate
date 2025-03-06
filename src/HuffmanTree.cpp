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

bool HuffmanTree::cmp(const Node *a, const Node *b) {
    if (a->amount == b->amount) {
        return a->leaf.value() <= b->leaf.value();
    }
    return a->amount < b->amount;
}

void HuffmanTree::build() {
    std::vector<uint64_t> amount(256);
    for (auto& byte: data_) {
        ++amount[byte.value()];
    }

    for (auto& byte : data_) {
        leaves.insert(new Node{byte, amount[byte.value()]});
    }

    auto tree = leaves;

    while (tree.size() > 1) {
        const auto left = *tree.begin();
        tree.erase(tree.begin());
        const auto right = *tree.begin();
        tree.erase(tree.begin());

        const auto parent = new Node{Byte(), left->amount + right->amount, left, right};
        left->parent = right->parent = parent;
        tree.insert(parent);
    }
    root = *tree.begin();
}
