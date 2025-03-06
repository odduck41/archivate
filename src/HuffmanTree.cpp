#include "../include/HuffmanTree.h"
#include <set>
#include <fstream>
#include <__algorithm/ranges_reverse.h>

HuffmanTree::HuffmanTree(const char *filename) {
    read(filename);
    build();
}

void HuffmanTree::save(const char *filename, const char *tree) {
    read(filename);
    build();
    std::ofstream os(tree, std::ios::binary);
    os.write(reinterpret_cast<char*>(amount_), 256 * sizeof(uint32_t));
    os.close();
}

void HuffmanTree::load(const char * tree) {
    delete[] amount_;
    amount_ = new uint32_t[256]{};

    std::ifstream is(tree, std::ios::binary);
    is.read(reinterpret_cast<char*>(amount_), 256 * sizeof(uint32_t));
    is.close();

    build();
}

void HuffmanTree::encode(const char *filename) {
    delete[] code;
    std::vector<bool> seq;
    for (auto& byte: raw_) {
        const auto now = get(byte);
        seq.insert(seq.end(), now.begin(), now.end());
    }

    const uint64_t sz = seq.size();

    const auto result = new uint8_t[(sz + 7) / 8]{};

    for (size_t i = 0; i < sz; ++i) {
        const auto byte = i / 8;
        const auto r_bit = byte * 8 + 7 - i;
        if (seq[i]) {
            result[byte] |= (1 << r_bit);
        }
    }

    std::ofstream os(filename, std::ios::binary);
    os.write(reinterpret_cast<const char*>(&sz), sizeof(uint64_t));
    os.write(reinterpret_cast<char*>(result), sz);
    os.close();

    delete[] result;
}

void HuffmanTree::decode(const char *input, const char *output) {
    std::ifstream is(input, std::ios::binary);

    uint64_t sz = 0;
    is.read(reinterpret_cast<char*>(&sz), sizeof(uint64_t));

    auto encoded = new uint8_t[(sz + 7) / 8]{};
    is.read(reinterpret_cast<char*>(encoded), sz);

    is.close();

    std::vector<uint8_t> decoded;
    const Node *now = root_;

    for (size_t i = 0; i < sz; ++i) {
        const auto byte = i / 8;
        const auto r_bit = byte * 8 + 7 - i;
        if (!((encoded[byte] >> r_bit) & 0b1)) {
            now = now->left;
        } else {
            now = now->right;
        }

        if (now->left == now->right) {
            decoded.push_back(now->value);
            now = root_;
        }
    }
    delete[] encoded;

    auto result = &(*decoded.begin());

    std::ofstream os(output, std::ios::binary);
    os.write(reinterpret_cast<char*>(result), decoded.size());
    os.close();
}

void HuffmanTree::build() {
    clear();
    leaves_.clear();

    if (amount_ == nullptr) {
        amount_ = new uint32_t[256]{};

        for (const auto& byte: raw_) {
            ++amount_[byte];
        }
    }

    for (uint16_t i = 0; i < 256; ++i) {
        if (!amount_[i]) continue;
        leaves_.push_back(new Node{static_cast<uint8_t>(i), amount_[i]});
    }

    std::set<Node*, decltype(
        [](const Node* a, const Node* b) -> bool {
            if (a->weight == b->weight) {
                return a->value <= b->value;
            }
            return a->weight < b->weight;
        }
    )> tree = {leaves_.begin(), leaves_.end()};

    while (tree.size() > 1) {
        const auto left = *tree.begin();
        tree.erase(tree.begin());
        const auto right = *tree.begin();
        tree.erase(tree.begin());

        const auto parent = new Node{0, left->weight + right->weight, left, right};

        left->parent = right->parent = parent;
        tree.insert(parent);
    }

    root_ = *tree.begin();
}

void HuffmanTree::read(const char *filename) {
    std::ifstream is(filename, std::ios::binary);
    is.seekg(0, std::ios::end);
    const auto sz = is.tellg();
    is.seekg(0, std::ios::beg);

    raw_.resize(sz);
    auto ptr = &(*raw_.begin());
    is.read(reinterpret_cast<char*>(ptr), sz);
    is.close();
}

void HuffmanTree::clear(const Node *me) {
    if (me == nullptr) {
        me = root_;
        if (me == nullptr) return;
    }

    if (me->left != nullptr) {
        clear(me->left);
    }
    if (me->right != nullptr) {
        clear(me->right);
    }
    delete me;
    me = nullptr;
}

std::vector<bool> HuffmanTree::get(const uint8_t x) {
    if (code == nullptr) {
        code = new std::vector<bool>[256]{};
    }
    if (!code[x].empty()) return code[x];
    const Node *me = nullptr;
    for (const auto & leave : leaves_) {
        if (leave->value == x) {
            me = leave;
            break;
        }
    }

    if (me == nullptr) throw std::logic_error("Byte not found");

    while (me->parent != nullptr) {
        const auto parent = me->parent;

        if (parent->left == me) {
            code[x].push_back(false);
        } else {
            code[x].push_back(true);
        }

        me = parent;
    }

    std::ranges::reverse(code[x]);
    return code[x];
}
