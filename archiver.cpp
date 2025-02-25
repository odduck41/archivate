#include "archiver.h"

#include <fstream>
#include <set>

auto HuffmanTree::build(const std::string &text) -> void {
    bytes.resize(256, nullptr);

    for (size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = new Node(i);
    }

    for (const auto& byte : text) {
        ++bytes[*reinterpret_cast<const unsigned char*>(&byte)]->weight;
    }

    build();
}

auto HuffmanTree::dump(const std::string &filename) const -> void {
    std::ofstream os(filename, std::ios::binary);
    for (const auto& byte: bytes) {
        os.write(reinterpret_cast<char*>(&byte->weight), sizeof(uint32_t));
    }
    os.close();
}

auto HuffmanTree::load(const std::string &filename) -> void {
    clear();
    std::ifstream is(filename, std::ios::binary);
    clear();

    bytes.resize(256, nullptr);
    for (size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = new Node(i);
        is.read(reinterpret_cast<char*>(&bytes[i]->weight), sizeof(uint32_t));
    }

    build();
}

auto HuffmanTree::clear() -> void {
    delete_vertex(root);
    bytes.clear();
}

auto HuffmanTree::delete_vertex(Node *&vertex) -> void {
    if (vertex == nullptr) return;

    auto left = vertex->left;
    auto right = vertex->right;

    delete_vertex(left);
    delete_vertex(right);

    delete vertex;
    vertex = nullptr;
}

auto HuffmanTree::build() -> void {
    std::set<Node*, decltype(
        [](const Node *a, const Node *b) -> bool {
            if (a->weight == b->weight) {
                return a->byte < b->byte;
            }
            return a->weight < b->weight;
        }
    )> tree;

    for (const auto& byte: bytes) {
        if (!byte->weight) continue;
        tree.insert(byte);
    }

    while (tree.size() > 1) {
        const auto left = *tree.begin();
        tree.erase(tree.begin());

        const auto right = *tree.begin();
        tree.erase(tree.begin());

        const auto parent = new Node({0, left->weight + right->weight});
        left->parent = right->parent = parent;
        tree.insert(parent);
    }

    root = *tree.begin();
}
