#include "archiver.h"

#include <fstream>
#include <set>
#include <algorithm>

auto HuffmanTree::build(const std::string &text) -> void {
    text_ = text;
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

auto HuffmanTree::operator[](const unsigned char &x) -> std::string {
    return get(x);
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
                return a->byte <= b->byte;
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

        const auto parent = new Node({0, left->weight + right->weight, left, right});
        left->parent = right->parent = parent;
        tree.insert(parent);
    }

    root = *tree.begin();
}

auto HuffmanTree::calculate(const Node *from) -> std::string {
    std::string result;

    while (from->parent != nullptr) {
        const auto parent = from->parent;
        if (parent->left == from) {
            result += '0';
        } else {
            result += '1';
        }

        from = parent;
    }

    std::ranges::reverse(result);

    return result;
}

auto HuffmanTree::get(const unsigned char &x) -> std::string {
    if (bytes[x]->weight == 0) {
        return {};
    }

    if (seq[x].empty()) {
        seq[x] = calculate(bytes[x]);
    }

    return seq[x];
}

auto HuffmanTree::binpack(const std::string &filename) -> void {
    std::ofstream os(filename, std::ios::binary);
    const auto s = packed();

    void *ptr = malloc((static_cast<int>(s.size()) + 7) / 8);
    // os.write(reinterpret_cast<char*>(s.size()), sizeof(size_t));
    // os << s.size() << "\n";
    uint64_t sz = s.size();
    os.write(reinterpret_cast<char *>(&sz), 8);
    // char nullbyte = 0;
    // os.write(reinterpret_cast<char *>(&nullbyte), 1);

    for (int i = 0; i < s.size(); ++i) {
        const int byte = i / 8;
        const int pwr = byte * 8 + 7 - i;
        if (s[i] == '1') {
            (*(static_cast<uint8_t*>(ptr) + byte)) |= (1 << pwr);
        }
    }

    os.write(static_cast<const char*>(ptr), (static_cast<int>(s.size()) + 7) / 8);
    os.close();
    free(ptr);
}

auto HuffmanTree::flatpack(const std::string &filename) -> void {
    std::ofstream os(filename);
    const auto s = packed();
    os.write(s.c_str(), static_cast<long>(s.size()));

    os.close();
}

auto HuffmanTree::packed() -> std::string {
    std::string result;
    for (const auto& byte: text_) {
        result += get(*reinterpret_cast<const unsigned char*>(&byte));
    }
    return result;
}

auto HuffmanTree::pack(const std::string &filename, const bool &binary) -> void {
    if (binary) binpack(filename);
    else flatpack(filename);
}

auto HuffmanTree::setText(const std::string &text) -> void {
    text_ = text;
}

auto HuffmanTree::unpack(const std::string &filename, const bool &binary) -> std::string {
    if (binary) return binunpack(filename);
    return flatunpack(filename);
}

auto HuffmanTree::binunpack(const std::string &filename) -> std::string {
    std::ifstream is(filename, std::ios::binary);

    uint64_t sz;
    is.read(reinterpret_cast<char *>(&sz), 8);

    void *ptr = malloc((static_cast<int>(sz) + 7) / 8);
    is.read(static_cast<char*>(ptr), (static_cast<int>(sz) + 7) / 8);

    std::string result;
    for (int i = 0; i < sz; ++i) {
        const int byte = i / 8;
        const int pwr = byte * 8 + 7 - i;

        if (((*(static_cast<uint8_t*>(ptr) + byte)) >> pwr) & 0b1) {
            result += "1";
        } else {
            result += "0";
        }

    }

    free(ptr);
    return unpacked(result);
}

auto HuffmanTree::flatunpack(const std::string &) -> std::string {}

auto HuffmanTree::symbol(std::string &way) const -> unsigned char {
    const Node* f = root;
    size_t i = 0;
    for (; i < way.size(); ++i) {
        if (way[i] == '0') {
            if (f->left == nullptr) {
                way = {way.begin() + i, way.end()};
                return f->byte;
            }
            f = f->left;
        } else {
            if (f->right == nullptr) {
                way = {way.begin() + i, way.end()};
                return f->byte;
            }
            f = f->right;
        }
    }
    way = {way.begin() + i, way.end()};
    return f->byte;
}

auto HuffmanTree::unpacked(std::string archived) -> std::string {
    std::string result;
    while (!archived.empty()) result += symbol(archived);
    return result;
}

auto HuffmanTree::read(const std::string &filename) -> void {
    std::ifstream is(filename);
    is.seekg(0, std::ifstream::end);
    const long long size_ = is.tellg();
    is.seekg(0, std::ifstream::beg);

    const auto a = new char[size_];
    is.read(a, size_);

    const std::string s(a);
    delete[] a;
    build(s);

}