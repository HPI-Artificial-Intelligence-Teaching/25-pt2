#include <iostream>
#include <bitset>

int main() {
    std::bitset<8> bits;
    
    bits[0] = 1;
    bits[3] = 1;
    bits.set(7);
    
    std::cout << "Bitset: " << bits << std::endl;
    
    if (bits[3]) {
        std::cout << "Bit 3 is set" << std::endl;
    }
    
    bits.flip();
    std::cout << "After flip: " << bits << std::endl;
    
    std::cout << "Number of set bits: " << bits.count() << std::endl;
    
    return 0;
}