#include <cstdint>
#include <iostream>

uint32_t knuth_hash(uint32_t key, int bits) {
    return (key * 2654435769U) >> (32 - bits);
}

// Usage: hash to 2^10 = 1024 slots
// uint32_t hash = knuth_hash(12345, 10);

int main() {
    std::cout << "Hash of 12345 with 10 bits: " << knuth_hash(12345, 10) << std::endl;
    return 0;
}