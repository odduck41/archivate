#include <set>

#include "archiver.h"

auto HuffmanTree::create(const wchar_t* str) -> void {
    unsigned int count[96000 + 1]{};

    for (int i = 0; str[i] != 0; ++i) {
        ++count[str[i]];
    }

    std::set<Node*> tree;

    for (unsigned int i = 0; i < 96000 + 1; ++i) {
        if (count[i] == 0) continue;
        tree.insert(new Node{i, count[i]});
        alphabet.push_back(*(--tree.end()));
    }

    while (tree.size() > 1) {
        const auto left = *tree.begin();
        tree.erase(tree.begin());

        const auto right = *tree.begin();
        tree.erase(tree.begin());

        auto parent = new Node{0, left->weight + right->weight, left, right};
        left->parent = right->parent = parent;

        tree.insert(parent);
    }

    root = *tree.begin();
}

auto HuffmanTree::operator[](const wchar_t& letter) -> unsigned long long {
    if (letter_value.contains(letter)) {
        return letter_value.at(letter);
    }

    const Node* ptr{};
    for (const auto& ltr : alphabet) {
        if (ltr->letter == letter) {
            ptr = ltr;
            break;
        }
    }

    letter_value[letter] = build(ptr);

    return letter_value[letter];
}

auto HuffmanTree::build(const Node* from) -> unsigned long long {
    unsigned long long result = 0;
    int power = 0;

    while (from->parent != nullptr) {
        const auto parent = from->parent;
        if (from == parent->right) {
            result += (1 << (++power));
        }
        from = parent;
    }

    return result;
}

auto operator<(const HuffmanTree::Node* a, const HuffmanTree::Node* b) -> bool {
    if (a->weight == b->weight) {
        return a->letter < b->letter;
    }
    return a->weight < b->weight;
}

auto convert(const char* str) -> const unsigned int* {

}