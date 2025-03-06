#pragma once
#include "../include/Byte.h"
#include <set>

class HuffmanTree {
public:
    explicit HuffmanTree(const char *);

    void encode(const char *);
    void decode(const char *) const;
private:
    RawData data_{};

    struct Node {
        Byte leaf{};
        uint64_t amount{};

        Node *left{};
        Node *right{};

        Node* parent{};
    };

    static bool cmp(const Node* a, const Node* b);
    Node* root{};

    std::set<Node*, decltype(cmp)> leaves{};

    void build();
};
