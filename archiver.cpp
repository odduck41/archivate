#include <set>

#include "archiver.h"

auto HuffmanTree::create(const wchar_t* str) -> void {
    size_t count[96000 + 1]{};
    bool was[96000 + 1]{};

    for (int i = 0; str[i] != 0; ++i) {
        ++count[str[i]];
    }

    std::set<Node*, decltype(
        [](const Node *a, const Node *b) -> bool {
            if (a->weight == b->weight) {
                return a->letter < b->letter;
            }
            return a->weight < b->weight;
    })> tree;

    for (size_t i = 0; i < 96000 + 1; ++i) {
        if (count[i] == 0) continue;
        if (!was[i]) {
            auto now = new Node{static_cast<wchar_t>(i), count[i]};
            tree.insert(now);
            alphabet.push_back(now);
            was[i] = true;
        }
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

auto HuffmanTree::operator[](const wchar_t &letter) -> size_t {
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

auto HuffmanTree::build(const Node *from) -> size_t {
    size_t result = 0;
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

auto convert(const char* str) -> const unsigned int* {

}