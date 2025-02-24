#pragma once
#include <vector>
#include <map>

class HuffmanTree {
public:
    HuffmanTree() = default;
    auto save(const char*) -> void;
    auto load(const char*) -> void;
    auto create(const wchar_t*) -> void;

    auto operator[](const wchar_t&) -> unsigned long long;

private:
    struct Node {
        wchar_t letter{};
        unsigned int weight{};

        Node *left{}, *right{};

        Node *parent{};
    };

    static auto build(const Node*) -> unsigned long long;

    friend auto operator<(const Node*, const Node*) -> bool;

    Node *root{};
    std::vector<Node*> alphabet{};
    std::map<wchar_t, unsigned long long> letter_value;
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
