#include "include/Byte.h"
#include <iostream>

int main() {
    Byte a(new unsigned char);
    a[0] = true;
    a[1] = true;
    a[3] = true;
    a[7] = true;
    for (int i = 0; i < 8; ++i) {
        std::cout << a[i].value();
    }
}