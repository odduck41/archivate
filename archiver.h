#pragma once
#include <vector>
#include <map>

class HuffmanTree {
public:
    HuffmanTree() = default;
    auto save(const unsigned int*) -> void;
    auto load(const unsigned int*) -> void;
    auto create(const unsigned int*) -> void;

    auto operator[](const unsigned int&) -> unsigned long long;

private:
    struct Node {
        unsigned int letter{};
        unsigned int weight{};

        Node *left{}, *right{};

        Node *parent{};
    };

    static auto build(const Node*) -> unsigned long long;

    friend auto operator<(const Node*, const Node*) -> bool;

    Node *root{};
    std::vector<Node*> alphabet{};
    std::map<unsigned int, unsigned long long> letter_value;
};


auto convert(const char*) -> const unsigned int*;
auto convert(const unsigned int*) -> const char*;

auto commands(int, const char**) -> void;

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
