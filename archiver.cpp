#include <set>

#include "archiver.h"

auto HuffmanTree::create(const unsigned int* str) -> void {
    unsigned int count[96000 + 1]{};
    for (int i = 0; str[i] != 0; ++i) {
        ++count[str[i]];
    }

    std::set<Node*> tree;

    for (unsigned int i = 0; i < 96000 + 1; ++i) {
        if (count[i] == 0) continue;
        tree.insert(new Node{i, count[i]});
    }

    while (tree.size() > 1) {
        const auto left = *tree.begin();
        tree.erase(tree.begin());

        const auto right = *tree.begin();
        tree.erase(tree.begin());

        auto parent = new Node{0, left->weight + right->weight, left, right};
        tree.insert(parent);
    }

    root = *tree.begin();
}
