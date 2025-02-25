#pragma once
#include <cstdint>
#include <string>
#include <vector>

class HuffmanTree {
public:
    HuffmanTree() = default;
    auto build(const std::string &) -> void;
    auto dump(const std::string &) const -> void;
    auto load(const std::string &) -> void;
    auto clear() -> void;

private:
    struct Node {
        unsigned char byte{};
        uint32_t weight{};

        Node *left{}, *right{};
        Node *parent{};
    };

    Node* root{};
    std::vector<Node*> bytes;
    static auto delete_vertex(Node*&) -> void;
    auto build() -> void;
};


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
