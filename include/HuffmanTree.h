#pragma once
#include "../include/Byte.h"

class HuffmanTree {
public:
    explicit HuffmanTree(const unsigned char *);

    void encode(const unsigned char *);
    void decode(const unsigned char *);
private:
    RawData data_{};

    struct Node {
        Byte leaf{};

        Node *left{};
        Node *right{};

        Node* parent{};
    };

};