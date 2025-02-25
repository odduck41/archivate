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

    auto operator[](const unsigned char&) -> std::string;

    auto packed() -> std::string;
    auto pack(const std::string &, const bool & = true) -> void;
private:
    std::string text_{};

    struct Node {
        unsigned char byte{};
        uint32_t weight{};

        Node *left{}, *right{};
        Node *parent{};
    };

    Node* root{};
    std::vector<Node*> bytes;

    std::string seq[256]{};

    static auto delete_vertex(Node *&) -> void;
    auto build() -> void;

    static auto calculate(const Node *) -> std::string;
    auto get(const unsigned char &) -> std::string;

    auto binpack(const std::string &) -> void;
    auto flatpack(const std::string &) -> void;
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
