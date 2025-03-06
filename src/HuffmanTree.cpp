#include "../include/HuffmanTree.h"

#include <fstream>
#include <iostream>
#include <__algorithm/ranges_reverse.h>

HuffmanTree::HuffmanTree(const char *filename) {
    read(filename);
    build();
}

void HuffmanTree::read(const char *filename) {
    std::ifstream is(filename, std::ios_base::binary);
    is.seekg(0, std::ifstream::end);
    const size_t sz = is.tellg();
    is.seekg(0, std::ifstream::beg);

    data_.create(sz);
    is.read(data_, static_cast<long>(sz));

    is.close();
}

std::vector<uint32_t> HuffmanTree::load(const char *filename) {
    std::vector<uint32_t> amount(256, 0);
    std::ifstream is(filename, std::ios::binary);
    for (auto& i: amount) {
        is.read(reinterpret_cast<char*>(&i), sizeof(uint32_t));
    }
    is.close();
    return amount;
}

void HuffmanTree::save(const char *filename) {
    std::vector<uint32_t> amount(256, 0);
    for (auto& byte: this->data_) {
        ++amount[byte.value()];
    }

    std::ofstream os(filename, std::ios::binary);
    for (auto& i: amount) {
        os.write(reinterpret_cast<char*>(&i), sizeof(uint32_t));
    }
    os.close();
}

void HuffmanTree::encode(const char *output) {
    const auto enc = encode();
    RawData encoded((enc.size() + 7) / 8);
    for (size_t i = 0; i < enc.size(); ++i) {
        encoded[i / 8][i - i / 8 * 8] = (enc[i] == '1');
    }
    std::ofstream os(output, std::ios::binary);
    auto sz = enc.size();
    os.write(reinterpret_cast<char*>(&sz), sizeof(uint64_t));
    os.write(encoded, static_cast<long>(encoded.size()));
    os.close();
}

void HuffmanTree::decode(const char *from, const char *to, const char *tree) {
    build(load(tree));
    std::ifstream is(from, std::ios::binary);
    uint64_t sz;
    is.read(reinterpret_cast<char*>(&sz), sizeof(uint64_t));
    RawData encoded((sz + 7) / 8);
    is.read(encoded, static_cast<long>(encoded.size()));
    is.close();

    RawData decoded(3);
    size_t index = 0;
    auto* nw = root;
    for (size_t i = 0; index < decoded.size(); ++i) {
        if (encoded[i / 8][i - i / 8 * 8]) {
            nw = nw->right;
        } else {
            nw = nw->left;
        }

        if (nw->left == nullptr) {
            decoded[index] = nw->leaf;
            nw = root;
            ++index;
        }
    }
    std::ofstream os(to, std::ios::binary);
    os.write(decoded, 3);
    os.close();

}

std::string HuffmanTree::encode() {
    std::string encoded;
    for (auto& i : data_) {
        encoded += get(i.value());
    }
    return encoded;
}

void HuffmanTree::build(std::vector<uint32_t> amount) {
    if (amount.empty()) {
        amount.resize(256, 0);
        for (auto& byte: data_) {
            ++amount[byte.value()];
        }

        for (auto& byte : data_) {
            leaves.push_back(new Node{byte, amount[byte.value()]});
        }
    } else {
        for (uint16_t i = 0; i < 256; ++i) {
            if (!amount[i]) continue;
            leaves.push_back(new Node{Byte(i), amount[i]});
        }
    }


    std::set<Node*, decltype([](const Node* a, const Node* b) {
        if (a->amount == b->amount) {
            return a->leaf.value() <= b->leaf.value();
        }
        return a->amount < b->amount;
    })> tree = {leaves.begin(), leaves.end()};

    while (tree.size() > 1) {
        const auto left = *tree.begin();
        tree.erase(tree.begin());
        const auto right = *tree.begin();
        tree.erase(tree.begin());

        const auto parent = new Node{Byte(), left->amount + right->amount, left, right};
        left->parent = right->parent = parent;
        tree.insert(parent);
    }
    root = *tree.begin();
}

std::string HuffmanTree::get(const unsigned char x) {
    if (path.contains(x)) return path[x];
    std::string way;
    const Node *now = nullptr;
    for (const auto& i : leaves) {
        if (i->leaf.value() == x) {
            now = i;
            break;
        }
    }
    if (now == nullptr) throw std::logic_error("Symbol not found");

    while (now->parent != nullptr) {
        const auto parent = now->parent;
        if (parent->left == now) {
            way += '0';
        } else {
            way += '1';
        }
        now = parent;
    }
    std::ranges::reverse(way);
    path[x] = way;
    return path[x];
}
