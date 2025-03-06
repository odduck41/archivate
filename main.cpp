#include <fstream>

int main() {
    uint8_t* const e = new uint8_t[256];
    for (int i = 0; i < 256; ++i) {
        e[i] = i;
    }
    std::ofstream os("../test.txt", std::ios::binary);
    os.write(reinterpret_cast<char*>(e), 256);
    os.close();
    delete[] e;
}