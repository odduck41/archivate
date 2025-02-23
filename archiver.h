#pragma once

class HuffmanTree {
public:
    HuffmanTree() = default;
    void save(const char*);
    void load(const char*);
    void create(const char*);

    auto operator[](char) const -> long long;
private:
    struct Node {
        char letter{};
        long long weight{};

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
