#pragma once
#include "../include/Byte.h"

class HuffmanTree {
public:
    explicit HuffmanTree(const char *);

    void encode(const char *);
    void decode(const char *) const;
private:
    RawData data_{};

    struct Node {
        Byte leaf{};

        Node *left{};
        Node *right{};

        Node* parent{};
    };

    Node* root{};
    Node* leaves{};

    void build();
};
