#pragma once
#include <vector>

class HuffmanTree {
public:
    explicit HuffmanTree(const char *);
    HuffmanTree() = default;

    void save(const char *, const char *);
    void load(const char *);

    void encode(const char *);
    void decode(const char *, const char *);
private:
    std::vector<uint8_t> raw_{};

    struct Node {
        uint8_t value{};
        uint32_t weight{};

        Node *left{}, *right{};
        Node *parent{};
    };

    Node *root_{};
    std::vector<Node*> leaves_{};
    std::vector<bool>* code{};
    uint32_t* amount_{};

    void build();
    void read(const char *);
    void clear(const Node* = nullptr);
    std::vector<bool> get(uint8_t);
};
