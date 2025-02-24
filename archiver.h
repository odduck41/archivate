#pragma once
#include <bitset>
#include <vector>
#include <map>

template<size_t length>
struct symbol {
    std::bitset<length> seq;
};

class HuffmanTree {
public:
    HuffmanTree() = default;
    auto save(const char*) -> void;
    auto load(const char*) -> void;
    auto create(const wchar_t*) -> void;

    auto operator[](const wchar_t&) -> size_t;

private:
    struct Node {
        wchar_t letter{};
        size_t weight{};

        Node *left{}, *right{};

        Node *parent{};
    };

    static auto build(const Node*) -> size_t;

    Node *root{};
    std::vector<Node*> alphabet{};
    std::map<wchar_t, size_t> letter_value;
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
