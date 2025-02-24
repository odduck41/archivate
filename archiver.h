#pragma once

class HuffmanTree {
public:
    HuffmanTree() = default;
    auto save(const unsigned int*) -> void;
    auto load(const unsigned int*) -> void;
    auto create(const unsigned int*) -> void;

    auto operator[](unsigned int) const -> long long;

private:
    struct Node {
        unsigned int letter{};
        unsigned int weight{};

        Node *left{}, *right{};
    };

    friend auto operator<(const Node*, const Node*) -> bool;

    Node *root{};
};

void commands(int, const char**);

// squeezer [command]
//
// commands
// tree
//    --from=[string]
//    --to=[string]
// pack
//    --input=[string]
//    --output=[string]
// unpack
//    --input=[string]
//    --output=[string]
//    --tree=[string]
// Flags
//    --help
//
// squeezer [command] --help
