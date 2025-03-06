#pragma once
#include "../include/Byte.h"
#include <set>
#include <map>


class HuffmanTree {
public:
    explicit HuffmanTree(const char *);
    HuffmanTree() = default;

    std::vector<uint32_t> load(const char *);
    void save(const char *);

    void encode(const char *);
    void decode(const char *, const char *, const char *);
    std::string encode();
private:
    RawData data_{};

    struct Node {
        Byte leaf{};
        uint32_t amount{};

        Node *left{};
        Node *right{};

        Node* parent{};
    };
    Node* root{};

    std::vector<Node*> leaves{};
    std::map<unsigned char, std::string> path{};

    void read(const char *);
    void build(std::vector<uint32_t> = {});
    std::string get(unsigned char);
};
